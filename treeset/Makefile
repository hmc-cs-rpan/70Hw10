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

TARGETS = stringhash-test hashset-cow-test hashset-test myspell

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
# You should probably use a more realistic number of buckets than 10
#       for stringhash-test, but the exact number is up to you.

test: stringhash-test hashset-cow-test hashset-test
	./stringhash-test 10 /usr/share/dict/web2
	./hashset-cow-test
	./hashset-test

documentation: doxygen.config
	doxygen doxygen.config

###############################################################################
# CREATING PROGRAMS
###############################################################################

# "make stringhash-test" brings the relevant .o files up-to-date (recursively)
#      and then links them.

# In a command run by the makefile, $^ stands for the things the target
#      depends on (in this case, the list stringhash-test.o stringhash.o")
#      This is useful so that we don't have to duplicate this list
#      both in the dependency list and in the linking command, and we
#      don't have to define a STRINGHASH_TEST_OBJS variable that is
#      used only for these two lines.

stringhash-test: stringhash-test.o stringhash.o
	$(CXX) $(CXXFLAGS) -o stringhash-test $^


# "make hashset-cow-test" brings the relevant .o files up-to-date (recursively)
#      and then links them.

hashset-cow-test: hashset-cow-test.o gtest-all.o
	$(CXX) $(CXXFLAGS) -o hashset-cow-test $^

hashset-test: hashset-test.o stringhash.o  gtest-all.o 
	$(CXX) $(CXXFLAGS) -o hashset-test $^

myspell: myspell.o spellchecker.o stringhash.o
	$(CXX) $(CXXFLAGS) -o myspell $^


###############################################################################
# GENERATING OBJECT FILES
###############################################################################

# The .o files depend on the corresponding .cpp file and the .hpp
#      files that C++ code includes.
#      In each case, the command to generate the .o file uses
#      our C++ compiler to compile the .cpp file, with the -c flag.

hashset-cow-test.o: hashset-cow-test.cpp hashset.hpp hashset-private.hpp
	$(CXX) $(CXXFLAGS) -c hashset-cow-test.cpp

stringhash.o: stringhash.cpp stringhash.hpp
	$(CXX) $(CXXFLAGS) -c stringhash.cpp

stringhash-test.o: stringhash-test.cpp stringhash.hpp
	$(CXX) $(CXXFLAGS) -c stringhash-test.cpp

stringutils.o: stringutils.cpp stringutils.hpp
	$(CXX) $(CXXFLAGS) -c stringutils.cpp

hashset-test.o: hashset-test.cpp hashset.hpp hashset-private.hpp
	$(CXX) $(CXXFLAGS) -c hashset-test.cpp

spellchecker.o: hashset.hpp hashset-private.hpp spellchecker.hpp
	$(CXX) $(CXXFLAGS) -c spellchecker.cpp

# The google test .o file is similar, except that it is
#    named gtest-all.cc instead of gtest-all.cpp
#

gtest-all.o : gtest/gtest-all.cc gtest/gtest.h
	$(CXX) $(CXXFLAGS) -c gtest/gtest-all.cc
