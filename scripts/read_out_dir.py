#!/usr/bin/python
# -*- coding: utf-8; -*-

import re
import os
import sys
import glob
import time
import datetime
import logging

import hdf5_types

logging.basicConfig(format='%(levelname)s:%(message)s', level=logging.INFO)
logger = logging.getLogger(__name__)

import numpy as np
import mpmath as mp
mp.mp.dps = 1000

sphere_volume = 4./3. * np.pi * 0.5**3

modfac_file_pattern = re.compile(r"modfac_entropy_dump,(?P<date>[0-9]{8}-[0-9]{6}),mod=(?P<modfac>[0-9.e-]+)$")

def parse_filename(filename):
    filename_matcher = modfac_file_pattern.search(filename)
    modfactor = filename_matcher.group('modfac')
    modfactor = float(modfactor)
    date = filename_matcher.group('date')
    date = datetime.datetime.strptime(date, "%Y%m%d-%H%M%S")
    date = time.mktime(date.timetuple())
    date = int(date)
    return {'modfactor': modfactor, 'timestamp': date}

def mp_average(data, log_weights):
    total = mp.mpf(0.)
    sum_weights = 0.
    for datum, log_weight in zip(data, log_weights):
        datum = mp.mpf(float(datum))
        log_weight = mp.mpf(log_weight)
        weight = mp.exp(log_weight)
        total += datum * weight
        sum_weights += weight
    total /= sum_weights
    return float(total)

def calc_means(data, lambda_correction = 0., mu_values = np.arange(-4., 4., 1.)):
    means = []
    for mu in mu_values:
        log_weights = data['S'] + data['n']*(mu + lambda_correction)
        mean_for_mu = mp_average(data['n'], log_weights)
        if not mean_for_mu:
            continue
        means.append((mu, mean_for_mu))
    return means

def write_table(out_filename, results):
    with open(out_filename, "w") as out_fhandle:
        for line in results:
            out_fhandle.write("\t".join(map(str, line)) + "\n")

def write_means(file_or_directory_name, results_means):
    out_filename_means = os.path.join(file_or_directory_name, "read_out_results_means.dat")
    logger.info("Writing results for mean particle numbers to file " + str(out_filename_means))
    write_table(out_filename_means, results_means)

def write_timestamps(file_or_directory_name, results_timestamps):
    out_filename_timestamps = os.path.join(file_or_directory_name, "read_out_results_timestamps.dat")
    logger.info("Writing results for timestamps to file " + str(out_filename_timestamps))
    write_table(out_filename_timestamps, results_timestamps)

def write_hdf5(file_or_directory_name, results_means, results_timestamps):
    out_filename_hdf5 = os.path.join(file_or_directory_name, "read_out_results.hdf5")
    import tables
    logger.info("Opening HDF5 table " + out_filename_hdf5)
    out_file = tables.openFile(out_filename_hdf5, mode="w", title="Read out for dir " + file_or_directory_name)
    out_data_filter = tables.Filters(complevel=9, complib="bzip2", shuffle=True, fletcher32=True)

    measurements_group = out_file.createGroup("/", "measurements", "Aggregated result data")
    timestamp_table = out_file.createTable(measurements_group, 'timestamp', hdf5_types.Timestamp, "Timestamps for all modfactors", filters=out_data_filter)
    averages_table = out_file.createTable(measurements_group, 'average', hdf5_types.ParticleNumberEstimation, "Estimations for the average number of particles", filters=out_data_filter)

    average = averages_table.row
    for line in results_means:
        average["modfactor"], average["mu"], average["avN"] = line
        average.append()

    timestamp = timestamp_table.row
    for line in results_timestamps:
        timestamp["modfactor"], timestamp["timestamp"] = line
        timestamp.append()

    out_file.close()
    logger.info("Saved HDF5 table " + out_filename_hdf5)

