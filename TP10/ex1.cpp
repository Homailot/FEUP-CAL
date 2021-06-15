#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> computePrefix(std::string pattern) {
    std::vector<int> pi(pattern.size());

    size_t patternSize = pattern.size();
    pi[0] = 0;
    int j = 0;

    for(size_t i = 1; i < patternSize; i++) {
        while(j > 0 && pattern[j] != pattern[i]) {
            j = pi[j-1];
        }
        if(pattern[j] == pattern[i]) j++;
        pi[i] = j;
    }

    return pi;
}

int kmpMatcher(std::string text, std::string pattern) {
    computePrefix(pattern);

    std::vector<int> pi = computePrefix(pattern);
    int numMatch = 0, matches = 0;

    for(char ch : text) {
        while(numMatch > 0 && pattern[numMatch] != ch) {
            numMatch = pi[numMatch - 1]; // character does not match
        }
        if(pattern[numMatch] == ch) {
            numMatch++; // character matches
        }
        if(numMatch == pattern.size()) {
            matches++;
            numMatch = pi[numMatch - 1];
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