#include "exercises.h"
#include <sstream>

std::string calcSum(int sequence[], unsigned long n) {
    const size_t size = n;
    size_t lowest_i;
    int sums[size+1][size]; //size(m,i)
    uint32_t lowest_sum, sum;
    std::stringstream ss;

    for(size_t m = 0; m <= size; m++) {
        lowest_sum = UINT32_MAX;
        lowest_i = 0;

        for(size_t i = 0; i < size - (m - 1); i++) {
            if (m == 0) {
                sums[m][i] = 0;

                continue;
            }

            sum = sums[m][i] = sums[m-1][i] + sequence[i+m-1];

            if(sum < lowest_sum) {
                lowest_sum = sum;
                lowest_i = i;
            }
        }

        if(m > 0) ss << lowest_sum << "," << lowest_i << ";";
    }

    return ss.str();
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	testPerformanceCalcSum();
}