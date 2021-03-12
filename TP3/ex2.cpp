#include "exercises.h"
#include <iostream>

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if(n == 1) {
        i = 0;
        j = 0;
        return A[0];
    }

    int middle = n / 2;

    int i_first, j_first, i_second, j_second, sum_second, sum_first, best_sum;
    sum_first = best_sum = maxSubsequenceDC(A, middle, i_first, j_first);
    sum_second = maxSubsequenceDC(A+middle, n - middle, i_second, j_second);
    i_second += middle; j_second += middle;

    if(sum_second > best_sum) {
        best_sum = sum_second;
        i = i_second;
        j = j_second;
    } else {
        i = i_first;
        j = j_first;
    }

    int sum = sum_first;

    for(int j_sum = j_first + 1; j_sum <= j_second; j_sum++) {
        sum += A[j_sum];
        if(sum > best_sum) {
            best_sum = sum;
            i = i_first;
            j = j_sum;
        }
    }

    sum = sum_second;

    for(int i_sum = i_second - 1; i_sum >= i_first; i_sum--) {
        sum += A[i_sum];
        if(sum > best_sum) {
            best_sum = sum;
            i = i_sum;
            j = j_second;
        }
    }


	return best_sum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    int A5[] = {6, -7, 2, 2, 10, -2, -1, -5, -4};
    unsigned int n5 = 9;
    EXPECT_EQ(maxSubsequenceDC(A5,n5,i,j), 14);
    EXPECT_EQ(i, 2);
    EXPECT_EQ(j, 4);

    int A6[] = {-6, -7, -2, 10, 2, 2, -7, 6, -4};
    unsigned int n6 = 9;
    EXPECT_EQ(maxSubsequenceDC(A6,n6,i,j), 14);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 5);
}