# Makefile for zipkin_import

# Settings specific for Mac OS X and MacPorts
CXX=clang++
CFLAGS=-g
LIB_PATHS=-L/opt/local/lib -L/usr/local/lib
INC_PATHS=-I/opt/local/include/apr-1 -I/opt/local/include
THRIFT_DIR=/opt/local/include/thrift
BOOST_DIR=/opt/local/include
OBJDIR=bin

INC= -I$(THRIFT_DIR) -I$(BOOST_DIR)
LIBS=-lthrift

SOURCES    := ${wildcard src/*.cpp src/thrift/*.cpp}
CLIENT_OBJS    := ${SOURCES:.cpp=.o}

$(info $(SOURCES))
$(info $(CLIENT_OBJS))

zipkin_import: $(CLIENT_OBJS)
		$(CXX) -o zipkin_import -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H\
                                $(INC) $(LIB_PATHS) $(LIBS) $(CLIENT_OBJS)

%.o : %.cpp
		$(CXX) $(CFLAGS) $(INC_PATHS) -o $*.o -c $<

clean:
		rm -f zipkin_import $(CLIENT_OBJS)
