/**
 * \file spellchecker.cpp
 * \authors Ricky Pan, Amy Huang
 *
 * \brief Spell checker for strings
 */

#include "spellchecker.hpp"
#include <cstddef>
#include <ostream>
#include <sstream>
#include <fstream>

using namespace std;


SpellChecker::SpellChecker(const std::string& filename)
{
    // Open provided file
    ifstream inputStream(filename);
    if (!inputStream) {
        cerr << "Couldn't open file: " << filename << endl;
        exit(1);
    }

    // Read data from the file, one item per line, insert each word into dict
    string line;
    while(inputStream.good()) {
        getline(inputStream, line);
        if (inputStream.fail())
            break;

        dict_.insert(line);
    };
}

void SpellChecker::spellCheck(std::string& word) const
{
    string letter;

    // Convert to lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    if (!dict_.exists(word)) {

        cerr << word << ": ";

        // Check if nearby words exist, by replacing each letter with 
        // all possible letters
        for (size_t i = 0; i < word.size(); ++i) {
            string currWord = word;

            // Loop through ASCII values for the letters a-z
            for(size_t ch = 97; ch < 123; ++ch) {
                stringstream ss;
                ss << (char)ch;
                ss >> letter;

                currWord.replace(i, 1, letter);

                // Print the dictionary suggestion
                if (dict_.exists(currWord)) {
                    cerr << currWord << " ";
                }
            }
        }
        cerr << endl;
    }  
}
