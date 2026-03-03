#include <gtest/gtest.h>
#include "scran_blocks/parallel_quantiles.hpp"
#include "scran_tests/scran_tests.hpp"
#include <vector>

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
    int nan_count = 0;
    for (auto x : out_opt2) {
        nan_count += std::isnan(x);
    }
    EXPECT_EQ(nan_count, out_opt2.size());
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
