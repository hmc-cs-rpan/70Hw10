/**
 * \file treeset-cow-test.cpp
 * \author CS 70 Provided Code, Amy Huang, Ricky Pan
 *
 * \brief Tests a treeset to ensure that it is properly generic and doesn't
 *        contain any hidden dependencies on being a tree of strings.
 *        Does not extensively test TreeSet functionality.
 */


/*****************************************************
 * Compatability Tests
 *
 *      Test for any hidden dependencies of TreeSet on
 *      functions of the template type or included
 *      files.
 * ***************************************************/

#include "treeset.hpp"

#include <ostream> // For std::ostream
#include <cstddef> // For size_t

#include "signal.h" // For signal
#include "unistd.h" // For alarm


/**
 * \class Cow
 * \brief
 *   Test class which implements the bare minimum to be usable with a TreeSet.
 * \remarks
 *   As this class is very brief and intended purely for testing
 *   purposes, we keep it completely contained within this file. Doing
 *   so on production level code is problematic.
 */
class Cow {

public:
    /// Non-default constructor.
    explicit Cow(size_t numHats);

private:
    size_t numHats_;   ///< How many hats does our Cow have?

    // Give external functions friend access
    friend std::ostream& operator<<(std::ostream& out, const Cow& printMe);
    friend bool operator<(const Cow& lhs, const Cow& rhs);
};

/// We can simulate <, >, and == using just the < operator
bool operator<(const Cow& lhs, const Cow& rhs) 
{
    return lhs.numHats_ < rhs.numHats_;
}


// As an extra, we define an output operator for the Cow type.
//
// NOTE: Cow isn't *required* to have an output operator, but it is reasonable
// for the tree to have a (non-required) debugging function that prints
// out the tree.  To *use* such a function Cows need to have printing
// defined.

/// Output a Cow in visual form
std::ostream& operator<<(std::ostream& out, const Cow& printMe)
{
    for (size_t i = 0; i < printMe.numHats_; ++i)
        out << "        _====_\n";

    out << "         (__)\n"    // Shamelessly taken from Debian's (& Ubuntu's)
        << "         (oo)\n"    //    apt-get moo
        << "   /------\\/ \n"   // (apt has "super cow" powers)
        << "  / |    ||  \n"
        << " *  /\\---/\\  \n"
        << "    ~~   ~~  \n";
    return out;
}

Cow::Cow(size_t numHats)
    : numHats_(numHats)
{
    // Nothing (else) to do.
}

// Explicitly instantiate the entire templated class

template class TreeSet<Cow>;

/*****************************************************
 * Functionality Tests
 *
 *      Functionality tests for TreeSet
 * ***************************************************/

#include "gtest/gtest.h"

/// Test insert and exists for cows
TEST(cowTestSuite, basicTests)
{
    Cow mabel(3);
    TreeSet<Cow> cowSet;

    EXPECT_FALSE(cowSet.exists(mabel));
    cowSet.insert(mabel);
    EXPECT_TRUE(cowSet.exists(mabel));

}

/****************************
 * Boilerplate main function
 * **************************/

// Called if the test runs too long.
static void timeout_handler(int)
{
    // We go super-low-level here, because we can't trust anything in
    // the C/C++ library to really be working right.
    write(STDERR_FILENO, "Timeout occurred!\n", 18);
    abort();
}

/// Run tests
int main(int argc, char** argv)
{
    // Initalize testing environment
    ::testing::InitGoogleTest(&argc, argv);

    signal(SIGALRM, timeout_handler);   // Call this when the timer expires
    alarm(10);                          // set the timer at 10 seconds
    return RUN_ALL_TESTS();
}