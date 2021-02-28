// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

#include <iostream>

bool isCanonical(unsigned int C[], unsigned int n) {
    if(n < 3) return false;
    bool final = true;

    unsigned limit1 = C[2]+1;
    unsigned limit2 = C[n-2]+C[n-1];
    auto * Stock = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * n));
    auto * usedCoinsGreedy = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * n));
    auto * usedCoinsBF = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * n));

    for(int i = limit1+1; i < limit2; i++) {
        for(int j = 0; j < n; j++) {
            Stock[j] = i/C[j] + 5;
        }
        if(!changeMakingGreedy(C, Stock, n, i, usedCoinsGreedy)) {
            final = false; break;
        }
        if(!changeMakingBF(C, Stock, n, i, usedCoinsBF)) {
            final = false; break;
        }

        if(sumArray(usedCoinsGreedy, n) != sumArray(usedCoinsBF,n)) {
            final = false; break;
        }
    }

    free(Stock);
    free(usedCoinsBF);
    free(usedCoinsGreedy);
    return final;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}