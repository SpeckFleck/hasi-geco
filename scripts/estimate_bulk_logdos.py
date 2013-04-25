#!/usr/bin/python
# -*- coding: utf-8; -*-

import sys
import numpy as np

HARD_SPHERE_RADIUS = 0.5
SPHERE_VOLUME = np.pi * pow(HARD_SPHERE_RADIUS, 3) * 4. / 3.
THERMAL_WAVELENGHT_POW3 = SPHERE_VOLUME
log_thermal_wavelength_pow3 = np.log(THERMAL_WAVELENGHT_POW3)

# fitted heuristically
V_free_polycoeffs = np.array([3.82096924e+02, 6.21187256e+03, -7.71055722e+03, 3.33799588e+03, -7.51297200e+02, 5.07092032e+01, -1.85825727e+01, -7.94670516e+00, -1.26357161e-04])

def get_V_free_estimate(density):
    """Return estimate for free volume fraction"""
    return np.polyval(V_free_polycoeffs, density)
    
def get_logdos_estimate(V_box, eta_max):
    logdos = [(0., 0.)]
    N_max = int(eta_max * V_box / SPHERE_VOLUME)
    for N in xrange(1, N_max):
        N_prev, S_prev = logdos[-1]
        density = N * SPHERE_VOLUME / V_box
        log_V_free = get_V_free_estimate(density) + np.log(V_box)
        S = S_prev + log_V_free - log_thermal_wavelength_pow3 - np.log(N)
        logdos.append((N, S))
    logdos = np.array(logdos, dtype=[("N", "i4"), ("S", "f8")])
    np.savetxt(sys.stdout, logdos)

def process_cmdline(argv):
    """Return 2-tuple of a settings object and an argument list.
    If argv is None, sys.argv[1:] is used.
    """
    if not argv:
        import sys
        argv = sys.argv[1:]

    import optparse
    parser = optparse.OptionParser(
        formatter=optparse.TitledHelpFormatter(width = 120),
        add_help_option = None)

    parser.add_option('-h', '--help', action='help', help="Show this help message and exit")
    parser.add_option('-x', '--width', action='store', dest='width', type='float', default=5., help="Specify system width")
    parser.add_option('-y', '--height', action='store', dest='height', type='float', default=5., help="Specify system height")
    parser.add_option('-z', '--depth', action='store', dest='depth', type='float', default=5., help="Specify system depth")
    parser.add_option('-e', '--density_max', action='store', dest='eta_max', type='float', default=0.2, help="Specify maximum particle density for which an estimate should be generated")

    settings, args = parser.parse_args(argv)
    return settings, args

def main(argv = None):
    """Main function called in command mode."""
    settings, args = process_cmdline(argv)

    V_box = settings.width * settings.height * settings.depth
    # code here
    get_logdos_estimate(V_box, settings.eta_max)

    return 0

if __name__ == "__main__":
    status = main()
    sys.exit(status)
