#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
    if(k == n || k <= 1) {
        return 1;
    }

    return s_recursive(n-1, k-1) + k*s_recursive(n-1, k);
}

unsigned long b_recursive(unsigned int n) {
    unsigned long sum = 0;
    for(int k = 1; k <= n; k++) {
        sum += s_recursive(n, k);
    }
    return sum;
}

unsigned long s_dynamic_ineff(unsigned int n, unsigned int k) {
    static unsigned long combinations[100][100];

    if(combinations[n][k] != 0) return combinations[n][k];

    if(k == n || k <= 1) {
        combinations[n][k] = 1;
        return 1;
    }

    unsigned long solution = s_dynamic_ineff(n-1, k-1) + k*s_dynamic_ineff(n-1, k);
    combinations[n][k] = solution;

    return solution;
}

unsigned long b_dynamic_ineff(unsigned int n) {
    static unsigned long combinations[100];

    if(combinations[n] != 0) return combinations[n];
    unsigned  long sum = 0;

    for(size_t k = 1; k <= n; k++)
    {
        sum += s_dynamic_ineff(n, k);
    }
    combinations[n] = sum;

    return sum;
}

unsigned long s_dynamic(unsigned int n, unsigned int k) {
    const size_t max_j = n-k;
    unsigned long combinations[max_j + 1];

    for(size_t j = 0; j <= max_j; j++) {
        combinations[j] = 1;
    }

    for(size_t i = 1; i < k; i++) {
        for(size_t j = 1; j <=max_j; j++) {
            combinations[j] += (i+1)*combinations[j-1];
        }
    }

    return combinations[max_j];
}

unsigned long b_dynamic(unsigned int n) {
    const size_t max_j = n - 1;
    unsigned long combinations[max_j + 1];
    unsigned long sum = 0;

    for(size_t j = 0; j <= max_j; j++) {
        combinations[j] = 1;
    }
    sum += combinations[max_j];

    for(size_t i = 1; i<=max_j; i++) {
        for(size_t j = 1; j<=max_j-i; j++) {
            combinations[j] += (i+1)*combinations[j-1];
        }
        sum += combinations[max_j - i];
    }

    return sum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic_ineff(3,3));
    EXPECT_EQ(3025,s_dynamic_ineff(9,3));
    EXPECT_EQ(22827,s_dynamic_ineff(10,6));

    EXPECT_EQ(5,b_dynamic_ineff(3));
    EXPECT_EQ(203,b_dynamic_ineff(6));
    EXPECT_EQ(1382958545,b_dynamic_ineff(15));

    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));

}