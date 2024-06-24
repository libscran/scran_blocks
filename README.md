# Utilities for scran

![Unit tests](https://github.com/libscran/core_utils/actions/workflows/run-tests.yaml/badge.svg)
![Documentation](https://github.com/libscran/core_utils/actions/workflows/doxygenate.yaml/badge.svg)
[![Codecov](https://codecov.io/gh/libscran/core_utils/graph/badge.svg?token=JWV0I4WJX2)](https://codecov.io/gh/libscran/core_utils)

## Overview

This repository contains utility functions for the other [**libscran**](https://github.com/libscran) repositories.
I don't know what else to say - it's just a mishmash of random functions that are re-used in multiple other libraries or don't warrant their own repository.
Developers should check out the [reference documentation](https://libscran.github.io/core_utils) for the available functions.

## Averaging vectors

The `average_vectors::compute()` function will compute the element-wise averages of any number of equi-length arrays.

```cpp
#include "scran/average_vectors.hpp"

std::vector<double> stat1 { 1, 2, 3, 4 };
std::vector<double> stat2 { 5, 6, 7, 8 };

// Contains { 3, 4, 5, 6 }.
auto averaged = scran::average_vectors::compute(
    stat1.size(), 
    { stat1.data(), stat2.data() }
    /* skip_nan = */ false
);
```

If NaNs are present, they can be ignored:

```cpp
#include "scran/average_vectors.hpp"
#include <limits>

auto nan = std::numeric_limits<double>::quiet_NaN();
std::vector<double> stat1 { 1, nan, 3, nan };
std::vector<double> stat2 { 5, 6, nan, nan };

// Contains { 3, 6, 3, nan }.
auto averaged = scran::average_vectors::compute(
    stat1.size(), 
    { stat1.data(), stat2.data() }
    /* skip_nan = */ true
);
```

We also support per-vector weights:

```cpp
#include "scran/average_vectors.hpp"

std::vector<double> stat1 { 1, 2, 3, 4 };
std::vector<double> stat2 { 5, 6, 7, 8 };
std::vector<double> weights { 1, 9 };

// Contains { 4.6, 5.6, 6.6, 7.6 }.
auto averaged = scran::average_vectors::compute(
    stat1.size(), 
    { stat1.data(), stat2.data() }
    weights.data(),
    /* skip_nan = */ false
);
```

## Weighting blocks

Several **libscran** analysis steps allow users to block on uninteresting factors like the batch or sample of origin.
Statistics are typically computed within each block and then combined across each block (e.g., with `average_vectors::compute()`).
When doing so, it may be desirable to weight each block by its size, favoring larger blocks that can emit more stable statistics.

The `block_weights::compute()` function will compute weights for each block based on its size.
The example below uses a variable block weight that increases linearly with block size from 0 to 200, after which it is capped at 1.
This `VARIABLE` policy penalizes very small blocks to ensure that their unstable statistics do not overly influence the average.
However, blocks are equally weighted once they are "large enough", ensuring that the average is not dominated by a single very large block. 

```cpp
#include "scran/block_weights.hpp"

std::vector<size_t> block_sizes { 10, 100, 1000 };
auto weights = scran::block_weights::compute(
    block_sizes, 
    /* policy = */ scran::block_weights::VARIABLE,
    /* variable = */ { 0, 200 } 
);
```

Users can also change the policy to `NONE`, where weights are equal to the block size;
or `EQUAL`, where all blocks are equally weighted regardless of size (assuming they are non-empty).

## Building projects

This repository is part of the broader [**libscran**](https://github.com/libscran/libscran) library,
so users are recommended to use the latter in their projects.
**libscran** developers should just use CMake with `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
  scran_core_utils 
  GIT_REPOSITORY https://github.com/libscran/core_utils
  GIT_TAG master # or any version of interest
)

FetchContent_MakeAvailable(scran_core_utils)

# For executables:
target_link_libraries(myexe scran_core_utils)

# For libaries
target_link_libraries(mylib INTERFACE scran_core_utils)
```
