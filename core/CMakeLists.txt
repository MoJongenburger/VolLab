add_library(vollab_core
  src/version.cpp
)

target_include_directories(vollab_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
