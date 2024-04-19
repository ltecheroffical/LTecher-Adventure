cmake_minimum_required(VERSION 3.0.0)
project(ltecher_adventure VERSION 0.1.0)

# SDL
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL_TEST_LIBRARY OFF)

# PNG
set(PNG_TESTS OFF)
set(PNG_SHARED OFF)

# Shared libs
set(BUILD_SHARED_LIBS OFF)

# C++
set(CMAKE_CXX_STANDARD 20)

# Windows compability
if (WIN32)
  include(cmake/windows.cmake)
endif()

# Libraries
add_subdirectory(thirdparty/SDL)                # Rendering library
add_subdirectory(thirdparty/SDL_image)          # Image loading library
add_subdirectory(thirdparty/SDL_mixer)          # Audio loading library
add_subdirectory(thirdparty/SDL_ttf)            # Font loading library
add_subdirectory(thirdparty/SDL_net)            # Networking library

add_subdirectory(thirdparty/libpng)             # PNG loading library

add_subdirectory(thirdparty/tinyfiledialogs)    # GUI dialogs

# Sources
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

# Compilers
message(STATUS "CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  include(cmake/compilers/clang.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  include(cmake/compilers/clang.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  include(cmake/compilers/gcc.cmake)
else()
  # Display a warning message
  message(WARNING "The compiler type is unknown.")
endif()

# Resources
set(RESOURCES_PATH "resources/")

option(
  HARDCODE_PATH_IN_DEBUG
  "Sets if the path is hardcoded into the binary on debug mode.\n
    Useful when building to other platforms and testing" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(PRODUCTION_BUILD 1)
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
  set(PRODUCTION_BUILD 0)
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT HARDCODE_PATH_IN_DEBUG)
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES="${RESOURCES_PATH}") 
else()
  set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/")
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES="${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_PATH}")
endif()

message(STATUS "RESOURCES_PATH = ${RESOURCES_PATH}")

# Bundle (MacOS only)
if (APPLE)
  include(cmake/macos_bundle.cmake)
endif()

# Linking
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

add_dependencies("${CMAKE_PROJECT_NAME}"
  SDL3-static
  SDL3_image-static
  SDL3_mixer-static
  SDL3_net-static
  SDL3_ttf-static

  png_static

  tinyfiledialogs
)

target_link_libraries("${CMAKE_PROJECT_NAME}"
  SDL3-static
  SDL3_image-static
  SDL3_mixer-static
  SDL3_net-static
  SDL3_ttf-static

  png_static

  tinyfiledialogs
)
