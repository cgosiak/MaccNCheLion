cmake_minimum_required(VERSION 3.3)
project(NewMacc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES mnc.cpp SymbolTable.cpp SymbolTable.h DataEntry.cpp DataEntry.h mncscan.cpp mncscan.h mncparse.cpp mncparse.h mnccode.cpp mnccode.h)
add_executable(NewMacc ${SOURCE_FILES})