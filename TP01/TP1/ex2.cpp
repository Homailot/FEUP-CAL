// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    if(n < 0) return 0;

    int curSum, maxSum = A[0];
    i = 0; j = 0;

    for(int cur_i = 0; cur_i < n; cur_i++) {
        curSum = 0;

        for(int cur_j = cur_i; cur_j < n; cur_j++) {
            curSum += A[cur_j];

            if(curSum > maxSum) {
                maxSum = curSum;
                i = cur_i; j = cur_j;
            }
        }
    }

    return maxSum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}