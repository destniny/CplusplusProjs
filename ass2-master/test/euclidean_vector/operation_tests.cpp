#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("Addition") {
	auto const a1 = comp6771::euclidean_vector{1,2,3,4};
    auto const a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << a1 + a2;
	CHECK(oss.str() == "[5 5 5 5]");
}

TEST_CASE("Substraction") {
	auto const a1 = comp6771::euclidean_vector{1,2,3,4};
    auto const a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << a1 - a2;
	CHECK(oss.str() == "[-3 -1 1 3]");
}

TEST_CASE("Multiplication") {
	auto const a1 = comp6771::euclidean_vector{1,2,3,4};
    auto const a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << a1 * 5;
	CHECK(oss.str() == "[5 10 15 20]");
}

TEST_CASE("Division") {
	auto const a1 = comp6771::euclidean_vector{1,2,3,4};
    auto const a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << a1 / 2;
	CHECK(oss.str() == "[0.5 1 1.5 2]");
}

TEST_CASE("Compound Addition") {
    auto a1 = comp6771::euclidean_vector{1,2,3,4};
    auto a2 = comp6771::euclidean_vector{4,3,2,1};
    auto a3 = a1;
    a3 += a2;
	auto oss = std::ostringstream{};
	oss << a3;
	CHECK(oss.str() == "[5 5 5 5]");
}

TEST_CASE("Compound Substraction") {
	auto a1 = comp6771::euclidean_vector{1,2,3,4};
    auto a2 = comp6771::euclidean_vector{4,3,2,1};
    auto a3 = a1;
    a3 -= a2;
	auto oss = std::ostringstream{};
	oss << a3;
	CHECK(oss.str() == "[-3 -1 1 3]");
}

TEST_CASE("Compound Multiplication") {
	auto a1 = comp6771::euclidean_vector{1,2,3,4};
    auto a2 = comp6771::euclidean_vector{4,3,2,1};
    auto a3 = a1;
    a3 *= 5;
	auto oss = std::ostringstream{};
	oss << a3;
	CHECK(oss.str() == "[5 10 15 20]");
}

TEST_CASE("Compound Division") {
	auto a1 = comp6771::euclidean_vector{1,2,3,4};
    auto a2 = comp6771::euclidean_vector{4,3,2,1};
    auto a3 = a1;
    a3 /= 2;
	auto oss = std::ostringstream{};
	oss << a3;
	CHECK(oss.str() == "[0.5 1 1.5 2]");
}

TEST_CASE("Unary plus") {
	auto a1 = comp6771::euclidean_vector{1, 2, 3, 4};
	auto oss = std::ostringstream{};
	oss << +a1;
	CHECK(oss.str() == "[1 2 3 4]");
}

TEST_CASE("negatation") {
	auto a1 = comp6771::euclidean_vector{1, 2, 3, 4};
	auto oss = std::ostringstream{};
	oss << -a1;
	CHECK(oss.str() == "[-1 -2 -3 -4]");
}
