CC = gcc
CXX = g++

MOCASINNS_ROOT = ../../mocasinns
MOCASINNS_INCLUDE =  -I$(MOCASINNS_ROOT)/libmocasinns/include

CFLAGS_DEBUG = #-ggdb3 -pg --coverage
CFLAGS_PREFERENCES = -std=gnu++0x -mfpmath=sse
CFLAGS_OPTIMIZATION = -O3 -march=native
CFLAGS_WARNINGS = -Wall -Wextra -pedantic
CFLAGS_INCLUDE = -I../include $(MOCASINNS_INCLUDE)
CFLAGS = $(CFLAGS_DEBUG) $(CFLAGS_PREFERENCES) $(CFLAGS_OPTIMIZATION) $(CFLAGS_WARNINGS) $(CFLAGS_INCLUDE)


LDFLAGS_BOOST = -static
LDFLAGS = $(LDFLAGS_BOOST)

MCCHD_WL_OPTIONS = 
MCCHD_WL_LIBS = -lboost_serialization -lboost_signals -lboost_program_options -lboost_system -lboost_filesystem -lboost_log_setup -lboost_log -lboost_thread -lpthread -lrt
MCCHD_WL_LIBS_PATH = 
MCCHD_WL_SOURCES = mcchd_wl.cpp

MCCHD_METRO_OPTIONS = 
MCCHD_METRO_LIBS = -lboost_serialization -lboost_signals -lboost_program_options -lboost_system -lboost_filesystem -lboost_log_setup -lboost_log -lboost_thread -lpthread -lrt
MCCHD_METRO_LIBS_PATH = $(MOCASINNS_RANDOM_LIB)
MCCHD_METRO_SOURCES = mcchd_metropolis.cpp

all: mcchd_wl_bulk

ALL_TARGETS = mcchd_wl_bulk mcchd_wl_plane mcchd_wl_line mcchd_wl_point

mcchd_wl_bulk: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=Bulk
mcchd_wl_plane: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=PlaneDefect
mcchd_wl_line: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=LineDefect
mcchd_wl_point: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=PointDefect

ALL_TARGETS += mcchd_wl_innersphere mcchd_wl_outersphere mcchd_wl_innercylinder mcchd_wl_outercylinder

mcchd_wl_innersphere: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=InnerSphere
mcchd_wl_outersphere: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=OuterSphere
mcchd_wl_innercylinder: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=InnerCylinder
mcchd_wl_outercylinder: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=OuterCylinder

ALL_TARGETS += mcchd_wl_nodal_p mcchd_wl_nodal_g mcchd_wl_nodal_d mcchd_wl_nodal_inner_iwp mcchd_wl_nodal_outer_iwp

mcchd_wl_nodal_p: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=PSurface
mcchd_wl_nodal_g: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=DSurface
mcchd_wl_nodal_d: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=GSurface
mcchd_wl_nodal_inner_iwp: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=InnerIWPSurface
mcchd_wl_nodal_outer_iwp: MCCHD_WL_OPTIONS = -DCONTAINER_NAME=OuterIWPSurface

$(ALL_TARGETS): $(MCCHD_WL_SOURCES)
	$(CXX) $(CFLAGS) $(MCCHD_WL_SOURCES) $(LDFLAGS) $(INCLUDE) $(MCCHD_WL_OPTIONS) $(MCCHD_WL_LIBS_PATH) $(MCCHD_WL_LIBS) -o $@

really-all: $(ALL_TARGETS) mcchd_metropolis

mcchd_metropolis: MCCHD_METRO_OPTIONS = -DCONTAINER_NAME=Bulk

mcchd_metropolis: $(MCCHD_METRO_SOURCES)
	$(CXX) $(CFLAGS) $(MCCHD_METRO_SOURCES) $(LDFLAGS) $(INCLUDE) $(MCCHD_METRO_OPTIONS) $(MCCHD_METRO_LIBS_PATH) $(MCCHD_METRO_LIBS) -o $@

clean:
	rm -f *.o *.d $(ALL_TARGETS) mcchd_metropolis
