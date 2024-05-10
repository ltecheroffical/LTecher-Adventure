# Configure's the clang compiler

if (WIN32)
  # Add -static-libstdc++ on Windows
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -static-libstdc++
  )
endif()

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
  -Wall
)
