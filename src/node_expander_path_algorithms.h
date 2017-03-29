#ifndef NODE_EXPANDER_PATH_ALGORITHMS_H
#define NODE_EXPANDER_PATH_ALGORITHMS_H

#include <iostream>
#include <memory>
#include <set>
#include <queue>
#include "graph_concepts.h"
#include "graph_lib_headers.h"
#include "function_objs.h"
#include "path_algorithms_structs.h"

using namespace std;

template<typename V>
bool path_exists(V v, V g)
{
	list<V> frontier;
	return path_exists_generic(v, g, frontier, [](list<V>& q, V& v) { q.push_front(v); }, [] (list<V>& q) { q.pop_back(); }, [] (list<V>& q) { return q.back(); });
}

template<typename V, typename F, typename Insert, typename Remove, typename Top>
bool path_exists_generic(V v, V g, F f, Insert in, Remove rem, Top top)
{
	bool debug_on = false;
	vector<typename V::element_type> path;
	unordered_set<typename V::element_type> visited_nodes;
	F frontier = f;
	in(frontier, v);
	bool first_it = true;
	while (!frontier.empty()) {
		if (debug_on) {
			cout << "still looping\n";
			cout << "frontier size" << frontier.size() << '\n';
		}
		V curr_node = top(frontier);
		visited_nodes.insert(*curr_node);
		if (*curr_node == *g && first_it == false) {
			return true;
		}
		rem(frontier);
		vector<V> children = curr_node->expand();
		for (auto c : children) {
			if (visited_nodes.find(*c) == visited_nodes.end()) {
				in(frontier, c);
			}
		}
		first_it = false;
	}
	return false;
}
template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_dfs(V v, V g)
{
	list<V> frontier;
	return find_path_generic(v, g, frontier, [](list<V>& q, V& v) { q.push_back(v); }, [] (list<V>& q) { q.pop_back(); }, [] (list<V>& q) { return q.back(); });
}

template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_bfs(V v, V g)
{
	list<V> frontier;
	return find_path_generic(v, g, frontier, [](list<V>& q, V& v) { q.push_front(v); }, [] (list<V>& q) { q.pop_back(); }, [] (list<V>& q) { return q.back(); });
}


template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_ucs(V v, V g)
{
	typedef priority_queue<V, vector<V>, GreaterThanCost<V>> queue_type;
	queue_type pq;
	return find_path_generic(v, g, pq, [](queue_type& q, V& v) { q.push(v); }, [] (queue_type& q) { q.pop(); }, [] (queue_type& q) { return q.top(); });
}

template<typename V>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_ast(V v, V g)
{
	typedef priority_queue<V, vector<V>, HeuristicGreaterThanCost<V>> queue_type;
	queue_type pq;
	return find_path_generic(v, g, pq, [](queue_type& q, V& v) { q.push(v); }, [] (queue_type& q) { q.pop(); }, [] (queue_type& q) { return q.top(); });
}

template<typename V, typename F, typename Insert, typename Remove, typename Top>
shared_ptr<struct path_data<typename V::element_type, typename V::element_type::cost_type>> find_path_generic(V v, V g, F f, Insert in, Remove rem, Top top)
{
	typedef typename V::element_type element_type;
	typedef typename V::element_type::cost_type cost_type;
	bool debug_on = false;
	vector<typename V::element_type> path;
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
			if (debug_on) {
				cout << "found goal state\n";
			}
			path.push_back(*curr_node);
			shared_ptr<typename V::element_type> curr_v = curr_node->parent;
			while (curr_v != nullptr) {
				path.push_back(*curr_v);
				curr_v = curr_v->parent;
			}
			reverse(path.begin(), path.end());
			shared_ptr<path_data<element_type, cost_type>> found_path_data = make_shared<path_data<element_type, cost_type>>();
			found_path_data->path_v = path;
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
	found_path_data->path_v = path;
	return found_path_data;
}

#endif
