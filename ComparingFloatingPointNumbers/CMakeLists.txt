cmake_minimum_required(VERSION 3.5)

project(App CXX)

# Check if supported platforms and compilers.
if(WIN32)
	if(MSVC)
		if(MSVC14)
		else()
			message(FATAL_ERROR "You are using an unsupported MSVC version!")
		endif()
	elseif()
		message(FATAL_ERROR "You are using an unsupported Windows compiler!")
	endif()
elseif(UNIX)
	option(FORCE_32BIT_BUILD "Force a 32bit compile on 64bit" OFF)
else()
	message(FATAL_ERROR "You are on an unsupported platform!")
endif()

# Additional cmake files.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Compiler settings.
include(compiler_settings)

# The relative path from `CMAKE_CURRENT_SOURCE_DIR`.
set(SOURCES_DIR "sources")

# Fetch files.
file(GLOB_RECURSE HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" ${SOURCES_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" ${SOURCES_DIR}/*.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

# Define a grouping for source files in IDE project generation.
if(WIN32 AND MSVC)
	include(utils)
	do_grouping_for_files("Header Files" ${SOURCES_DIR} "${HEADER_FILES}")
	do_grouping_for_files("Source Files" ${SOURCES_DIR} "${SOURCE_FILES}")
endif()

# Targets.
add_executable(${PROJECT_NAME} ${ALL_FILES})
if(FORCE_32BIT_BUILD)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()

# Install.
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin/Debug CONFIGURATIONS Debug)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin/Release CONFIGURATIONS Release)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin/MinSizeRel CONFIGURATIONS MinSizeRel)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin/RelWithDebInfo CONFIGURATIONS RelWithDebInfo)

# Tests
option(CREATE_UNIT_TESTS "If you need an unit tests." ON)
if(${CREATE_UNIT_TESTS})
    enable_testing()
    include(cmake/gtest.cmake)
    add_subdirectory(test)
endif()