/**
 * \file treeset-set.cpp
 * \authors Amy Huang, Ricky Pan
 *
 * \brief Tests TreeSet functionality.
 */

#include <ostream>
#include <cstddef>

#include "signal.h"
#include "unistd.h"

#include <sstream>
#include <fstream>

#include "treeset.hpp"

template class TreeSet<std::string>;

#include "gtest/gtest.h"

/// Tests basic methods before and after one insert
TEST(stringTestSuite, oneInsertTest)
{
    std::string testStr = "hello";
    TreeSet<std::string> stringSet;

    EXPECT_FALSE(stringSet.exists(testStr));
    EXPECT_EQ(stringSet.size(), 0U);
    EXPECT_EQ(stringSet.height(), -1);

    stringSet.insert(testStr);
    EXPECT_TRUE(stringSet.exists(testStr));
    EXPECT_EQ(stringSet.size(), 1U);
    EXPECT_EQ(stringSet.height(), 0);
}

/// Tests large number of inserts
TEST(stringTestSuite, manyInsertTest)
{
    TreeSet<std::string> stringSet;
    
    std::stringstream ss;
    std::string s;

    // Insert characters
    for (size_t ch = 32; ch < 127; ++ch) {
        ss << (char)ch;
        ss >> s;
        stringSet.insert(s);
    }

    // Check that all the characters have been inserted
    for (size_t ch = 32; ch < 127; ++ch) {
        ss << ch;
        ss >> s;
        EXPECT_TRUE(stringSet.exists(s));
    }

    EXPECT_EQ(stringSet.size(), 95U);
    EXPECT_LT(stringSet.height(), 70);
}

/// Tests insert on strings from smallDict.words
TEST(stringTestSuite, smallDictStringInsertTest)
{
    TreeSet<std::string> stringSet;

    std::string filename = "smalldict.words";
    
    // Open provided file
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        exit(1);
    }

    // Read data from the file, one item per line
    std::string line;
    while(inFile.good()) {
        getline(inFile, line);
        if (inFile.fail())
            break;
        stringSet.insert(line);
    };

    EXPECT_EQ(stringSet.size(), 341U);
    EXPECT_LT(stringSet.height(), 250);
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