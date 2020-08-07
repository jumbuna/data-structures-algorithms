cmake_minimum_required(VERSION 3.16)
project(dsAlg)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(algs)
include_directories(algs/searching)
include_directories(algs/sorting)
include_directories(algs/substring-search)
include_directories(documentation)
include_directories(ds)
include_directories(src)
include_directories(test)

add_executable(substring test/substring.cpp)
add_executable(search test/Searching.cpp)
add_executable(sort test/sorting.cpp)
add_executable(main test/main.cpp)
