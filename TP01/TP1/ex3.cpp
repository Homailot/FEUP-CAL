// By: Gonçalo Leão

#include "exercises.h"

//std::vector<std::vector<int>> getCombinations(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned usedCoins[]) {
//    std::vector<std::vector<int>> combinations;
//    std::vector<std::vector<int>> previousCombinations;
//    std::vector<int> newCombination;
//    if(n == 0) return {{}};
//    if (n == 1) {
//        previousCombinations = {{}};
//    } else {
//        previousCombinations = getCombinations(C+1, Stock+1, n-1);
//    }
//
//    for(int j = 0; j < previousCombinations.size(); j++) {
//        for(int i = Stock[0]; i > 0; i--) {
//            newCombination = previousCombinations[j];
//            newCombination.insert(newCombination.begin(), i);
//            combinations.push_back(newCombination);
//        }
//    }
//
//
//    return combinations;
//}

//bool getCombinations(unsigned int C[], unsigned int Stock[], unsigned T, unsigned int n, unsigned sum, unsigned usedCoins[]) {
//    if(n == 0) return false;
//
//    for(int attempt = 0; attempt <= Stock[0]; attempt++) {
//        usedCoins[0] = attempt;
//
//        if(sum + attempt*C[0] == T) return true;
//        else if(n>1 && getCombinations(C+1, Stock+1, T, n-1, sum + attempt*C[0], usedCoins+1)) return true;
//    }
//    usedCoins[0] = 0;
//    return false;
//}

unsigned sumC(unsigned int C[], unsigned n, unsigned int usedCoins[]) {
    unsigned sum = 0;

    for(int i = 0; i < n; i++) {
        sum += usedCoins[i] * C[i];
    }

    return sum;
}

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int pos;

    for(int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }

    while(true) {
        pos = (int)n-1;

        for(int i = 0; i <= Stock[pos]; i++) {
            usedCoins[pos] = i;
            if(sumC(C, n, usedCoins) == T) {
                return true;
            }
        }

        while(pos >= 0 && usedCoins[pos] == Stock[pos]) {
            usedCoins[pos] = 0;
            pos--;
        }
        if(pos == -1) break;
        usedCoins[pos]++;
    }

    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}