#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("Compare1") {
	auto const a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << (a2==comp6771::euclidean_vector{4,3,2,1});
	CHECK(oss.str() == "1");
	oss = std::ostringstream{};
	oss << (a2!=comp6771::euclidean_vector{4,3,2,1});
	CHECK(oss.str() == "0");
}