def extract_data(file_or_directory_name, lambda_correction = 0., mu_values = np.arange(-4., 4., 1.), hdf5=False):
    if os.path.isfile(file_or_directory_name):
        dir_mode = False
        all_modfac_files = [file_or_directory_name]
        target_filename = file_or_directory_name + ".dat"
    elif os.path.isdir(file_or_directory_name):
        dir_mode = True
        all_modfac_files = glob.glob(file_or_directory_name + "/modfac_entropy_dump,*")
        all_modfac_files.sort(key=lambda f: os.path.getmtime(f))
        target_filename = os.path.join(file_or_directory_name, "modfac_extract.dat")
    else:
        return

    # parse directory name for parameters?
    # put parameters into files?
    
    results_means = []
    results_means.append(["# modfactor", "mu", "avN"])
    results_timestamps = []
    results_timestamps.append(["# modfactor", "timestamp"])
    for filename in all_modfac_files:
        parameters = parse_filename(filename)
        modfactor = parameters['modfactor']
        modfactor = float(modfactor)
        timestamp = parameters['timestamp']
        timestamp = int(timestamp)
        results_timestamps.append((modfactor, timestamp))
        
        logger.info("Processing entry t=" + str(timestamp) + " , m=" + str(modfactor))
        data = np.loadtxt(filename, dtype=[('n', 'i4'), ('S', 'f8')])
        for mu, mean in calc_means(data, mu_values = mu_values):
            results_means.append((modfactor, mu, mean))

    if dir_mode and not hdf5:
        write_means(file_or_directory_name, results_means)
        write_timestamps(file_or_directory_name, results_timestamps)
    elif dir_mode and hdf5:
        write_hdf5(file_or_directory_name, results_means[1:], results_timestamps[1:])
    else:
        logger.info("Single file mode not supported ATM.")


def process_cmdline(argv = None):
    if not argv:
        argv = sys.argv[1:]

    import optparse
    parser = optparse.OptionParser(formatter=optparse.TitledHelpFormatter(width = 120), add_help_option = None)
    parser.add_option('-h', '--help', action='help', help="Show this help message and exit")
    parser.add_option('--lambda-in', action='store', dest='lambda_in', type="float", default=sphere_volume, help="Specify thermal wavelength Lamba^3 used in simulation.")
    parser.add_option('--lambda-out', action='store', dest='lambda_out', type="float", default=sphere_volume, help="Specify thermal wavelength Lamba^3 used in simulation.")
    parser.add_option('--mu-min', action='store', dest='mu_min', type="float", default=-4., help="Minimal mu value")
    parser.add_option('--mu-max', action='store', dest='mu_max', type="float", default=4., help="Maximal mu value - not included")
    parser.add_option('--mu-step', action='store', dest='mu_step', type="float", default=1., help="Step size between mu values")
    parser.add_option('--hdf5', action='store_true', dest='hdf5', help="Output in HDF5 format. Default is CSV.")
    parser.add_option('--csv', action='store_false', dest='hdf5', help="Output in CSV format. Default.")
  
    settings, args = parser.parse_args(argv)
    return settings, args


def main(argv = None):
    settings, args = process_cmdline(argv)

    thermal_wavelength_calculated = settings.lambda_in
    thermal_wavelength_for_comparison = settings.lambda_out
    thermal_wavelength_exponent_correction = np.log(thermal_wavelength_calculated) - np.log(thermal_wavelength_for_comparison)

    mu_values = np.arange(settings.mu_min, settings.mu_max, settings.mu_step)

    out_files_or_dirs = args
    for out_file_or_dir in out_files_or_dirs:
        logger.info("Beginning processing of " + str(out_file_or_dir))
        extract_data(out_file_or_dir, lambda_correction=thermal_wavelength_exponent_correction, mu_values=mu_values, hdf5=settings.hdf5)
    
    return 0

if __name__ == "__main__":
    status = main()
    sys.exit(status)
