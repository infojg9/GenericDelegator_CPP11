# Author: https://github.com/infojg9
# MIT/BSD Redistributable License

cmake_minimum_required(VERSION 3.8)
project(GenericDelegator)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -pipe -DGENERIC_DELEGATE_ON -Wall -Wextra -Wchkp -Wdouble-promotion -Wformat -Werror -pedantic -O0 -g3 -ggdb3 -ftest-coverage -fprofile-arcs")

set(SOURCE_FILES CGenericDelegater.h main.cpp)
add_executable(GenericDelegator ${SOURCE_FILES})
