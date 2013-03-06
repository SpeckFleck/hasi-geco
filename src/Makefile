CC = gcc
CXX = g++

MOCASINNS_ROOT = ../../mocasinns
MOCASINNS_INCLUDE =  -I$(MOCASINNS_ROOT)/libmocasinns/include
MOCASINNS_RANDOM_INCLUDE = -I$(MOCASINNS_ROOT)/librandom/include
MOCASINNS_RANDOM_LIB = -L$(MOCASINNS_ROOT)/librandom/lib

CFLAGS_DEBUG = -g -pg
CFLAGS_PREFERENCES = -std=gnu++0x -mfpmath=sse
CFLAGS_OPTIMIZATION = -O3 -march=native
CFLAGS_WARNINGS = -Wall -Wextra -pedantic
CFLAGS_INCLUDE = -I../include $(MOCASINNS_RANDOM_INCLUDE) $(MOCASINNS_INCLUDE)
CFLAGS = $(CFLAGS_DEBUG) $(CFLAGS_PREFERENCES) $(CFLAGS_OPTIMIZATION) $(CFLAGS_WARNINGS) $(CFLAGS_INCLUDE)


LDFLAGS_BOOST = -static
LDFLAGS = $(LDFLAGS_BOOST)

MCCHD_WL_LIBS = -lcppunit -lrandom -lboost_serialization -lboost_signals -lboost_program_options -lboost_system -lboost_filesystem -lboost_log -lboost_thread -lpthread -lrt
MCCHD_WL_LIBS_PATH = $(MOCASINNS_RANDOM_LIB)
MCCHD_WL_OBJECTS = mcchd_wl.o

all: mcchd_wl

mcchd_wl: $(MCCHD_WL_OBJECTS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(MCCHD_WL_OBJECTS) $(MCCHD_WL_LIBS_PATH) $(MCCHD_WL_LIBS) -o mcchd_wl


-include $(TEST_OBJECTS:.o=.d)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
	$(CXX) $(CFLAGS) -MM -MF $*.d $<

clean:
	rm -f *.o *.d test
