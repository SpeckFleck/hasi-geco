#!/usr/bin/python
# -*- coding: utf-8; -*-

import re
import os
import sys
import glob
import time
import datetime
import numpy as np
import mpmath as mp
mp.mp.dps = 1000

thermal_wavelength_calculated = 1.
thermal_wavelength_for_comparison = 4./3. * np.pi * 0.5**3
thermal_wavelength_exponent_correction = np.log(thermal_wavelength_calculated) - np.log(thermal_wavelength_for_comparison)
mu_values = np.arange(-4., 4., 1.)

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

def mp_average(data, weights):
    total = mp.mpf(0.)
    sum_weights = 0.
    for datum, weight in zip(data, weights):
        datum = mp.mpf(float(datum))
        weight = mp.mpf(weight)
        total += datum * weight
        sum_weights += weight
    total /= sum_weights
    return float(total)    

def calc_means(data):
    means = []
    for mu in mu_values:
        mean_for_mu = mp_average(data['n'], np.exp(data['S'] + data['n']*(mu + thermal_wavelength_exponent_correction)))
        if not mean_for_mu:
            continue
        means.append(mean_for_mu)
    return means

def extract_data(file_or_directory_name):
    if os.path.isfile(file_or_directory_name):
        all_modfac_files = [file_or_directory_name]
        target_filename = file_or_directory_name + ".dat"
    elif os.path.isdir(file_or_directory_name):
        all_modfac_files = glob.glob(file_or_directory_name + "/modfac_entropy_dump,*")
        target_filename = os.path.join(file_or_directory_name, "modfac_extract.dat")
    else:
        return

    # parse directory name for parameters?
    # put parameters into files?
    
    results = []
    for filename in all_modfac_files:
        data = np.loadtxt(filename, dtype=[('n', 'i4'), ('S', 'f8')])
        means = calc_means(data)
        parameters = parse_filename(filename)
        modfactor = parameters['modfactor']
        timestamp = parameters['timestamp']
        print modfactor, timestamp, means
        
    print results


def process_cmdline(argv = None):
    if not argv:
        argv = sys.argv[1:]

    import optparse
    parser = optparse.OptionParser(formatter=optparse.TitledHelpFormatter(width = 120), add_help_option = None)
    parser.add_option('-h', '--help', action='help', help="Show this help message and exit")
    
    settings, args = parser.parse_args(argv)
    return settings, args


def main(argv = None):
    settings, args = process_cmdline(argv)

    out_files_or_dirs = args
    for out_file_or_dir in out_files_or_dirs:
        extract_data(out_file_or_dir)
    
    return 0

if __name__ == "__main__":
    status = main()
    sys.exit(status)
