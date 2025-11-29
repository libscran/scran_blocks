#ifndef SCRAN_BLOCKS_PARALLEL_QUANTILES_HPP
#define SCRAN_BLOCKS_PARALLEL_QUANTILES_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <vector>
#include <cstddef>
#include <cmath>

#include "utils.hpp"

#include "sanisizer/sanisizer.hpp"

/**
 * @file parallel_quantiles.hpp
 * @brief Quantile of parallel elements across arrays.
 */

namespace scran_blocks {

/**
 * @brief Calculate a single quantile from a container.
 *
 * @tparam Output_ Floating-point type of the output quantile.
 * @tparam Size_ Integer type of the number of elements.
 *
 * This class should be constructed once, given the number of elements and the desired probability.
 * It can then applied across any number of containers of size equal to the pre-specified number of elements. 
 * The quantile is type 7, consistent with the default in R's `quantile` function. 
 */
template<typename Output_, typename Size_>
class SingleQuantile {
public:
    /**
     * @param n Number of elements in the container.
     * @param quantile Quantile to compute, in \f$[0, 1]\f$.
     */
    SingleQuantile(Size_ n, double quantile) {
        const double frac = (n - 1) * quantile;
        const double base = std::floor(frac);
        my_lower = base;
        my_upper_fraction = frac - base;
        my_lower_fraction = 1 - my_upper_fraction;
        my_skip_upper = my_upper_fraction == 0;
    }

private:
    Size_ my_lower;
    double my_upper_fraction;
    double my_lower_fraction;
    bool my_skip_upper;

public:
    /**
     * @tparam Iterator_ Random-access writeable iterator to a container.
     * @param begin Start of the container.
     * @param end End of the container.
     * @return Quantile for the sequence of elements in `[begin, end)`.
     *
     * The range `[begin, end)` should have length equal to `n`, and should not contain any NaN values.
     */
    template<typename Iterator_>
    Output_ operator()(Iterator_ begin, Iterator_ end) const {
        auto target = begin + my_lower;
        std::nth_element(begin, target, end);

        // Avoid looking at target+1 if don't need it - in particular, we'd get a out-of-bounds access if quantile = 1.
        if (my_skip_upper) {
            return *target;
        } else {
            return *target * my_lower_fraction + *(target + 1) * my_upper_fraction;
        }
    }
};

/**
 * Compute the quantile for parallel elements across multiple arrays.
 * This can be used as an alternative to `parallel_means()` to summarize statistics across blocks, e.g., by computing the median with `quantile = 0.5`.
 * The quantile is type 7, consistent with the default in R's `quantile` function. 
 *
 * @tparam Stat_ Type of the input statistic, typically floating point.
 * @tparam Output_ Floating-point type of the output quantile.
 *
 * @param n Length of each array.
 * @param[in] in Vector of pointers to input arrays of length `n`.
 * @param quantile Quantile to compute, in \f$[0, 1]\f$.
 * @param[out] out Pointer to an output array of length `n`.
 * On completion, `out[i]` is filled with the quantile of `(in.front()[i], in[1][i], ..., in.back()[i])`.
 * @param skip_nan Whether to check for NaNs.
 * If `true`, NaNs are removed before computing the quantile.
 * If `false`, it is assumed that no NaNs are present.
 */
template<typename Stat_, typename Output_>
void parallel_quantiles(const std::size_t n, const std::vector<Stat_*>& in, const double quantile, Output_* const out, const bool skip_nan) {
    const auto nblocks = in.size();
    if (nblocks == 0) {
        std::fill_n(out, n, std::numeric_limits<Output_>::quiet_NaN());
        return;
    } else if (nblocks == 1) {
        std::copy_n(in[0], n, out);
        return;
    }

    std::vector<Stat_> tmp_buffer;
    tmp_buffer.reserve(nblocks);

    if (skip_nan) {
        for (std::size_t g = 0; g < n; ++g) {
            tmp_buffer.clear();
            for (decltype(I(nblocks)) b = 0; b < nblocks; ++b) {
                const auto val = in[b][g];
                if (!std::isnan(val)) {
                    tmp_buffer.push_back(val);
                }
            }

            const auto actual_nblocks = tmp_buffer.size();
            if (actual_nblocks == 0) {
                out[g] = std::numeric_limits<Output_>::quiet_NaN();
            } else if (actual_nblocks == 1) {
                out[g] = tmp_buffer.front(); 
            } else {
                SingleQuantile<Output_, decltype(I(actual_nblocks))> calc(actual_nblocks, quantile);
                out[g] = calc(tmp_buffer.begin(), tmp_buffer.end());
            }
        }

    } else {
        SingleQuantile<Output_, decltype(I(nblocks))> calc(nblocks, quantile);
        for (std::size_t g = 0; g < n; ++g) {
            tmp_buffer.clear();
            for (decltype(I(nblocks)) b = 0; b < nblocks; ++b) {
                tmp_buffer.push_back(in[b][g]);
            }
            out[g] = calc(tmp_buffer.begin(), tmp_buffer.end());
        }
    }
}

/**
 * Overload of `parallel_quantiles()` that allocates memory for the output array.
 *
 * @tparam Output_ Floating-point type of the output quantile.
 * @tparam Stat_ Type of the input statistic, typically floating point.
 *
 * @param n Length of each array.
 * @param[in] in Vector of pointers to input arrays of length `n`.
 * @param quantile Quantile to compute, in \f$[0, 1]\f$.
 * @param skip_nan Whether to check for NaNs.
 * If `true`, NaNs are removed before computing the quantile.
 * If `false`, it is assumed that no NaNs are present.
 *
 * @return Vector of length `n`, where the `i`-th element is the quantile of `(in.front()[i], in[1][i], ..., in.back()[i])`.
 */
template<typename Output_ = double, typename Stat_>
std::vector<Output_> parallel_quantiles(const std::size_t n, const std::vector<Stat_*>& in, const double quantile, const bool skip_nan) {
    auto out = sanisizer::create<std::vector<Output_> >(n);
    parallel_quantiles(n, in, quantile, out.data(), skip_nan);
    return out;
}

}

#endif

