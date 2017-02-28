cmake_minimum_required(VERSION 2.8)

# Google Test settings
include(ExternalProject)

set(GTEST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/googletest")

# Download and install GoogleTest
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${GTEST_PREFIX}
    # cmake arguments
    CMAKE_ARGS -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    )

ExternalProject_Get_Property(googletest source_dir binary_dir)
set(GTEST_LOCATION  "${binary_dir}/googlemock/gtest")
set(GTEST_INCLUDES  "${source_dir}/googletest/include")
set(GTEST_LIB       "${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(GTEST_MAIN_LIB  "${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}")

# variables defining the import location properties for the generated gtest and
# gtestmain libraries
if(MSVC)
    set(GTEST_IMPORTED_LOCATION
        IMPORTED_LOCATION_DEBUG     "${GTEST_LOCATION}/Debug/${GTEST_LIB}"
        IMPORTED_LOCATION_RELEASE   "${GTEST_LOCATION}/Release/${GTEST_LIB}"
        )
    set(GTESTMAIN_IMPORTED_LOCATION
        IMPORTED_LOCATION_DEBUG     "${GTEST_LOCATION}/Debug/${GTEST_MAIN_LIB}"
        IMPORTED_LOCATION_RELEASE   "${GTEST_LOCATION}/Release/${GTEST_MAIN_LIB}"
        )
else()
    set(GTEST_IMPORTED_LOCATION
        IMPORTED_LOCATION           "${GTEST_LOCATION}/${GTEST_LIB}")
    set(GTESTMAIN_IMPORTED_LOCATION
        IMPORTED_LOCATION           "${GTEST_LOCATION}/${GTEST_MAIN_LIB}")
endif()

# the gtest include directory exists only after it is build, but it is used/needed
# for the set_target_properties call below, so make it to avoid an error
file(MAKE_DIRECTORY ${GTEST_INCLUDES})

# define imported library 'gtest'
add_library(gtest IMPORTED STATIC GLOBAL)
set_target_properties(gtest PROPERTIES
    IMPORTED_LINK_INTERFACE_LIBRARIES   "${CMAKE_THREAD_LIBS_INIT}"
    INTERFACE_INCLUDE_DIRECTORIES       "${GTEST_INCLUDES}"
    ${GTEST_IMPORTED_LOCATION}
    )

# define imported library 'gtest_main'
add_library(gtest_main IMPORTED STATIC GLOBAL)
set_target_properties(gtest_main PROPERTIES
    IMPORTED_LINK_INTERFACE_LIBRARIES   gtest
    ${GTESTMAIN_IMPORTED_LOCATION}
    )

# make 'gtest' depend on 'googletest'
add_dependencies(gtest googletest)    