CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(sorter)
SET(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pedantic -g")

find_package(Boost 1.53 COMPONENTS program_options)
if(Boost_FOUND)
    include_directories($Boost_INCLUDE_DIRS})

    # listsorter
    ADD_EXECUTABLE(listsorter main.cpp main.h listsort.h listsort.cpp)
    target_compile_definitions(listsorter PUBLIC USELIST)
    target_link_libraries(listsorter ${Boost_LIBRARIES})