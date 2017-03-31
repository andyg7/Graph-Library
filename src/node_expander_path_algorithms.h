#ifndef NODE_EXPANDER_PATH_ALGORITHMS_H
#define NODE_EXPANDER_PATH_ALGORITHMS_H

#include <iostream>
#include <memory>
#include <set>
#include <queue>
#include "graph_concepts.h"
#include "function_objs.h"
#include "path_algorithms_structs.h"

using namespace std;

template<typename V>
bool path_exists(V v, V g)
{
	list<V> frontier;
	return path_exists_generic(v, g, frontier, [](list<V>& q, V& v) { q.push_front(v); }, [](list<V>& q) { q.pop_back(); }, [](list<V>& q) { return q.back(); });
}

template<typename V, typename F, typename Insert, typename Remove, typename Top>
bool path_exists_generic(V v, V g, F f, Insert in, Remove rem, Top top)
{
	typedef typename V::element_type element_type;
	bool debug_on = false;
	vector<element_type> path;
	unordered_set<element_type> visited_nodes;
	unordered_set<element_type> frontier_helper;
	F frontier = f;
	in(frontier, v);
	frontier_helper.insert(*v);
	while (!frontier.empty()) {
		V curr_node = top(frontier);
		visited_nodes.insert(*curr_node);
		rem(frontier);
		auto tmp_it = frontier_helper.find(*curr_node);
		frontier_helper.erase(tmp_it);

		vector<V> children = curr_node->expand();
		for (auto c : children) {
			if (*c == *g) {
				return true;
			}
			if (visited_nodes.find(*c) == visited_nodes.end() && frontier_helper.find(*c) == frontier_helper.end()) {
				in(frontier, c);
				frontier_helper.insert(*c);
			}
		}
	}
	return false;
}

template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_dfs(V v, V g)
{
	list<V> frontier;
	return find_path_generic(v, g, frontier, [](list<V>& q, V& v) { q.push_back(v); }, [](list<V>& q) { q.pop_back(); }, [](list<V>& q) { return q.back(); });
}

template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_bfs(V v, V g)
{
	list<V> frontier;
	return find_path_generic(v, g, frontier, [](list<V>& q, V& v) { q.push_front(v); }, [](list<V>& q) { q.pop_back(); }, [](list<V>& q) { return q.back(); });
}

template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_ucs(V v, V g)
{
	typedef priority_queue<V, vector<V>, GreaterThanCost<V>> queue_type;
	queue_type pq;
	return find_path_generic(v, g, pq, [](queue_type& q, V& v) { q.push(v); }, [](queue_type& q) { q.pop(); }, [](queue_type& q) { return q.top(); });
}

template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_ast(V v, V g)
{
	typedef priority_queue<V, vector<V>, HeuristicGreaterThanCost<V>> queue_type;
	queue_type pq;
	return find_path_generic(v, g, pq, [](queue_type& q, V& v) { q.push(v); }, [](queue_type& q) { q.pop(); }, [](queue_type& q) { return q.top(); });
}

template<typename V, typename F, typename Insert, typename Remove, typename Top>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_generic(V v, V g, F f, Insert in, Remove rem, Top top)
{
	typedef typename V::element_type element_type;
	typedef typename V::element_type::cost_type cost_type;
	bool debug_on = false;
	unordered_set<typename V::element_type> visited_nodes;
	F frontier = f;
	in(frontier, v);
	while (!frontier.empty()) {
		if (debug_on) {
			cout << "still looping\n";
			cout << "frontier size" << frontier.size() << '\n';
		}
		V curr_node = top(frontier);
		visited_nodes.insert(*curr_node);
		if (*curr_node == *g) {
			vector<element_type> path;
			vector<string> string_path;
			if (debug_on) {
				cout << "found goal state\n";
			}
			path.push_back(*curr_node);
			string_path.push_back((*curr_node).to_string());
			cost_type total_cost = (curr_node->cost);
			shared_ptr<element_type> curr_v = curr_node->parent;
			while (curr_v != nullptr) {
				path.push_back(*curr_v);
				string t_s = curr_v->to_string();
				string_path.push_back(t_s);
				curr_v = curr_v->parent;
			}
			reverse(path.begin(), path.end());
			reverse(string_path.begin(), string_path.end());
			shared_ptr<path_data<element_type, cost_type>> found_path_data = make_shared<path_data<element_type, cost_type>>();
			found_path_data->path_v = path;
			found_path_data->path_v_stringified = string_path;
			found_path_data->cost = total_cost;
			return found_path_data;
		}
		rem(frontier);
		vector<V> children = curr_node->expand();
		for (auto c : children) {
			if (visited_nodes.find(*c) == visited_nodes.end()) {
				in(frontier, c);
			}
		}
	}
	shared_ptr<struct path_data<element_type, cost_type>> found_path_data = make_shared<path_data<element_type, cost_type>>();
	vector<element_type> path;
	found_path_data->path_v = path;
	return found_path_data;
}

#endif
