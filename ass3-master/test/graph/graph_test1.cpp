#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>

TEST_CASE("basic test") {
	auto g = gdwg::graph<int, std::string>{};
	auto n = 5;
	g.insert_node(n);
	CHECK(g.is_node(n));
}

TEST_CASE("my test") {
	std::ostringstream out, out2;
	auto g = gdwg::graph<std::string, int>{};
	g.insert_node("hello");
	g.insert_node("how");
	g.insert_node("are");
	g.insert_node("you?");

	g.insert_edge("hello", "how", 5);
	g.insert_edge("hello", "are", 8);
	g.insert_edge("hello", "are", 2);

	g.insert_edge("how", "you?", 1);
	g.insert_edge("how", "hello", 4);

	g.insert_edge("are", "you?", 3);

	out << g;

	auto g2 = gdwg::graph<std::string, int>(g);
	out2 << g2;
	CHECK(out.str() == out2.str());

	auto g3 = gdwg::graph<std::string, int>();

	out = std::ostringstream();
	out << g3;
	CHECK(out.str() == "()");

	g = {"abc", "123", "qwq"};
	g.insert_edge("abc", "qwq", -123);
	out = std::ostringstream();
	out << g;
	CHECK(out.str() == "(abc\n(\n	qwq | -123 \n)\n)");
	std::vector<int> ls1 = {1, 2, 3, 4};
	auto g4 = gdwg::graph<int, int>(1, 5);
	CHECK(g4.nodes() == ls1);
	g = g2;
	g3 = move(g2);
	CHECK(g == g3);

	g2 = g3;
	g3 = gdwg::graph<std::string, int>(g2);
	g3 = gdwg::graph<std::string, int>(move(g2));
	CHECK(g == g3);

	auto g5 = gdwg::graph<int, int>(1, 5);
	g4.insert_edge(1, 3, -1);
	g5.insert_edge(1, 3, -1);
	g4.insert_edge(3, 4, 2);
	g5.insert_edge(3, 4, 2);
	g5.insert_node(5);
	g5.erase_node(3);
	g5.insert_edge(1, 5, -1);
	g5.insert_edge(5, 4, 2);

	g4.replace_node(3, 5);
	CHECK(g4 == g5);

	g5.insert_edge(2, 4, 4);
	g4.insert_edge(5, 4, 4);
	g5.merge_replace_node(2, 5);
	CHECK(!(g5 == g4));
	g4.erase_node(2);
	CHECK(g5 == g4);
	g4.insert_edge(1, 4, 8);

	g4.erase_edge(1, 4, 8);
	CHECK(g5 == g4);
	g4.clear();
	CHECK(g4 == (gdwg::graph<int, int>()));
	CHECK(g5.is_node(5));
	CHECK(!g5.is_node(3));
	CHECK(!g5.empty());
	CHECK(g4.empty());
	CHECK(g.is_connected("hello", "how"));
	CHECK(!g.is_connected("hello", "you?"));
	CHECK((g.weights("hello", "are") == std::vector<int>{8, 2}));
	CHECK((g.connections("hello") == std::vector<std::string>{"are", "how"}));
}
