cmake_minimum_required(VERSION 3.15)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman src/main.cpp src/BitFileManipulator.cpp src/HuffmanTree.cpp
        src/HuffmanArchiver.cpp src/ByteFileReader.cpp src/CLI.cpp)

project(test_huffman)
add_executable(test_huffman src/BitFileManipulator.cpp src/HuffmanTree.cpp
        src/HuffmanArchiver.cpp src/ByteFileReader.cpp src/CLI.cpp
        test/doctest.h test/TestBinManipulator.cpp test/TestMain.cpp test/TestHaffmanTree.cpp test/TestCompressExtract.cpp test/TestCLI.cpp test/TestCLI.cpp)


include_directories(include)
include_directories(test)

add_definitions(-DDEBUG)
add_definitions(-DFLAGS)
add_definitions(-D_GNU_SOURCE)
