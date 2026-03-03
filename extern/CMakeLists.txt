include(FetchContent)

FetchContent_Declare(
  sanisizer
  GIT_REPOSITORY https://github.com/LTLA/sanisizer
  GIT_TAG master # ^0.1.0
)

FetchContent_Declare(
  quickstats
  GIT_REPOSITORY https://github.com/LTLA/quickstats
  GIT_TAG master # ^0.1.0
)

FetchContent_MakeAvailable(sanisizer)
FetchContent_MakeAvailable(quickstats)
