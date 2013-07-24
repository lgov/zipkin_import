# Makefile for zipkin_import

# Settings specific for Mac OS X and MacPorts
CXX=clang++
CFLAGS=-g
LIB_PATHS=-L/opt/local/lib -L/usr/local/lib
INC_PATHS=-I./src -I/opt/local/include
OBJDIR=bin

LIBS=-lthrift -lboost_program_options-mt

SOURCES = ${wildcard src/*.cpp src/thrift/*.cpp}
CLIENT_OBJS = ${SOURCES:.cpp=.o}

zipkin_import: $(CLIENT_OBJS)
		$(CXX) -o zipkin_import -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H\
                                $(INC_PATHS) $(LIB_PATHS) $(LIBS) $(CLIENT_OBJS)

TEST_SOURCES = ${filter-out src/zipkin_import.cpp, ${wildcard test/*.cpp} \
		$(SOURCES) }
TEST_OBJS = ${TEST_SOURCES:.cpp=.o}

test: ${TEST_OBJS}
		$(CXX) -o zipkin_import_tests -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H\
				$(INC_PATHS) $(LIB_PATHS) $(LIBS) -lboost_unit_test_framework-mt\
                $(TEST_OBJS)

%.o : %.cpp
		$(CXX) $(CFLAGS) $(INC_PATHS) -o $*.o -c $<

clean:
		rm -f zipkin_import zipkin_import_tests $(CLIENT_OBJS)
