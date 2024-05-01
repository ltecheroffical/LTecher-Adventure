add_executable(${CMAKE_PROJECT_NAME}_test_vec2 tests/test_vec2.cpp)

target_include_directories(${CMAKE_PROJECT_NAME}_test_vec2 PRIVATE
  "${CMAKE_SOURCE_DIR}/src/"
  "${CMAKE_SOURCE_DIR}/include/")

add_test(NAME ${CMAKE_PROJECT_NAME}_test_vec2 
         COMMAND ${CMAKE_PROJECT_NAME}_test_vec2)
