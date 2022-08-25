#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
// TODO: Make this graph generic
//       ... this won't just compile
//       straight away
namespace gdwg {
	template<class N, class E>
	class graph {
	public:
		struct value_type {
			N a;
			N b;
			E v;
		};
		std::map<N, std::map<N, std::set<std::shared_ptr<E>>>> G;
		std::map<E, std::shared_ptr<E>> pointer;
		std::set<N> node;
		void adde(N a, N b, std::shared_ptr<E> v) {
			G[a][b].insert(v);
		}
		void reset() {
			G.clear();
			node.clear();
			pointer.clear();
		}
		graph() {
			reset();
		}
		graph(std::initializer_list<N> il) {
			reset();
			for (auto i = il.begin(); i != il.end(); ++i)
				node.insert(*i);
		}
		template<typename InputIt>
		graph(InputIt first, InputIt last) {
			reset();
			for (auto i = first; i != last; ++i) {
				node.insert(*i);
			}
		}
		graph(graph&& other) noexcept {
			G = other.G;
			node = other.node;
			pointer = other.pointer;
		}
		auto operator=(graph&& other) noexcept -> graph& {
			G = other.G;
			node = other.node;
			pointer = other.pointer;
			return *this;
		}
		graph(graph const& other) {
			G = other.G;
			node = other.node;
			pointer = other.pointer;
		}
		auto operator=(graph const& other) -> graph& {
			G = other.G;
			node = other.node;
			pointer = other.pointer;
			return *this;
		}
		auto insert_node(N const& value) -> bool {
			if (node.count(value))
				return false;
			node.insert(value);
			return true;
		}
		auto insert_edge(N const& src, N const& dst, E const& weight) -> bool {
			if (pointer.count(weight) && G[src][dst].count(pointer[weight])) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::insert_edge when either src "
				                         "or dst node does not exist");
				return false;
			}
			if (!pointer.count(weight))
				pointer[weight] = std::shared_ptr<E>(new E(weight));
			adde(src, dst, pointer[weight]);
			return true;
		}
		auto replace_node(N const& old_data, N const& new_data) -> bool {
			if (node.count(new_data)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::replace_node on a node that "
				                         "doesn't exist");
				return false;
			}
			G[new_data] = G[old_data];
			G.erase(old_data);
			node.insert(new_data);
			node.erase(old_data);
			for (typename std::map<N, std::map<N, std::set<std::shared_ptr<E>>>>::iterator it =
			        G.begin();
			     it != G.end();
			     ++it)
			{
				if (it->second.count(old_data)) {
					it->second[new_data] = it->second[old_data];
					it->second.erase(old_data);
				}
			}
			return true;
		}
		void merge(std::set<std::shared_ptr<E>>& a, std::set<std::shared_ptr<E>> b) {
			for (typename std::set<std::shared_ptr<E>>::iterator it = b.begin(); it != b.end(); ++it)
				a.insert(*it);
		}
		auto merge_replace_node(N const& old_data, N const& new_data) -> void {
			if (!node.count(new_data) || !node.count(old_data)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::merge_replace_node on old or "
				                         "new data if they don't exist in the graph");
				return;
			}
			for (typename std::map<N, std::set<std::shared_ptr<E>>>::iterator it = G[old_data].begin();
			     it != G[old_data].end();
			     ++it)
			{
				merge(G[new_data][it->first], it->second);
			}
			G.erase(old_data);
			node.erase(old_data);
			for (typename std::map<N, std::map<N, std::set<std::shared_ptr<E>>>>::iterator it =
			        G.begin();
			     it != G.end();
			     ++it)
			{
				if (it->second.count(old_data)) {
					merge(it->second[new_data], it->second[old_data]);
					it->second.erase(old_data);
				}
			}
		}
		auto erase_node(N const& value) -> bool {
			node.erase(value);
			G.erase(value);
			for (typename std::map<N, std::map<N, std::set<std::shared_ptr<E>>>>::iterator it =
			        G.begin();
			     it != G.end();
			     ++it)
			{
				it->second.erase(value);
			}
			return true;
		}
		auto erase_edge(N const& src, N const& dst, E const& weight) -> bool {
			if (!node.count(src) || !node.count(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::erase_edge on src or dst if "
				                         "they don't exist in the graph");
				return false;
			}
			if (!G.count(src))
				return true;
			if (!G[src].count(dst))
				return true;
			if (pointer.count(weight))
				G[src][dst].erase(pointer[weight]);
			return true;
			return false;
		}
		auto clear() noexcept -> void {
			reset();
		}
		auto is_node(N const& value) const -> bool {
			return node.count(value);
		}
		auto empty() const -> bool {
			return node.empty();
		}
		auto is_connected(N const& src, N const& dst) const -> bool {
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::is_connected if src or dst "
				                         "node don't exist in the graph");
				return false;
			}
			auto ls = G;
			return ls[src][dst].size();
		}
		auto nodes() const -> std::vector<N> {
			std::vector<N> ans;
			for (typename std::set<N>::iterator it = node.begin(); it != node.end(); ++it)
				ans.push_back(*it);
			return ans;
		}
		auto weights(N const& src, N const& dst) const -> std::vector<E> {
			std::vector<E> ans;
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::weights if src or dst node "
				                         "don't exist in the graph");
				return ans;
			}
			auto ls = G;
			for (typename std::set<std::shared_ptr<E>>::iterator it = ls[src][dst].begin();
			     it != ls[src][dst].end();
			     ++it)
				ans.push_back(**it);
			return ans;
		}
		// auto erase_edge(iterator i) -> iterator;
		// auto erase_edge(iterator i, iterator s) -> iterator;

		// auto find(N const& src, N const& dst, E const& weight) -> iterator;
		auto connections(N const& src) const -> std::vector<N> {
			std::vector<N> ans;
			if (!is_node(src)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::connections if src doesn't "
				                         "exist in the graph");
				return ans;
			}
			auto ls = G;
			for (typename std::map<N, std::set<std::shared_ptr<E>>>::const_iterator it = ls[src].begin();
			     it != ls[src].end();
			     ++it)
				if (it->second.size())
					ans.push_back(it->first);
			return ans;
		}
		// auto begin() const -> iterator;
		// auto end() const -> iterator;
		auto operator==(graph const& other) -> bool {
			graph ls = other;
			if (node != ls.node)
				return false;
			std::stringstream a, b;
			a << *this;
			b << other;
			return a.str() == b.str();
			// for(auto it=G.begin();it!=G.end();++it)
			// {
			// 	if(it->second.size()!=ls.G[it->first].size())return false;
			// 	for(auto it2=it->second.begin();it2!=it->second.end();++it2)
			// 	{
			// 		if(it2->second.size()!=ls.G[it->first][it2->first].size())return false;
			// 		for(auto it3=it2->second.begin();it3!=it2->second.end();++it3)
			// 		{
			// 			int flag=0;
			// 			for(auto
			// it4=ls.G[it->first][it2->first].begin();it4!=ls.G[it->first][it2->first].end();++it4)
			// 			{
			// 				if(**it3==**it4)flag=1;
			// 			}
			// 			if(!flag)return false;
			// 		}
			// 	}
			// }
			return true;
		}
		friend auto operator<<(std::ostream& os, graph const& g) -> std::ostream& {
			os << '(';
			for (auto it = g.G.begin(); it != g.G.end(); ++it) {
				if (it->second.begin() != it->second.end())
					os << it->first << "\n(\n";
				for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
					if (it2->second.begin() != it2->second.end())
						os << "	" << it2->first << " | ";
					for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
						os << **it3 << ' ';
					}
					if (it2->second.begin() != it2->second.end())
						os << std::endl;
				}
				if (it->second.begin() != it->second.end())
					os << ")\n";
			}
			os << ')';
			return os;
		}
		class iterator {
		public:
			using reference = value_type;
			using pointer = void;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::bidirectional_iterator_tag;
			typename std::map<N, std::map<N, std::set<std::shared_ptr<E>>>>::iterator a, end;
			typename std::map<N, std::set<std::shared_ptr<E>>>::iterator b;
			typename std::set<std::shared_ptr<E>>::iterator c;
			int isend;
			// Iterator constructor
			iterator() = default;

			// Iterator source
			auto operator*() -> reference {
				value_type ans;
				ans.a = a->first;
				ans.b = b->first;
				ans.v = **c;
				return ans;
			}

			// Iterator traversal
			auto operator++() -> iterator& {
				iterator ans = *this;
				ans.isend = 0;
				ans.c++;
				if (ans.c == ans.b->second.end()) {
					ans.b++;
					if (ans.b == ans.a->second.end()) {
						ans.a++;
						if (ans.a == end) {
							ans.isend = 1;
							return ans;
						}
						ans.b = ans.a->second.begin();
					}
					ans.c = ans.b->second.begin();
				}
				return ans;
			}
			auto operator++(int) -> iterator {
				iterator ans = *this;
				ans.isend = 0;
				ans.c++;
				if (ans.c == ans.b->second.end()) {
					ans.b++;
					if (ans.b == ans.a->second.end()) {
						ans.a++;
						if (ans.a == end) {
							ans.isend = 1;
							return ans;
						}
						ans.b = ans.a->second.begin();
					}
					ans.c = ans.b->second.begin();
				}
				return ans;
			}

			// Iterator comparison
			auto operator==(iterator const& other) -> bool {
				return isend == other.isend;
			}

		private:
			// explicit iterator(unspecified);
		};
		auto begin() const -> iterator {
			iterator ans;

			ans.a = G.begin();
			ans.end = G.end();
			ans.b = ans.a->second.begin();
			ans.c = ans.b->second.begin();
			ans.isend = 0;
			return ans;
		}
		auto end() const -> iterator {
			iterator ans;
			ans.isend = 1;
			return ans;
		}

		// Your member functions go here
	private:
	};

} // namespace gdwg

#endif // GDWG_GRAPH_HPP
