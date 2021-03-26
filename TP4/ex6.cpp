#include "exercises.h"

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    if(n <= 0)
        return 0;

    const size_t size = n;
    int sums[size][size], sum;
    int max_sum = n > 0 ? A[0] : 0;
    sums[0][0] = A[0];
    i = 0, j = 0;

    for(int index = 1; index < n; index++) {
        sum = sums[i][index-1] + A[index];
        sums[i][index] = sum;

        if(sum > max_sum) {
            max_sum = sum;
            j = index;
        }

        sum = A[index];
        sums[index][index] = sum;

        if(sum > max_sum) {
            max_sum = sum;
            i = index;
            j = index;
        }
    }

    return max_sum;
}

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
	// Copy-paste your solution for ex2 of TP1 HERE
	return 0;
}

int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
	// Copy-paste your solution for ex2 of TP3 HERE
	return 0;
}

void testPerformanceMaxSubsequence() {
	// TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    int A5[] = {6, -7, 2, 2, 10, -2, -1, -5, -4};
    unsigned int n5 = 9;
    EXPECT_EQ(maxSubsequenceDP(A5,n5,i,j), 14);
    EXPECT_EQ(i, 2);
    EXPECT_EQ(j, 4);

    int A6[] = {-6, -7, -2, 10, 2, 2, -7, 6, -4};
    unsigned int n6 = 9;
    EXPECT_EQ(maxSubsequenceDP(A6,n6,i,j), 14);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 5);

    testPerformanceMaxSubsequence();
}