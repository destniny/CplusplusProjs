#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("norm") {
	// Euclidean Norm
	auto const a1 = comp6771::euclidean_vector{10,2,3,4};
	auto oss = std::ostringstream{};
	oss << comp6771::euclidean_norm(a1);
	CHECK(oss.str() == "11.3578");
}

TEST_CASE("unit") {
	// Euclidean Norm
	auto const a1 = comp6771::euclidean_vector{10,2,3,4};
	auto oss = std::ostringstream{};
	oss << comp6771::unit(a1);
	CHECK(oss.str() == "[0.880451 0.17609 0.264135 0.35218]");
}

TEST_CASE("dot") {
	// Euclidean Norm
	auto const a1 = comp6771::euclidean_vector{10,2,3,4};
	auto a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << comp6771::dot(a1, a2);
	CHECK(oss.str() == "56");
}