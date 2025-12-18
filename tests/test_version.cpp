#include <catch2/catch_test_macros.hpp>
#include "vollab/version.hpp"

TEST_CASE("version is non-empty") {
  REQUIRE(!vollab::version().empty());
}
