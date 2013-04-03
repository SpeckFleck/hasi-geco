#!/usr/bin/python
# -*- coding: utf-8; -*-

import tables

class ParticleNumberEstimation(tables.IsDescription):
    modfactor = tables.FloatCol()
    mu = tables.FloatCol()
    avN = tables.FloatCol()

class Timestamp(tables.IsDescription):
    modfactor = tables.FloatCol()
    timestamp = tables.UInt64Col()

if __name__ == "__main__":
    pass
