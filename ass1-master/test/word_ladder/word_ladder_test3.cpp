#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"

TEST_CASE("work -> play 2") {
	auto const english_lexicon = word_ladder::read_lexicon("./test/word_ladder/english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	std::vector<std::string> golden1 = {"work", "fork", "form", "foam", "flam", "flay", "play"};
	CHECK(golden1 == ladders[0]);

	std::vector<std::string> golden2 = {"work", "pork", "perk", "peak", "pean", "plan", "play"};
	CHECK(golden2 == ladders[1]);

	std::vector<std::string> golden3 = {"work", "pork", "perk", "peak", "peat", "plat", "play"};
	CHECK(golden3 == ladders[2]);

	std::vector<std::string> golden4 = {"work", "pork", "perk", "pert", "peat", "plat", "play"};
	CHECK(golden4 == ladders[3]);

	std::vector<std::string> golden5 = {"work", "pork", "porn", "pirn", "pian", "plan", "play"};
	CHECK(golden5 == ladders[4]);

	std::vector<std::string> golden6 = {"work", "pork", "port", "pert", "peat", "plat", "play"};
	CHECK(golden6 == ladders[5]);

	std::vector<std::string> golden7 = {"work", "word", "wood", "pood", "plod", "ploy", "play"};
	CHECK(golden7 == ladders[6]);

	std::vector<std::string> golden8 = {"work", "worm", "form", "foam", "flam", "flay", "play"};
	CHECK(golden8 == ladders[7]);

	std::vector<std::string> golden9 = {"work", "worn", "porn", "pirn", "pian", "plan", "play"};
	CHECK(golden9 == ladders[8]);

	std::vector<std::string> golden10 = {"work", "wort", "bort", "boat", "blat", "plat", "play"};
	CHECK(golden10 == ladders[9]);

	std::vector<std::string> golden11 = {"work", "wort", "port", "pert", "peat", "plat", "play"};
	CHECK(golden11 == ladders[10]);

	std::vector<std::string> golden12 = {"work", "wort", "wert", "pert", "peat", "plat", "play"};
	CHECK(golden12 == ladders[11]);
}