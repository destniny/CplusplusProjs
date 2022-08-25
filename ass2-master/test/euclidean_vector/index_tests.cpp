#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("get") {
	auto a1 = comp6771::euclidean_vector{1,2,3,4};
	auto oss = std::ostringstream{};
	oss << a1[0];
	CHECK(oss.str() == "1");
}

TEST_CASE("set") {
	auto a1 = comp6771::euclidean_vector{1,2,3,4};
	auto oss = std::ostringstream{};
    a1[0] = 10;
	oss << a1.at(0);
	CHECK(oss.str() == "10");
}

TEST_CASE("dimenstion") {
	auto a1 = comp6771::euclidean_vector{1,2,3,4};
	auto oss = std::ostringstream{};
	oss << a1.dimensions();
	CHECK(oss.str() == "4");
}