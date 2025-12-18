add_executable(vollab_md
  src/main.cpp
)

target_include_directories(vollab_md PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(vollab_md PRIVATE
  spdlog::spdlog
  nlohmann_json::nlohmann_json
  Boost::system
  OpenSSL::SSL
  OpenSSL::Crypto
)
