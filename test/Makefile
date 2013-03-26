CC = gcc
CXX = g++

MOCASINNS_ROOT = ../../mocasinns
MOCASINNS_INCLUDE =  -I$(MOCASINNS_ROOT)/libmocasinns/include

CFLAGS_DEBUG = -ggdb3 -pg
CFLAGS_PREFERENCES = -std=gnu++0x -mfpmath=sse
CFLAGS_OPTIMIZATION = #-O3 -march=native
CFLAGS_WARNINGS = -Wall -Wextra -pedantic
CFLAGS_INCLUDE = -I../include $(MOCASINNS_INCLUDE)
CFLAGS = $(CFLAGS_DEBUG) $(CFLAGS_PREFERENCES) $(CFLAGS_OPTIMIZATION) $(CFLAGS_WARNINGS) $(CFLAGS_INCLUDE)


LDFLAGS_BOOST = -static
LDFLAGS = $(LDFLAGS_BOOST)

TEST_LIBS = -lcppunit -lboost_serialization -lpthread -lboost_signals
TEST_LIBS_PATH = 
TEST_OBJECTS += test_mcchd_WangLandau.o
TEST_OBJECTS += test_mcchd_Metropolis.o
TEST_OBJECTS += test_Step.o
TEST_OBJECTS += test_HardDiscs.o
TEST_OBJECTS += test_CollisionFunctor_SingularDefects.o
TEST_OBJECTS += test_CollisionFunctor_NodalSurfaces.o
TEST_OBJECTS += test_CollisionFunctor_SimpleGeometries.o
TEST_OBJECTS += test_LookupTable.o
TEST_OBJECTS += test_Disc.o
TEST_OBJECTS += test_Point.o
TEST_OBJECTS += test.o

all: test

test: $(TEST_OBJECTS) $(OBJ_LIB)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(TEST_OBJECTS) $(TEST_LIBS_PATH) $(TEST_LIBS) -o test


-include $(TEST_OBJECTS:.o=.d)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
	$(CXX) $(CFLAGS) -MM -MF $*.d $<

clean:
	rm -f *.o *.d test
