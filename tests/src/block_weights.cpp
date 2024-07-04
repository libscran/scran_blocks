#include <gtest/gtest.h>
#include "block_weights.hpp"
#include <vector>

TEST(BlockWeights, Variable) {
    scran::block_weights::VariableParameters params;
    params.lower_bound = 0;
    params.upper_bound = 0;
    EXPECT_EQ(0, scran::block_weights::compute_variable(0, params));
    EXPECT_EQ(1, scran::block_weights::compute_variable(1, params));

    params.lower_bound = 5;
    params.upper_bound = 10;
    EXPECT_EQ(0, scran::block_weights::compute_variable(0, params));
    EXPECT_EQ(0.2, scran::block_weights::compute_variable(6, params));
    EXPECT_EQ(1, scran::block_weights::compute_variable(10, params));
    EXPECT_EQ(1, scran::block_weights::compute_variable(15, params));
}

TEST(BlockWeights, Compute) {
    std::vector<int> sizes { 0, 10, 100, 1000 };
    scran::block_weights::VariableParameters params;

    {
        std::vector<double> expected { 0, 1, 1, 1 };
        EXPECT_EQ(expected, scran::block_weights::compute(sizes, scran::block_weights::Policy::EQUAL, params));
    }

    {
        std::vector<double> expected(sizes.begin(), sizes.end());
        EXPECT_EQ(expected, scran::block_weights::compute(sizes, scran::block_weights::Policy::NONE, params));
    }

    {
        scran::block_weights::VariableParameters params;
        params.lower_bound = 20;
        params.upper_bound = 200;

        std::vector<double> expected;
        for (auto s : sizes) {
            expected.push_back(scran::block_weights::compute_variable(s, params));
        }

        EXPECT_EQ(expected, scran::block_weights::compute(sizes, scran::block_weights::Policy::VARIABLE, params));
    }
}
