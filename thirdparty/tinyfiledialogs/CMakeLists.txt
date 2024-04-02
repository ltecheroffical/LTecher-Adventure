cmake_minimum_required(VERSION 3.16)
project(tinyfiledialogs)

add_library(tinyfiledialogs)

target_sources(tinyfiledialogs PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/tinyfiledialogs.c
)

target_include_directories(tinyfiledialogs PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
