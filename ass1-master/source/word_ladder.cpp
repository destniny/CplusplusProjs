#include "comp6771/word_ladder.hpp"
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace word_ladder {
	auto read_lexicon(std::string const& path) -> std::unordered_set<std::string>;

	auto str_cmp(std::string str1, std::string str2) -> int{
		auto count = 0;
		for (unsigned long i = 0; i < str1.size(); i++){
			if (str1[i] != str2[i]) count++;
		}
		return count;
	}

	void print_vector(std::vector<std::string> vec){
		for (auto any : vec){
			std::cout << any << " ";
		}
		std::cout << std::endl;
	}

	// Given a start word and destination word, returns all the shortest possible paths from the
	// start word to the destination, where each word in an individual path is a valid word per the
	// provided lexicon. Pre: ranges::size(from) == ranges::size(to) Pre: valid_words.contains(from)
	// and valid_words.contains(to)
	auto generate(std::string const& from,
								std::string const& to,
								std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>>{

		// 1. get only same length words into graph_set
		// std::cout << from << std::endl;
		// std::cout << to << std::endl;

		std::unordered_set<std::string>::iterator it;

		std::unordered_set<std::string> graph_set;
		unsigned long const input_size = from.size();

		// std::cout << lexicon << std::endl;
		// std::qsort(lexicon, lexicon.size(), );
		for (it = lexicon.begin(); it != lexicon.end(); ++it){
			auto str = *it;
			if (str.size() == input_size){
				graph_set.insert(str);
			}
			// std::cout << str.size() << std::endl;
		}

		// 2. Constrcut graph
		std::unordered_map<std::string, std::vector<std::string>> graph;

		for (it = graph_set.begin(); it != graph_set.end(); ++it){
			auto str = *it;
			std::vector<std::string> entries;
			graph.insert({str, entries});
		}

		std::unordered_set<std::string>::iterator it_inner;

		for (it = graph_set.begin(); it != graph_set.end(); ++it){
			auto str = *it;
			// std::cout << str << std::endl;
			// another iterator to loop till the end of set
			it_inner = it;
			++it_inner;
			for (;it_inner != graph_set.end(); ++it_inner){
				auto str1 = *it_inner;
				auto out = str_cmp(str, str1);
				if (out == 1){
					// it is an connection
					graph[str].push_back(str1);
					graph[str1].push_back(str);
				}
			}
		}

		// BFS algo
		std::vector<std::vector<std::string>> res;
		std::vector<std::string> cur_path = {from};
		std::queue<std::vector<std::string>> bfs_queue;
		// std::unordered_map<std::string, std::vector<std::string>> parent;
		bfs_queue.push(cur_path);
		std::unordered_set<std::string> bfs_seen_set = {from};
		auto tem_flag = 0;
		// auto i = 0;
		// while (i < 100){
		while (!bfs_queue.empty()) {
			cur_path = bfs_queue.front();
			// print_vector(cur_path);
			bfs_queue.pop();
			auto cur_word = cur_path.back();
			// std::cout << cur_word << std::endl;
			std::vector<std::string> entries = graph[cur_word];
			for (auto const &vec: entries){
				if (!bfs_seen_set.count(vec) and !tem_flag){
					bfs_seen_set.insert(vec);
					if (vec == to){
						tem_flag = 1;
						cur_path.push_back(vec);
						res.push_back(cur_path);
						break;
					}else{
						auto tmp = cur_path;
						tmp.push_back(vec);
						bfs_queue.push(tmp);
					}

				}
			}
			// i++;
		}

		for (auto any: res){
			for (auto k: any){
				std::cout << k << "<-";
			}
			std::cout << std::endl;
		}

		// std::cout << "For work" << std::endl;
		// for (auto any: graph["work"]){
		// 	std::cout << any << " ";
		// }
		// std::cout << std::endl;

		return res;

	}




	// auto graph_gen() -> {

	// }
} // namespace word_ladder
