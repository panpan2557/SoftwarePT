
cmake_minimum_required(VERSION 3.3)
project(SoftwarePT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -liconv")

set(SOURCE_FILES SyllableReader.cpp SyllableReader.cpp SyllableReader.h main.cpp EntryCounter.h EntryCounter.cpp Trie.cpp Trie.h)
add_library(SyllableReader STATIC SyllableReader.cpp)
add_library(EntryCounter STATIC EntryCounter.cpp)
add_executable(SoftwarePT ${SOURCE_FILES})
target_link_libraries(SoftwarePT SyllableReader EntryCounter)