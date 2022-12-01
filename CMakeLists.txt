cmake_minimum_required(VERSION 3.23)
project(AdventOfCode2022)

file(GLOB_RECURSE SRCS src/*)
add_executable(AdventOfCode2022 ${SRCS})