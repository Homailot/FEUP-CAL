#include "exercises.h"
#include <iostream>

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    const size_t coins = n + 1;
    const size_t changes = T + 1;
    const int err = T+1;
    int coin_index;
    int candidate_a, candidate_b;
    int min_coins[coins][changes], last_coin[coins][changes];

    for(int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }


    for(int max_coin = 0; max_coin <= n; max_coin++) {
        for(int change = 0; change <= T; change++) {
            if(change == 0) {
                min_coins[max_coin][change] = 0;
                last_coin[max_coin][change] = err;

                continue;
            } else if(max_coin == 0) {
                min_coins[max_coin][change] = err;
                last_coin[max_coin][change] = err;

                continue;
            }

            coin_index = max_coin - 1;

            if(change - (int)C[coin_index] < 0) candidate_a = err;
            else candidate_a = min_coins[max_coin][change - C[coin_index]] + 1;

            candidate_b = min_coins[max_coin - 1][change];

            if(candidate_a != err && ((candidate_a < candidate_b) || (candidate_b == err))) {
                min_coins[max_coin][change] = candidate_a;
                last_coin[max_coin][change] = coin_index;
            } else {
                min_coins[max_coin][change] = candidate_b;
                last_coin[max_coin][change] = last_coin[max_coin - 1][change];
            }
        }
    }

    if(min_coins[n][T] == err) return false;

    int change = T;
    int coin_used;
    while(change > 0) {
        coin_used = last_coin[n][change];

        usedCoins[coin_used]++;
        change -= C[coin_used];
    }

	return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}