cmake_minimum_required(VERSION 2.8)
project(html_render)

set(CMAKE_CXX_STANDARD 14)

add_executable(html_render main.cpp nlohmann_json.hpp ginger.h render.hpp main.cpp)