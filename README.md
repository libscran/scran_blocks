# Blocking utilities for scran

![Unit tests](https://github.com/libscran/scran_blocks/actions/workflows/run-tests.yaml/badge.svg)
![Documentation](https://github.com/libscran/scran_blocks/actions/workflows/doxygenate.yaml/badge.svg)
[![Codecov](https://codecov.io/gh/libscran/scran_blocks/graph/badge.svg?token=JWV0I4WJX2)](https://codecov.io/gh/libscran/scran_blocks)

## Overview

This repository contains utilities for blocked analyses for the other [**libscran**](https://github.com/libscran) repositories.
Any uninteresting factor of variation (usually across the cells) can be used as a blocking factor, e.g., experimental batches, sample/patient of origin.
In the presence of blocks, our general strategy is to perform the analysis within each block before combining our conclusions across blocks.
This ensures that our results are not affected by the uninteresting differences between blocks.

## Averaging vectors

The `average_vectors::compute()` function will compute the element-wise averages of any number of equi-length arrays.
This is typically used to average statistics across blocks, where each array contains the statistics for a single block over all genes.

```cpp
#include "scran_blocks/scran_blocks.hpp"

std::vector<double> stat1 { 1, 2, 3, 4 };
std::vector<double> stat2 { 5, 6, 7, 8 };

// Contains { 3, 4, 5, 6 }.
auto averaged = scran_blocks::average_vectors(
    stat1.size(), 
    { stat1.data(), stat2.data() }
    /* skip_nan = */ false
);
```

If NaNs are present, they can be ignored:

```cpp
#include <limits>

auto nan = std::numeric_limits<double>::quiet_NaN();
std::vector<double> stat1n { 1, nan, 3, nan };
std::vector<double> stat2n { 5, 6, nan, nan };

// Contains { 3, 6, 3, nan }.
auto averagedn = scran_blocks::average_vectors(
    stat1n.size(), 
    { stat1n.data(), stat2n.data() }
    /* skip_nan = */ true
);
```

We also support per-vector weights:

```cpp
std::vector<double> stat1w { 1, 2, 3, 4 };
std::vector<double> stat2w { 5, 6, 7, 8 };
std::vector<double> weights { 1, 9 };

// Contains { 4.6, 5.6, 6.6, 7.6 }.
auto averagedw = scran_blocks::average_vectors_weighted(
    stat1w.size(), 
    { stat1w.data(), stat2w.data() }
    weights.data(),
    /* skip_nan = */ false
);
```

See the [reference documentation](https://libscran.github.io/scran_blocks) for more details.

## Weighting blocks

When combining statistics across blocks, it may be desirable to weight each block by its size, favoring larger blocks that can emit more stable statistics.
This is done using the `compute_block_weights()` function that calculates a weight for each block based on its size.

```cpp
#include "scran_blocks/scran_blocks.hpp"

std::vector<size_t> block_sizes { 10, 100, 1000 };
auto weights = scran_blocks::compute_weights(
    block_sizes, 
    /* policy = */ scran_blocks::WeightPolicy::VARIABLE,
    /* variable = */ { 0, 200 } 
);
```

The above code chunk uses a variable block weight that increases linearly with block size from 0 to 200, after which it is capped at 1.
This `VARIABLE` policy penalizes very small blocks to ensure that their unstable statistics do not overly influence the average.
Blocks are equally weighted once they are "large enough", ensuring that the average is not dominated by a single very large block. 

Users can also change the policy to `NONE`, where weights are equal to the block size;
or `EQUAL`, where all blocks are equally weighted regardless of size (assuming they are non-empty).
In such cases, the `variable` argument is ignored.
Check out the [reference documentation](https://libscran.github.io/scran_blocks) for more details.

## Building projects

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
