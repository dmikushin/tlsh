project(
    tlsh-py
    LANGUAGES CXX
    VERSION 0.1.0
)

find_package(Python 3
    REQUIRED COMPONENTS Interpreter Development.Module
    OPTIONAL_COMPONENTS Development.SABIModule
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")

find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(
    _tlsh NB_STATIC
    ./src/tlsh.cpp
)

add_dependencies(_tlsh tlsh)

target_compile_definitions(_tlsh PRIVATE $<TARGET_PROPERTY:tlsh,COMPILE_DEFINITIONS>)
target_include_directories(_tlsh PRIVATE $<TARGET_PROPERTY:tlsh,INCLUDE_DIRECTORIES> ./inc)
target_link_directories(_tlsh PRIVATE $<TARGET_PROPERTY:tlsh,LINK_DIRECTORIES>)

if(MSVC)
target_link_libraries(_tlsh PRIVATE tlsh)
# target_link_libraries(_tlsh PRIVATE Userenv.lib Bcrypt.lib Ws2_32.lib kernel32.lib ntdll.lib bochscpu_ffi.lib)
else()
target_link_libraries(_tlsh PRIVATE tlsh)
    # target_link_libraries(_tlsh PRIVATE bochscpu_ffi)
endif()

if(APPLE)
    target_link_libraries(_tlsh PRIVATE "-framework CoreFoundation" -Wl -lm)
endif()

install(DIRECTORY tlsh DESTINATION .)
install(TARGETS _tlsh LIBRARY DESTINATION tlsh)

