#!/usr/bin/python
# -*- coding: utf-8; -*-

import tables

class ParticleNumberConvergence(tables.IsDescription):
    modfactor = tables.FloatCol()
    mu = tables.FloatCol()
    avN = tables.FloatCol()

class Timestamp(tables.IsDescription):
    modfactor = tables.FloatCol()
    timestamp = tables.UInt64Col()

class ParticleNumberEstimation(tables.IsDescription):
    mu = tables.FloatCol()
    avN = tables.FloatCol()

class DensityOfStates(tables.IsDescription):
    N = tables.UInt64Col()
    S = tables.FloatCol()


if __name__ == "__main__":
    pass
