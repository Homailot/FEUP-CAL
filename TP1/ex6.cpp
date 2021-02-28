// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>
#include <iostream>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(const std::vector<Activity>& A) {
    std::vector<Activity> res = A;

    std::sort(res.begin(), res.end());

    unsigned i = 0;
    while(i < res.size()-1) {
        if(
                (res[i].start > res[i+1].start && res[i].start < res[i+1].finish) ||
                (res[i].start == res[i+1].start) ||
                (res[i].finish > res[i+1].start))
            res.erase(res.begin()+i+1);
        else {
            i++;
        }
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(earliestFinishScheduling(A),  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}