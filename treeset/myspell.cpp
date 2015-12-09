/**
 * \file myspell.cpp
 *
 * \author CS 70 Provided Code, Amy Huang, Ricky Pan
 *
 * \brief Implements the UI for the spelling checker
 */


#include "treeset.hpp"
#include "spellchecker.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <forward_list>

using namespace std;

/**
 * \brief Process input from cin and compare against the dictionary.
 *        If the word is not found and has not been seen before, spelling
 *        corrections are output to cout.
 *
 * \param dictfile Name of dictionary file.
 *
 * \param debug    Boolean corresponding to the -d flag
 */
void spellcheck(const string& dictfile, bool debug)
{
    string word;
    SpellChecker oxford(dictfile);

    // Keep track of checked words, to avoid printing repeated misspellings
    forward_list<string> inputs = forward_list<string>();

    if (debug == true) {
        oxford.dict_.showStatistics(cerr);
    }
    while (cin >> word) {

        // Convert word to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Delete any punctuation at the last character
        if (!isalpha(word.back())) {
            word.pop_back();
        }

        // If word has not already been spellchecked, spellcheck it
        if (find(inputs.begin(), inputs.end(), word) == inputs.end()) {
            oxford.spellCheck(word);
        }
        // Add word to list of spellchecked words
        inputs.push_front(word);
    }
}

/// Main function, processes inputs and runs spellcheck
int main(int argc, const char** argv)
{
    bool debug = false;

    // Process command-line options
    --argc; // Skip past 0th arg (program name)
    ++argv;

    if (argc == 2 && *argv == string("-d")) {
        debug = true;
        --argc;
        ++argv;
    }

    if (argc != 1) {
        cerr << "Usage: ./myspell [-d] dict" << endl;
        exit(2);
    }

    // Check that spelling!
    try {
        spellcheck(argv[0], debug);
    } catch (std::runtime_error err) {
        cerr << err.what() << endl;
        return 1;
    }

    return 0;
}
