#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> computePrefix(std::string pattern) {
    std::vector<int> prefix(pattern.size());

    size_t patternSize = pattern.size();
    prefix[0] = 0;
    size_t j = 0; // j = k+1

    for(size_t i = 1; i < patternSize; i++) {
        while(j > 0 && pattern[j] != pattern[i]) {
            j = prefix[j-1];
        }

        if(pattern[j] == pattern[i]) {
            j++;
        }

        prefix[i] = j;
    }

    return prefix;
}

int kmpMatcher(std::string text, std::string pattern) {
    computePrefix(pattern);

    std::vector<int> prefix = computePrefix(pattern);
    int numMatch = 0, matches = 0;

    for(size_t i = 0; i < text.size(); i++) {
        while(numMatch > 0 && pattern[numMatch] != text[i]) {
            numMatch = prefix[numMatch - 1];
        }

        if(pattern[numMatch] == text[i]) {
            numMatch++;
        }

        if(numMatch == pattern.size()) {
            matches++;
            numMatch = prefix[numMatch - 1];
        }
    }

    return matches;
}

int numStringMatching(std::string filename, std::string toSearch) {
    std::string text;
    int matches = 0;

    std::ifstream file(filename);

    while(getline(file, text)) {
        matches += kmpMatcher(text, toSearch);
    }

    return matches;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}