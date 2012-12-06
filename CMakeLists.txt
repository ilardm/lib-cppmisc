cmake_minimum_required ( VERSION 2.8 )
project ( libcppmisc )
set ( TARGET_NAME   "cppmisc" ) # actual executable name

if ( DEFINED BUILD_EXAMPLES )
    add_subdirectory ( examples )
endif ()

set ( VERSION_MAJOR    0 )
set ( VERSION_MINOR    1 )
set ( VERSION_PATCH    1 )
set ( VERSION_MODE     d )
set ( VERSION_STRING   "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${VERSION_MODE}" )

message ( STATUS "configuring ${PROJECT_NAME} v${VERSION_STRING}" )

# define project sources and includes directories
set ( SOURCES_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/src/" )
set ( INCLUDES_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/inc/"
                    "${CMAKE_CURRENT_BINARY_DIR}"
    )

# define includes search path
include_directories ( ${INCLUDES_DIR}
                    )
# define sources search path
file ( GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp )
# define libraries search path
link_directories ( )

configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/inc/libcppmisc_version.h.in
                 ${CMAKE_CURRENT_BINARY_DIR}/libcppmisc_version.h
                 @ONLY
               )

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

# Doxygen target
find_package ( Doxygen )
if ( DOXYGEN_FOUND )
    configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target ( doc-libcppmisc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_library ( ${TARGET_NAME} STATIC ${SOURCES} )

target_link_libraries ( ${TARGET_NAME} )
