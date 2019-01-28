cmake_minimum_required(VERSION 3.6)

project(example_2)

add_executable(example_2 "")

file(GLOB_RECURSE SOURCES src/*.cpp)

target_sources(example_2
    PRIVATE
    ${SOURCES}
)

target_include_directories(example_2
    PRIVATE
    src
)

find_package(Threads REQUIRED)

target_link_libraries(example_2
    PRIVATE
    jet-live
    Threads::Threads
)

set_target_properties(example_2
    PROPERTIES
        CXX_STANDARD 11
)

target_compile_options(example_2
    PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Wpedantic>
    $<$<COMPILE_LANGUAGE:CXX>:-Wpedantic>
    $<$<COMPILE_LANGUAGE:C>:-Wshadow>
    $<$<COMPILE_LANGUAGE:CXX>:-Wshadow>
    $<$<COMPILE_LANGUAGE:C>:-Wconversion>
    $<$<COMPILE_LANGUAGE:CXX>:-Wconversion>
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(example_2
        PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wvexing-parse>
        $<$<COMPILE_LANGUAGE:CXX>:-Wvexing-parse>
    )
endif()
