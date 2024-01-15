set(TLSH_SRC_DIR ${TLSH_ROOT_DIR}/src)
set(TLSH_INC_DIR ${TLSH_SRC_DIR}/inc)

configure_file(${TLSH_INC_DIR}/tlsh_version.h.in ${TLSH_INC_DIR}/tlsh_version.h)

set(SOURCE_FILES
    # ${TLSH_SRC_DIR}/gen_arr2.cpp
    # ${TLSH_SRC_DIR}/input_desc.cpp
    # ${TLSH_SRC_DIR}/shared_file_functions.cpp
    ${TLSH_SRC_DIR}/tlsh_impl.cpp
    ${TLSH_SRC_DIR}/tlsh_util.cpp
    ${TLSH_SRC_DIR}/tlsh.cpp
)

if(WIN32)

endif()

if(TLSH_BUILD_STATIC)
    add_library(tlsh STATIC)
else()
    add_library(tlsh SHARED)
endif()


target_sources(tlsh PRIVATE ${SOURCE_FILES})

target_include_directories(tlsh PUBLIC ${TLSH_INC_DIR} ${TLSH_INC_DIR}/win32)

target_compile_definitions(tlsh
    PUBLIC
        BUCKETS_${TLSH_BUCKETS}
        CHECKSUM_${TLSH_CHECKSUM}B
)

if(WIN32)
    target_compile_definitions(tlsh PUBLIC _WINDOWS)
elseif(APPLE)
    target_compile_definitions(tlsh PUBLIC _MACOS)
elseif(UNIX)
    target_compile_definitions(tlsh PUBLIC _LINUX)
    target_compile_options(tlsh PUBLIC -fPIC)
else()
    message(FATAL_ERROR "Invalid OS")
 endif()

# set(TLSH_SRCS tlsh.cpp tlsh_impl.cpp tlsh_util.cpp input_desc.cpp shared_file_functions.cpp)
# add_library(tlsh_static STATIC ${TLSH_SRCS})
# target_link_libraries(tlsh_static PRIVATE)
# set_target_properties(tlsh_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set_target_properties(tlsh_static PROPERTIES OUTPUT_NAME tlsh${BUILD_POSTFIX})

# if (NOT DEFINED TLSH_SHARED_LIBRARY)
#     set(TLSH_SHARED_LIBRARY 0)
# endif()

# if(TLSH_SHARED_LIBRARY EQUAL 1)
#     add_library(tlsh_shared SHARED ${TLSH_SRCS})
#     target_link_libraries(tlsh_shared PRIVATE)
#     set_target_properties(tlsh_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
#     set_target_properties(tlsh_shared PROPERTIES OUTPUT_NAME tlsh${BUILD_POSTFIX})
#     set_target_properties(tlsh_shared PROPERTIES VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
#                                                  SOVERSION "${VERSION_MAJOR}")
# endif()

# if(TLSH_SHARED_LIBRARY)
#     install(TARGETS tlsh_static tlsh_shared DESTINATION lib)
# else()
#     install(TARGETS tlsh_static             DESTINATION lib)
# endif()

install(TARGETS tlsh DESTINATION lib)

install(
    FILES
        ${TLSH_INC_DIR}/tlsh_impl.h
        ${TLSH_INC_DIR}/tlsh_version.h
        ${TLSH_INC_DIR}/tlsh_util.h
        ${TLSH_INC_DIR}/tlsh.h
    DESTINATION
        inc
)


