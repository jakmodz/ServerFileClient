#pragma once
#include <sstream> 
#include <vector>
#include <string>


std::vector<std::string> GetWordsFromString(std::string& input)
{
    std::vector<std::string> words;

    std::istringstream stream(input);
    std::string word;

    while (stream >> word) 
    {
        words.push_back(word);  
    }
    return words;
}