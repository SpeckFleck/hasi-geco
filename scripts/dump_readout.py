#!/usr/bin/python
# -*- coding: utf-8; -*-

def process_cmdline(argv = None):
    if not argv:
        argv = sys.argv[1:]

    import optparse
    parser = optparse.OptionParser(formatter=optparse.TitledHelpFormatter(width = 120), add_help_option = None)
    parser.add_option('-h', '--help', action='help', help="Show this help message and exit")
    parser.add_option('--best-dos', action='store_true', dest='best_dos', help="Output best estimate dos as CSV.")
    parser.add_option('--best-average', action='store_true', dest='best_average', help="Output best estimate mu <-> avN as CSV.")
    parser.add_option('--timestamps', action='store_true', dest='timestamps', help="Output timestamps for modfactors.")
    parser.add_option('--convergence', action='store_true', dest='convergence', help="Output convergence of avN as CSV.")
  
    settings, args = parser.parse_args(argv)
    return settings, args


def main(argv = None):
    settings, args = process_cmdline(argv)

    if len(args) > 1:
        raise RuntimeError("Only 1 file can be processed at a time.")

    filename = args[0]
    logger.info("Beginning processing of " + str(filename))

    if settings.best_dos:
        pass
    elif settings.best_average:
        pass
    elif settings.timestamps:
        pass
    elif settings.convergence:
        pass
    
    return 0

if __name__ == "__main__":
    status = main()
    sys.exit(status)
