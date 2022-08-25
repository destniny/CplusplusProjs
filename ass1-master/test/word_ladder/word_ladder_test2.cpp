#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"

TEST_CASE("work -> play") {
	auto const english_lexicon = word_ladder::read_lexicon("./test/word_ladder/english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	CHECK(std::size(ladders) == 12);
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));

	CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"at", "it"}) == 5);
}