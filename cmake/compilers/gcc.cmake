# Configures the gcc/g++ compiler

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
  -static-libgcc
  -static-libstdc++
  -Wl,-R,'$$ORIGIN'
)

# Check for mingw
if (MINGW)
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -static
  )
endif()

if (WIN32)
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mwindows)
endif()

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
  -Wall
)
