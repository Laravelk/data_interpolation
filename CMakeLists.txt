cmake_minimum_required(VERSION 3.14)
project(math)

set(CMAKE_CXX_STANDARD 17)

find_package(libInterpolate REQUIRED)
find_package(Boost REQUIRED)

add_executable(math main.cpp Interpolation/Derivative.h Interpolation/Interpolation.cpp Interpolation/Interpolation.h)

target_link_libraries(math libInterpolate::Interpolate )
