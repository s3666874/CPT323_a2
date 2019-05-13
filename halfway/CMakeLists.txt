CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(mergeSorter)

SET(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++17 -Wextra -g")

find_package(Boost 1.53 COMPONENTS program_options)

if(Boost_FOUND)
    include_directories($Boost_INCLUDE_DIRS})
    
    # listsorter
    ADD_EXECUTABLE(listsorter main.cpp main.h list.cpp list.h datastructure.h)
    target_link_libraries(listsorter ${Boost_LIBRARIES})
    target_compile_definitions(listsorter PUBLIC USELIST)

endif()