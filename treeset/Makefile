#
# Makefile for CS 70 Spell Checking Assignment
# 

###############################################################################
# MAKEFILE VARIABLES
###############################################################################

# CXX is the name of the compiler we are using (clang++)

CXX = clang++

# CXXFLAGS are the flags we will be passing each compile
#    (our standard flags, plus some extras for Google Test)

EXTRA_CXXFLAGS = -I. -DGTEST_HAS_PTHREAD=0    # For Google Test
CXXFLAGS       = -g -std=c++11 -Wall -Wextra -pedantic $(EXTRA_CXXFLAGS)

# TARGETS is the list of all programs created when we do "make all"
#   (and which should be deleted when we do "make clean")

TARGETS = treeset-test

###############################################################################
# "PHONY" (BUT USEFUL) MAKEFILE TARGETS
###############################################################################


# "make all" brings all programs up-to-date (recursively)
#     and then runs no commands.

all: $(TARGETS)

# "make clean" brings nothing up to date, but always
#      runs commands to delete all created files

clean:
	rm -f $(TARGETS)
	rm -rf *.o

# "make test" brings all the testing programs up-to-date (recursively)
#       and then runs them.

test: treeset-test
	./treeset-test

documentation: doxygen.config
	doxygen doxygen.config

###############################################################################
# CREATING PROGRAMS
###############################################################################

# "make treeset-test" brings the relevant .o files up-to-date (recursively)
#      and then links them.

treeset-test: treeset-test.o gtest-all.o 
	$(CXX) $(CXXFLAGS) -o treeset-test $^

myspell: myspell.o spellchecker.o
	$(CXX) $(CXXFLAGS) -o myspell $^


###############################################################################
# GENERATING OBJECT FILES
###############################################################################

# The .o files depend on the corresponding .cpp file and the .hpp
#      files that C++ code includes.
#      In each case, the command to generate the .o file uses
#      our C++ compiler to compile the .cpp file, with the -c flag.

stringutils.o: stringutils.cpp stringutils.hpp
	$(CXX) $(CXXFLAGS) -c stringutils.cpp

treeset-test.o: treeset-test.cpp treeset.hpp treeset-private.hpp
	$(CXX) $(CXXFLAGS) -c treeset-test.cpp

spellchecker.o: hashset.hpp hashset-private.hpp spellchecker.hpp
	$(CXX) $(CXXFLAGS) -c spellchecker.cpp

# The google test .o file is similar, except that it is
#    named gtest-all.cc instead of gtest-all.cpp
#

gtest-all.o : gtest/gtest-all.cc gtest/gtest.h
	$(CXX) $(CXXFLAGS) -c gtest/gtest-all.cc
