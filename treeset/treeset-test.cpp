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

/// Tests something
TEST(stringTestSuite, oneInsertTest)
{
	// Hello
}