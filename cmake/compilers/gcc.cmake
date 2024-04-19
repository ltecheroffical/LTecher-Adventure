# Configures the gcc/g++ compiler

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
  -static-libgcc
  -static-libstdc++
  -Wl,-R,'$$ORIGIN'
)
