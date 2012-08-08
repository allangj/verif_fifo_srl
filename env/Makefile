#
#  Makefile to compile the environment
#
#  Author: Allan Granados Jiménez
# 
#

INFILE		= main
OUTFILE		= test
SYSTEMC		=/usr/local/systemc
LDFLAGS		= -L$(SYSTEMC)/lib-linux64 -lsystemc -lm
CXXFLAGS	=-Wno-deprecated -I$(SYSTEMC)/include -fpermissive

.PHONY: all build clean

all: build

build:
	g++ $(CXXFLAGS) -o $(OUTFILE).out $(INFILE).cpp $(LDFLAGS)

clean:
	rm -rf $(OUTFILE).out

