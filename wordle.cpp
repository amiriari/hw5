#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void buildWords(string& partial, int index, string floating, const set<string>& dict, set<string>& finalResults);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    set<string> finalResults;
    string partial = in;
    buildWords(partial, 0, floating, dict, finalResults);
    return finalResults;

}

// Define any helper functions here

void buildWords(string& partial, int index, string floating, const set<string>& dict, set<string>& finalResults)
{
    if(index == partial.size()) {
        // Base case: Full word created
        if(dict.find(partial) != dict.end() && floating.empty()) {
            finalResults.insert(partial);
        }
        return;
    }

    if(partial[index] != '-') {
        buildWords(partial, index + 1, floating, dict, finalResults);
    }
    else {
        set<char> tried;

        for(int i = 0; i < floating.size(); ++i) {
            char c = floating[i];
            if(tried.find(c) == tried.end()) {
                tried.insert(c);
                partial[index] = c;
                string newFloating = floating;
                newFloating.erase(newFloating.begin() + i);
                buildWords(partial, index + 1, newFloating, dict, finalResults);
                partial[index] = '-'; 
            }
        }

        for(char c = 'a'; c <= 'z'; ++c) {
            if(tried.find(c) == tried.end()) {
                partial[index] = c;
                buildWords(partial, index + 1, floating, dict, finalResults);
                partial[index] = '-'; 
            }
        }
    }
}
