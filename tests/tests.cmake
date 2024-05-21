add_executable(${CMAKE_PROJECT_NAME}_test_vec2 tests/test_vec2.cpp)
add_executable(${CMAKE_PROJECT_NAME}_test_save tests/test_save.cpp src/save/game_save.cpp)


target_include_directories(${CMAKE_PROJECT_NAME}_test_vec2 PRIVATE
  "${CMAKE_SOURCE_DIR}/src/"
  "${CMAKE_SOURCE_DIR}/include/")

target_include_directories(${CMAKE_PROJECT_NAME}_test_save PRIVATE
  "${CMAKE_SOURCE_DIR}/src/"
  "${CMAKE_SOURCE_DIR}/include/"
  "${CMAKE_SOURCE_DIR}/thirdparty/SDL/include")

target_link_libraries(${CMAKE_PROJECT_NAME}_test_save PRIVATE
  SDL3-static
  SDL3_image-static
)


add_test(NAME ${CMAKE_PROJECT_NAME}_test_vec2 
         COMMAND ${CMAKE_PROJECT_NAME}_test_vec2)

add_test(NAME ${CMAKE_PROJECT_NAME}_test_save 
         COMMAND ${CMAKE_PROJECT_NAME}_test_save)
