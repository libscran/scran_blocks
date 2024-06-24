#include <gtest/gtest.h>
#include "block_weights.hpp"
#include <vector>

TEST(BlockWeights, Variable) {
    EXPECT_EQ(0, scran::block_weights::compute_variable(0, {0, 0}));
    EXPECT_EQ(1, scran::block_weights::compute_variable(1, {0, 0}));

    EXPECT_EQ(0, scran::block_weights::compute_variable(0, {5, 10}));
    EXPECT_EQ(0.2, scran::block_weights::compute_variable(6, {5, 10}));
    EXPECT_EQ(1, scran::block_weights::compute_variable(10, {5, 10}));
    EXPECT_EQ(1, scran::block_weights::compute_variable(15, {5, 10}));
}

TEST(BlockWeights, Compute) {
    std::vector<int> sizes { 0, 10, 100, 1000 };

    {
        std::vector<double> expected { 0, 1, 1, 1 };
        EXPECT_EQ(expected, scran::block_weights::compute(sizes, scran::block_weights::Policy::EQUAL, {}));
    }

    {
        std::vector<double> expected(sizes.begin(), sizes.end());
        EXPECT_EQ(expected, scran::block_weights::compute(sizes, scran::block_weights::Policy::NONE, {}));
    }

    {
        std::vector<double> expected;
        for (auto s : sizes) {
            expected.push_back(scran::block_weights::compute_variable(s, {20, 200}));
        }
        EXPECT_EQ(expected, scran::block_weights::compute(sizes, scran::block_weights::Policy::VARIABLE, {20, 200}));
    }
}
