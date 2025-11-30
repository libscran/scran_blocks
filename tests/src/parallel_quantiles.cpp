#include <gtest/gtest.h>
#include "scran_blocks/parallel_quantiles.hpp"
#include "scran_tests/scran_tests.hpp"
#include <vector>

static int full_of_nans(const std::vector<double>& vec) {
    int nan_count = 0;
    for (auto x : vec) {
        nan_count += std::isnan(x);
    }
    return nan_count;
}

TEST(SingleQuantile, Simple) {
    std::vector<double> original { 0.7, 8.2, 2.3, 1.5, 8.8, 0.5 };
    const std::size_t n = static_cast<std::size_t>(original.size());
    scran_tests::CompareAlmostEqualParameters params;

    // Make a copy to preserve the original unordered state, otherwise the vector ends up sorted and the test is too easy. 
    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 0.5, params);
    }

    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0.1)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 0.6, params);
    }

    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0.25)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 0.9, params);
    }

    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0.5)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 1.9, params);
    }

    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0.75)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 6.725, params);
    }

    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0.8)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 8.2, params);
    }

    {
        auto values = original;
        double val = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 1)(values.begin(), values.end());
        scran_tests::compare_almost_equal(val, 8.8, params);
    }

    // Works with some lower precisions too.
    params.relative_tolerance = 1e-5;
    {
        auto values = original;
        auto fval = scran_blocks::SingleQuantile<float, decltype(values.begin())>(n, 1)(values.begin(), values.end());
        scran_tests::compare_almost_equal(static_cast<double>(fval), 8.8, params);
    }

    {
        std::vector<float> fvalues(original.begin(), original.end());
        auto val = scran_blocks::SingleQuantile<double, decltype(fvalues.begin())>(n, 1)(fvalues.begin(), fvalues.end());
        scran_tests::compare_almost_equal(val, 8.8, params);
    }
}

TEST(SingleQuantile, Complex) {
    const std::size_t n = 54; // n - 1 should be prime so that we can use EXPECT_LT, GT, without worrying about float equality.
    auto original = scran_tests::simulate_vector(n, {});

    for (int val = 1; val < 100; ++val) {
        const double prop = static_cast<double>(val)/100.0;
        auto values = original;
        const double Q = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, prop)(values.begin(), values.end());

        double sum = 0;
        for (auto x : original) {
            sum += (x <= Q);
        }

        EXPECT_GT(prop, (sum-1)/(n-1));
        EXPECT_LT(prop, sum/(n-1));
    }

    {
        auto values = original;
        const double Q = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 0)(values.begin(), values.end());
        EXPECT_EQ(Q, *std::min_element(original.begin(), original.end()));
    }

    {
        auto values = original;
        const double Q = scran_blocks::SingleQuantile<double, decltype(values.begin())>(n, 1)(values.begin(), values.end());
        EXPECT_EQ(Q, *std::max_element(original.begin(), original.end()));
    }
}

TEST(SingleQuantileVariable, Simple) {
    std::vector<double> original { 0, 1, 2, 3, 4, 5 };
    scran_blocks::SingleQuantileVariable<double, decltype(original.begin())> calc(original.size(), 0.5);

    {
        auto values = original;
        auto Q = calc(values.begin(), values.begin());
        EXPECT_TRUE(std::isnan(Q));
    }

    {
        auto values = original;
        auto Q = calc(values.begin(), values.begin() + 1);
        EXPECT_EQ(Q, 0);
    }

    {
        auto values = original;
        auto Q = calc(values.begin(), values.begin() + 2);
        scran_tests::compare_almost_equal(Q, 0.5, scran_tests::CompareAlmostEqualParameters());
    }

    {
        auto values = original;
        auto Q = calc(values.begin(), values.end());
        scran_tests::compare_almost_equal(Q, 2.5, scran_tests::CompareAlmostEqualParameters());
    }

    // Re-using the cached calculator.
    {
        auto values = original;
        auto Q = calc(values.begin() + 2, values.begin() + 4);
        scran_tests::compare_almost_equal(Q, 2.5, scran_tests::CompareAlmostEqualParameters());
    }
}

TEST(ParallelQuantiles, Simple) {
    std::vector<std::vector<double> > stuff {
        std::vector<double>{1, 2, 3, 4, 5},
        std::vector<double>{2, 1, 2, 6, 8},
        std::vector<double>{3, 7, 3, 3, 2}
    };

    auto out = scran_blocks::parallel_quantiles(5, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, 0.5, false);
    std::vector<double> ref {2, 2, 3, 4, 5};
    scran_tests::compare_almost_equal_containers(ref, out, {});

    auto nona = scran_blocks::parallel_quantiles(5, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, 0.5, true);
    EXPECT_EQ(out, nona);

    // Optimization when there's just one, or none.
    auto out_opt = scran_blocks::parallel_quantiles(5, std::vector<double*>{stuff[0].data()}, 0.5, false);
    EXPECT_EQ(out_opt, stuff[0]);

    auto out_opt2 = scran_blocks::parallel_quantiles(5, std::vector<double*>{}, 0.5, false);
    EXPECT_EQ(full_of_nans(out_opt2), out_opt2.size());
}

TEST(ParallelQuantiles, CheckNaNs) {
    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
    std::vector<std::vector<double> > stuff {
        std::vector<double>{1, nan,   3,   4, nan, 8},
        std::vector<double>{2, nan,   2, nan, nan, 5},
        std::vector<double>{3,   7, nan,   3, nan, 4}
    };

    auto out = scran_blocks::parallel_quantiles(6, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, 0.5, true);
    std::vector<double> ref {2, 7, 2.5, 3.5, nan, 5.0};
    scran_tests::compare_almost_equal_containers(ref, out, {});
}
