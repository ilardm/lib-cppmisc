cmake_minimum_required ( VERSION 2.8 )
project ( libcppmisc-exmple )
set ( TARGET_NAME   "${PROJECT_NAME}" ) # actual executable name

# define project sources and includes directories
set ( SOURCES_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/src/" )
set ( INCLUDES_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/inc/"
                    "${CMAKE_CURRENT_BINARY_DIR}"
    )

# define includes search path
include_directories ( ${INCLUDES_DIR}
                    )
# define source files list
file ( GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp )
# define libraries search path
link_directories ( )

# set default build type
if ( NOT CMAKE_BUILD_TYPE )
    message ( STATUS "${PROJECT_NAME}: set default build type" )

    # set ( CMAKE_BUILD_TYPE Release )
    # while in intensive development use debug build type
    set ( CMAKE_BUILD_TYPE Debug )
endif ()

# set common compiler flags
set ( CFLAGS    "-Wall" )
set ( CXXFLAGS  "-Wall" )
set ( DEFINES   "" )

# set compiler flags for build type
if ( CMAKE_BUILD_TYPE STREQUAL "Release" )              # Release
    message ( STATUS "${PROJECT_NAME}: build release" )

    set ( DEFINES   "${DEFINES} -D_RELEASE" )
endif()
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )                # Debug
    message ( STATUS "${PROJECT_NAME}: build debug" )

    set ( CFLAGS    "${CFLAGS} -O0" )
    set ( CXXFLAGS  "${CXXFLAGS} -O0" )
    set ( DEFINES   "${DEFINES} -D_DEBUG" )
endif ()

# apply flags
set ( CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} ${CFLAGS}" )
set ( CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} ${CXXFLAGS}" )
add_definitions ( ${DEFINES} )

# show flags
message ( STATUS "${PROJECT_NAME}: c flags: ${CMAKE_C_FLAGS}" )
message ( STATUS "${PROJECT_NAME}: cxx flags: ${CMAKE_CXX_FLAGS}" )
message ( STATUS "${PROJECT_NAME}: defines: ${DEFINES}" )

# build target
add_executable ( ${TARGET_NAME} ${SOURCES} )
target_link_libraries ( ${TARGET_NAME} cppmisc )
