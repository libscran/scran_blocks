#include <gtest/gtest.h>
#include "scran_blocks/parallel_means.hpp"
#include "scran_tests/scran_tests.hpp"
#include <vector>

static int full_of_nans(const std::vector<double>& vec) {
    int nan_count = 0;
    for (auto x : vec) {
        nan_count += std::isnan(x);
    }
    return nan_count;
}

TEST(ParallelMeans, Simple) {
    std::vector<std::vector<double> > stuff {
        std::vector<double>{1, 2, 3, 4, 5},
        std::vector<double>{2, 1, 2, 6, 8},
        std::vector<double>{3, 7, 3, 3, 2}
    };

    auto out = scran_blocks::parallel_means(5, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, false);
    std::vector<double> ref {2, 10.0/3, 8.0/3, 13/3.0, 5.0};
    scran_tests::compare_almost_equal(ref, out);

    // Optimization when there's just one, or none.
    auto out_opt = scran_blocks::parallel_means(5, std::vector<double*>{stuff[0].data()}, false);
    EXPECT_EQ(out_opt, stuff[0]);

    auto out_opt2 = scran_blocks::parallel_means(5, std::vector<double*>{}, false);
    EXPECT_EQ(full_of_nans(out_opt2), out_opt2.size());
}

TEST(ParallelMeans, Weighted) {
    std::vector<std::vector<double> > stuff {
        std::vector<double>{1, 2, 3, 4, 5},
        std::vector<double>{2, 1, 2, 6, 8},
        std::vector<double>{3, 7, 3, 3, 2}
    };

    // Using simple binary weights for testing purposes.
    std::vector<double> weights { 1, 0, 0 };
    std::vector<double*> ptrs{stuff[0].data(), stuff[1].data(), stuff[2].data()};
    auto out = scran_blocks::parallel_weighted_means(5, ptrs, weights.data(), false);
    EXPECT_EQ(out, stuff[0]);

    std::vector<double> weights1 { 1, 0, 1 };
    auto out1 = scran_blocks::parallel_weighted_means(5, ptrs, weights1.data(), false);
    auto ref1 = scran_blocks::parallel_means(5, std::vector<double*>{stuff[0].data(), stuff[2].data()}, false);
    EXPECT_EQ(out1, ref1);

    std::vector<double> weights2 { 1, 1, 1 };
    auto out2 = scran_blocks::parallel_weighted_means(5, ptrs, weights2.data(), false);
    auto ref2 = scran_blocks::parallel_means(5, ptrs, false);
    EXPECT_EQ(out2, ref2);

    // Now using some more complex weights.
    std::vector<double> weights3 { 0.5, 2, 1.5 };
    auto out3 = scran_blocks::parallel_weighted_means(5, ptrs, weights3.data(), false);
    std::vector<double> ref3{ 2.250, 3.375, 2.500, 4.625, 5.375 };
    scran_tests::compare_almost_equal(ref3, out3);

    // Optimizations.
    auto out_opt = scran_blocks::parallel_weighted_means(5, std::vector<double*>{stuff[0].data()}, weights1.data(), false);
    EXPECT_EQ(out_opt, stuff[0]);

    auto out_opt2 = scran_blocks::parallel_weighted_means(5, std::vector<double*>{}, weights1.data(), false);
    EXPECT_EQ(full_of_nans(out_opt2), out_opt2.size());

    double empty_weight = 0;
    auto out_opt3 = scran_blocks::parallel_weighted_means(5, std::vector<double*>{ stuff[1].data() }, &empty_weight, false);
    EXPECT_EQ(full_of_nans(out_opt3), out_opt3.size());

    std::vector<double> empty_weights(3);
    auto out_opt4 = scran_blocks::parallel_weighted_means(5, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, empty_weights.data(), false);
    EXPECT_EQ(full_of_nans(out_opt4), out_opt4.size());
}

TEST(ParallelMeans, Missings) {
    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
    std::vector<std::vector<double> > stuff {
        std::vector<double>{1,   2, nan,   4, nan},
        std::vector<double>{2, nan,   2, nan, nan},
        std::vector<double>{3,   7,   3, nan, nan}
    };

    auto out = scran_blocks::parallel_means(5, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, true);
    std::vector<double> ref {2.0, 9.0/2, 5.0/2, 4.0, nan};
    scran_tests::compare_almost_equal(ref, out);

    std::vector<double> weights { 2, 3, 5 };
    auto wout = scran_blocks::parallel_weighted_means(5, std::vector<double*>{stuff[0].data(), stuff[1].data(), stuff[2].data()}, weights.data(), true);
    std::vector<double> wref {(2 + 6 + 15)/10.0, (4 + 35)/(2.0 + 5.0), (6 + 15)/(3.0 + 5.0), 4.0, nan};
    scran_tests::compare_almost_equal(wref, wout);
}
