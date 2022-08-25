#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gdwg/graph.hpp"
using namespace std;
using namespace gdwg;

auto main() -> int {
	ostringstream out, out2;
	auto g = graph<std::string, int>{};
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

	auto g2 = graph<std::string, int>(g);
	out2 << g2;
	// assert(out.str()==out2.str());
	auto g3 = graph<string, int>();

	out = ostringstream();
	out << g3;
	// assert(out.str()=="()");

	g = {"abc", "123", "qwq"};
	g.insert_edge("abc", "qwq", -123);
	out = ostringstream();
	out << g;
	// assert(out.str()=="(abc\n(\n	qwq | -123 \n)\n)");
	vector<int> ls1 = {1, 2, 3, 4};
	auto g4 = graph<int, int>(1, 5);
	// assert(g4.nodes()==ls1);
	g = g2;
	g3 = move(g2);
	// assert(g==g3);

	g2 = g3;
	g3 = graph<string, int>(g2);
	g3 = graph<string, int>(move(g2));
	// assert(g==g3);

	auto g5 = graph<int, int>(1, 5);
	g4.insert_edge(1, 3, -1);
	g5.insert_edge(1, 3, -1);
	g4.insert_edge(3, 4, 2);
	g5.insert_edge(3, 4, 2);
	g5.insert_node(5);
	g5.erase_node(3);
	g5.insert_edge(1, 5, -1);
	g5.insert_edge(5, 4, 2);

	g4.replace_node(3, 5);
	// assert(g4==g5);

	g5.insert_edge(2, 4, 4);
	g4.insert_edge(5, 4, 4);
	g5.merge_replace_node(2, 5);
	// assert(!(g5==g4));
	g4.erase_node(2);
	// assert(g5==g4);
	g4.insert_edge(1, 4, 8);

	g4.erase_edge(1, 4, 8);
	// assert(g5==g4);
	g4.clear();
	// assert(g4==(graph<int,int>()));
	// assert(g5.is_node(5));
	// assert(!g5.is_node(3));
	// assert(!g5.empty());
	// assert(g4.empty());
	// assert(g.is_connected("hello","how"));
	// assert(!g.is_connected("hello","you?"));
	// assert((g.weights("hello","are")==vector<int>{8,2}));
	// assert((g.connections("hello")==vector<string>{"are","how"}));
	// This is a structured binding.
	// https://en.cppreference.com/w/cpp/language/structured_binding
	// It allows you to unpack your tuple.
	// for (auto const& [from, to, weight] : g) {
	// 	std::cout << from << " -> " << to << " (weight " << weight << ")\n";
	// }
}
