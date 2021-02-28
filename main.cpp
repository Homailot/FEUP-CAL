#include <iostream>
#include "gtest/gtest.h"
#include <time.h>

int main(int argc, char **argv) {
    srand(time(NULL));

    std::cout << "Running all tests..." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
