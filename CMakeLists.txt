cmake_minimum_required(VERSION 3.16)

project(ltecher_adventure)

if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/raylib)				# Game Engine

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")


add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

set(RESOURCES_FILE "gameassets.ltassets")

option(
  HARDCODE_PATH_IN_DEBUG
  "Sets if the path is hardcoded into the binary on debug mode.\n
    Useful when building to other platforms and testing" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT HARDCODE_PATH_IN_DEBUG)
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${RESOURCES_FILE}") 
else()
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_FILE}")
endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if (APPLE)
  add_custom_target(bundle)
  add_custom_command(TARGET bundle
    DEPENDS ${PROJECT_NAME}
   
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Resources"
    

    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bundle/Info.plist"
      "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Info.plist"

    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}" 
      "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS/"

    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bundle/run.sh" 
      "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS/run.sh"
    COMMAND chmod +x "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS/run.sh"


    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_FILE}"
      "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Resources/${RESOURCES_FILE}"

    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bundle/icon.icns" 
      "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Resources/icon.icns"
  )
endif()

if(MSVC)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
  raylib
)
