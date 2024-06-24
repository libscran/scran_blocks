#ifndef SCRAN_BLOCK_WEIGHTS_HPP
#define SCRAN_BLOCK_WEIGHTS_HPP

/**
 * @file block_weights.hpp
 * @brief Calculation of per-block weights.
 */

namespace scran {

/**
 * @namespace scran::block_weights
 * @brief Calculation of per-block weights.
 */
namespace block_weights {

/**
 * Policy to use for weighting blocks based on their size, i.e., the number of cells in each block.
 * This controls the calculation of weighted averages across blocks.
 *
 * - `NONE`: no weighting is performed.
 *   Larger blocks will contribute more to the weighted average. 
 * - `EQUAL`: each block receives equal weight, regardless of its size.
 *   Equivalent to averaging across blocks without weights.
 * - `VARIABLE`: each batch is weighted using the logic in `compute_variable()`.
 *   This penalizes small blocks with unreliable statistics while equally weighting all large blocks.
 */
enum class Policy : char { NONE, VARIABLE, EQUAL };

/**
 * @brief Parameters for `compute_variable()`.
 */
struct VariableParameters {
    /**
     * @param l Lower bound for the block weight calculation, should be non-negative.
     * @param u Upper bound for the block weight calculation, should be not less than `l`.
     * This should be greater than `l`.
     */
    constexpr VariableParameters(double l = 0, double u = 1000) : upper_bound(u), lower_bound(l) {}

    /**
     * Lower bound for the block weight calculation.
     */
    double lower_bound;

    /**
     * Upper bound for the block weight calculation.
     */
    double upper_bound;
};

/**
 * Weight each block of cells for use in computing a weighted average across blocks.
 * The weight for each block is calcualted from the size of that block.
 *
 * - If the block is smaller than some lower bound, it has zero weight.
 * - If the block is greater than some upper bound, it has weight of 1.
 * - Otherwise, the block has weight proportional to its size, increasing linearly from 0 to 1 between the two bounds.
 *
 * Blocks that are "large enough" are considered to be equally trustworthy and receive the same weight, ensuring that each block contributes equally to the weighted average.
 * By comparison, very small blocks receive lower weight as their statistics are generally less stable.
 * If both `cap` and `block_size` are zero, the weight is also set to zero.
 *
 * @param s Size of the block, in terms of the number of cells in that block.
 * @param params Parameters for the weight calculation, consisting of the lower and upper bounds.
 *
 * @return Weight of the block, to use for computing a weighted average across blocks. 
 */
inline double compute_variable(double s, const VariableParameters& params) {
    if (s < params.lower_bound || s == 0) {
        return 0;
    }

    if (s > params.upper_bound) {
        return 1;
    }

    return (s - params.lower_bound) / (params.upper_bound - params.lower_bound);
}

/**
 * Compute block weights for multiple blocks based on their size and the weighting policy.
 * For variable weights, this function will call `compute_variable()` for each block.
 *
 * @tparam Size_ Numeric type for the block size.
 *
 * @param sizes Vector of block sizes.
 * @param policy Policy for weighting blocks of different sizes.
 * @param variable Parameters for the variable block weights.
 *
 * @return Vector of block weights.
 */
template<typename Size_>
std::vector<double> compute(const std::vector<Size_>& sizes, Policy policy, const VariableParameters& variable) {
    size_t nblocks = sizes.size();
    std::vector<double> weights;
    weights.reserve(nblocks);

    if (policy == Policy::NONE) {
        weights.insert(weights.end(), sizes.begin(), sizes.end());
    } else if (policy == Policy::EQUAL) {
        for (auto s : sizes) {
            weights.push_back(s > 0);
        }
    } else {
        for (auto s : sizes) {
            weights.push_back(compute_variable(s, variable));
        }
    }

    return weights;
}

}

}

#endif
