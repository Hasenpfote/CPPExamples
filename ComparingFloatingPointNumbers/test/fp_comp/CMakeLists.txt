cmake_minimum_required(VERSION 3.1)

# Find thread.
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

#
set(TEST_NAME "fp_comp_test")
set(TEST_LABELS "fp_comp")

# Target sources directory
set(TARGET_SOURCES_DIR "../../sources")

# Target include directory
include_directories(${TARGET_SOURCES_DIR})

#
set(ALL_FILES
    #${TARGET_SOURCES_DIR}/bar.cpp
    fp_comp_test1.cpp
    fp_comp_test2.cpp
    # Add a new file here.
    )

#
add_executable(${TEST_NAME} ${ALL_FILES})
target_link_libraries(${TEST_NAME} gtest gtest_main Threads::Threads)
add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)

# run with: ctest -L xxx
set_property(TEST ${TEST_NAME} PROPERTY LABELS ${TEST_LABELS})