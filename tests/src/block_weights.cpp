#include <gtest/gtest.h>
#include "scran_blocks/block_weights.hpp"
#include <vector>

TEST(BlockWeights, Variable) {
    scran_blocks::VariableWeightParameters params;
    params.lower_bound = 0;
    params.upper_bound = 0;
    EXPECT_EQ(0, scran_blocks::compute_variable_weight(0, params));
    EXPECT_EQ(1, scran_blocks::compute_variable_weight(1, params));

    params.lower_bound = 5;
    params.upper_bound = 10;
    EXPECT_EQ(0, scran_blocks::compute_variable_weight(0, params));
    EXPECT_EQ(0.2, scran_blocks::compute_variable_weight(6, params));
    EXPECT_EQ(1, scran_blocks::compute_variable_weight(10, params));
    EXPECT_EQ(1, scran_blocks::compute_variable_weight(15, params));
}

TEST(BlockWeights, Compute) {
    std::vector<int> sizes { 0, 10, 100, 1000 };
    scran_blocks::VariableWeightParameters params;

    {
        std::vector<double> expected { 0, 1, 1, 1 };
        EXPECT_EQ(expected, scran_blocks::compute_weights(sizes, scran_blocks::WeightPolicy::EQUAL, params));
    }

    {
        std::vector<double> expected(sizes.begin(), sizes.end());
        EXPECT_EQ(expected, scran_blocks::compute_weights(sizes, scran_blocks::WeightPolicy::NONE, params));
        EXPECT_EQ(expected, scran_blocks::compute_weights(sizes, scran_blocks::WeightPolicy::SIZE, params));
    }

    {
        scran_blocks::VariableWeightParameters params;
        params.lower_bound = 20;
        params.upper_bound = 200;

        std::vector<double> expected;
        for (auto s : sizes) {
            expected.push_back(scran_blocks::compute_variable_weight(s, params));
        }

        EXPECT_EQ(expected, scran_blocks::compute_weights(sizes, scran_blocks::WeightPolicy::VARIABLE, params));
    }
}
