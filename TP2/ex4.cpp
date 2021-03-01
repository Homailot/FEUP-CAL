#include "exercises.h"

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

static std::vector<Activity> best;

void activitySelection(std::vector<Activity>& A, std::vector<Activity>& chosen) {
    for(auto activityIt = A.begin(); activityIt != A.end(); activityIt++) {
        auto activity = *activityIt;

        if(chosen.empty() || (!activity.overlaps(chosen.back()) && activity.start > chosen.back().finish)) {
            activityIt = A.erase(activityIt);
            chosen.push_back(activity);

            if(chosen.size() > best.size()) {
                best = chosen;
            }

            activitySelection(A, chosen);

            A.insert(activityIt, activity);
            chosen.pop_back();
        }
    }
}

std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A) {
    std::vector<Activity> chosen;

    activitySelection(A, chosen);
    return best;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

TEST(TP2_Ex4, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBacktracking(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}