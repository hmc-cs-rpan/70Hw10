/**
 * \file spellchecker.hpp
 *
 * \author Amy Huang, Ricky Pan
 *
 * \brief Provides the spellchecker class.
 */

#ifndef SPELLCHECKER_HPP_INCLUDED
#define SPELLCHECKER_INCLUDED 1

#include <cstddef>
#include <iostream>
#include "treeset.hpp"

class SpellChecker {
public:
    /**
     * \brief Constructor
     *
     * \params filename, a file containing the dictionary
     *
     * \details Populates a TreeSet using the dictionary
     */
    SpellChecker(const std::string& filename);

    SpellChecker() = delete;
    SpellChecker(const SpellChecker&) = delete;
    SpellChecker operator=(const SpellChecker&) = delete;

    /**
     * \brief Prints a list of suggestions for a misspelled input word
     *
     * \param filename, a file containing words
     */
     void spellCheck(std::string& word) const;

     // The dictionary
     TreeSet<std::string> dict_;
};

#endif
