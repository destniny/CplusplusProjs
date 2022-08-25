#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("Constructor1") {
	auto const a1 = comp6771::euclidean_vector();
	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[]");
}

TEST_CASE("Constructor2") {
	auto const a1 = comp6771::euclidean_vector(4);
	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[0 0 0 0]");
}

TEST_CASE("Constructor3") {
	auto const a1 = comp6771::euclidean_vector(3,5.0);
	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[5 5 5]");
}

TEST_CASE("Constructor4") {
	std::vector<double> ls1({1,2,3,4,5});
	auto const a1 = comp6771::euclidean_vector(ls1.begin(),ls1.end());
	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[1 2 3 4 5]");
}

TEST_CASE("Constructor5") {
	auto const a1 = comp6771::euclidean_vector{5.3,3.2,57.4,4.3,2.8};
	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[5.3 3.2 57.4 4.3 2.8]");
}

TEST_CASE("Constructor6") {
	auto const a1 = comp6771::euclidean_vector(3, 3.0);
	auto const a2 = comp6771::euclidean_vector(a1);
	auto oss = std::ostringstream{};
	oss << a2;
	CHECK(oss.str() == "[3 3 3]");
}

TEST_CASE("Constructor7") {
	auto const a1 = comp6771::euclidean_vector(3, 3.0);
	auto const a2 = comp6771::euclidean_vector(std::move(a1));
	auto oss = std::ostringstream{};
	oss << a2;
	CHECK(oss.str() == "[3 3 3]");
}

TEST_CASE("Constructor8") {
	auto const a1 = comp6771::euclidean_vector{1,2,3,4};
	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[1 2 3 4]");
}

TEST_CASE("Constructor9") {
	auto const a2 = comp6771::euclidean_vector{4,3,2,1};
	auto oss = std::ostringstream{};
	oss << (a2==comp6771::euclidean_vector{4,3,2,1});
	CHECK(oss.str() == "1");
	oss = std::ostringstream{};
	oss << (a2!=comp6771::euclidean_vector{4,3,2,1});
	CHECK(oss.str() == "0");
}
