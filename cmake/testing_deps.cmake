include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(TimeIt STATIC ${CMAKE_SOURCE_DIR}/tests/utils/TimeIt.cpp)
target_include_directories(TimeIt PUBLIC ${CMAKE_SOURCE_DIR}/tests/utils)