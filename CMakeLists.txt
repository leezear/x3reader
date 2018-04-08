cmake_minimum_required(VERSION 3.10)
project(reader)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/include/xcsp3)
include_directories(/usr/include/libxml2)
add_executable(reader main.cpp UTF8String.cc XCSP3Code.cc XCSP3CoreParser.cc XCSP3Manager.cc
        XCSP3Tree.cc XCSP3Code.cc XCSP3TreeNode.cc XMLParser.cc XMLParserTags.cc HModel.cpp HModel.h Timer.h BMFileParser.h)
target_link_libraries(reader xml2)