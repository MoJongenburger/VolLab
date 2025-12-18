if(NOT BUILD_TESTING)
  return()
endif()

find_package(Catch2 3 CONFIG REQUIRED)

add_executable(vollab_tests
  test_version.cpp
)

target_link_libraries(vollab_tests
  PRIVATE
    vollab_core
    Catch2::Catch2WithMain
)

add_test(NAME vollab_tests COMMAND vollab_tests)
