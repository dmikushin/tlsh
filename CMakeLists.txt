cmake_minimum_required(VERSION 3.26)

project(
  TLSH
  VERSION 5.0.0
  LANGUAGES CXX
  DESCRIPTION "TLSH C++ implementation"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(VCPKG_MANIFEST_MODE OFF)
set(CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(TLSH_BUILD_STATIC "Build as static library instead of shared library" ON)
option(TLSH_BUILD_BINDINGS "Build Python bindings" ON)

# TLSH uses only half the counting buckets.
# It can use all the buckets now.
set(TLSH_BUCKETS 128)

if(TLSH_BUCKETS EQUAL 48)
  set(TLSH_HASH "min hash")
elseif(TLSH_BUCKETS EQUAL 128)
  set(TLSH_HASH "compact hash")
elseif(TLSH_BUCKETS EQUAL 256)
  set(TLSH_HASH "full hash")
else()
  message(FATAL_ERROR "Invalid TLSH_BUCKETS value")
endif()

# TLSH uses 1 byte checksum. The collision rate is 1 in 24.
# It can use 3 bytes checksum now. That collision rate in 1 in 5800.
set(TLSH_CHECKSUM 1)

# setting TLSH_DISTANCE_PARAMETERS to 1 allows you to set command line arguments
# to set - and hence experiment with the distance parameters
#	by default this is zero
set(TLSH_DISTANCE_PARAMETERS 0)

set(TLSH_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(src)

if(TLSH_BUILD_BINDINGS)
  if (NOT TLSH_BUILD_STATIC)
    message(FATAL_ERROR "Bindings require static build")
  endif (NOT TLSH_BUILD_STATIC)

  add_subdirectory(python)
endif(TLSH_BUILD_BINDINGS)
