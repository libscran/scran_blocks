# Blocking utilities for libscran

![Unit tests](https://github.com/libscran/scran_blocks/actions/workflows/run-tests.yaml/badge.svg)
![Documentation](https://github.com/libscran/scran_blocks/actions/workflows/doxygenate.yaml/badge.svg)
[![Codecov](https://codecov.io/gh/libscran/scran_blocks/graph/badge.svg?token=JWV0I4WJX2)](https://codecov.io/gh/libscran/scran_blocks)

## Overview

This repository contains utilities for blocked analyses for the other [**libscran**](https://github.com/libscran) repositories.
Any uninteresting factor of variation (usually across the cells) can be used as a blocking factor, e.g., experimental batches, sample/patient of origin.
In the presence of blocks, our general strategy is to perform the analysis within each block before combining our conclusions across blocks.
This ensures that our results are not affected by the uninteresting differences between blocks.
See the [reference documentation](https://libscran.github.io/scran_blocks) for more details.

## Weighting blocks

When combining statistics across blocks, it may be desirable to weight each block by its size, favoring larger blocks that can emit more stable statistics.
This is done using the `compute_weights()` function that calculates a weight for each block based on its size.

```cpp
#include "scran_blocks/scran_blocks.hpp"

std::vector<size_t> block_sizes { 10, 100, 1000 };
auto weights = scran_blocks::compute_weights(
    block_sizes, 
    scran_blocks::WeightPolicy::VARIABLE,
    []{
        VariableWeightParameters vparams;
        vparams.upper_bound = 200;
        return vparams;
    }()
);
```

The above code chunk uses a variable block weight that increases linearly with block size from 0 to 200, after which it is capped at 1.
This `VARIABLE` policy penalizes very small blocks to ensure that their unstable statistics do not overly influence the average.
Blocks are equally weighted once they are "large enough", ensuring that the average is not dominated by a single very large block. 

Users can also change the policy to `SIZE`, where weights are equal to the block size;
or `EQUAL`, where all blocks are equally weighted regardless of size (assuming they are non-empty).
In such cases, the `variable` argument is ignored.
Check out the [reference documentation](https://libscran.github.io/scran_blocks) for more details.

## Combining blocked statistics

Computing a weighted mean is the most obvious approach to combine (weighted) statistics from multiple blocks.
When doing so, we recommend skipping blocks with a weight of zero.
This is slightly more efficient, but more importantly, it avoids problems with sums of `0 * Inf` or `0 * NaN` introducing unnecessary `NaN`s.
Implementations may also choose to skip `NaN` observations, in which case the denominator of the weighted mean should be adjusted accordingly.

Another simple approach is to compute a quantile, e.g., using the [**quickstats**](https://github.com/LTLA/quickstats) library.
A quantile like the median is more robust to outliers than a weighted mean, while the minimum/maximum can capture the best/worst-case behavior across all blocks.
For example, ranking genes by the minimum log-fold change will favor genes that exhibit consistent upregulation across all blocks.
However, quantiles are much less amenable to weighting as there is no clear choice for how the quantile should behave at the boundaries between observations.

# Building projects

### CMake with `FetchContent`

If you're using CMake, you just need to add something like this to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
  scran_blocks
  GIT_REPOSITORY https://github.com/libscran/scran_blocks
  GIT_TAG master # or any version of interest
)

FetchContent_MakeAvailable(scran_blocks)
```

Then you can link to **scran_blocks** to make the headers available during compilation:

```cmake
# For executables:
target_link_libraries(myexe libscran::scran_blocks)

# For libaries
target_link_libraries(mylib INTERFACE libscran::scran_blocks)
```

### CMake with `find_package()`

```cmake
find_package(libscran_scran_blocks CONFIG REQUIRED)
target_link_libraries(mylib INTERFACE libscran::scran_blocks)
```

To install the library, use:

```sh
mkdir build && cd build
cmake .. -DSCRAN_BLOCKS_TESTS=OFF
cmake --build . --target install
```

### Manual

If you're not using CMake, the simple approach is to just copy the files in `include/` - either directly or with Git submodules - and include their path during compilation with, e.g., GCC's `-I`.
