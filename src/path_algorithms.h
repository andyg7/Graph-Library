#ifndef PATH_ALGORITHMS_H
#define PATH_ALGORITHMS_H

#include <iostream>
#include <memory>
#include "graph_concepts.h"
#include "graph_structs.h"
#include "function_objs.h"
#include "node_expander_path_algorithms.h"

using namespace std;
using namespace graph_std_lib;

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<path_state<G, typename G::edge_type::cost_type>> generate_state(G& g, V x)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;
	auto it = g.underlying_data.begin();
	auto it_end = g.underlying_data.end();
	for (; it != it_end; it++) {
		if (((*it).vertex_wrapper_data)->vertex_data == *x) {
			break;
		}
	}
	shared_ptr<path_state_type> state = make_shared<path_state_type>(it->vertex_wrapper_data, 0, nullptr, g);
	return state;
}

template<typename G>
requires Graph<G>
bool cycle_exists(G& g)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;
	auto it = g.underlying_data.begin();
	auto it_end = g.underlying_data.end();

	for (; it != it_end; it++) {
		shared_ptr<path_state_type> start_state = make_shared<path_state_type>(it->vertex_wrapper_data, 0, nullptr, g);
		if (path_exists(start_state, start_state)) {
			return true;
		}
	}
	return false;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool cycle_exists(G& g, V v)
{
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;

	shared_ptr<path_state_type> start_state = generate_state(g, v);
	if (path_exists(start_state, start_state)) {
		return true;
	}
	return false;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool path_exists(G& g, V x, V y)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;

	shared_ptr<path_state_type> start_state = generate_state(g, x);
	shared_ptr<path_state_type> goal_state = generate_state(g, y);

	return path_exists(start_state, goal_state);
}

/*
   Uses DFS to find a path (not optimal)
 */
template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<struct path_data<typename G::vertex_type, typename G::edge_type::cost_type>> find_path_dfs(G& g, V x, V y)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;

	shared_ptr<path_state_type> start_state = generate_state(g, x);
	shared_ptr<path_state_type> goal_state = generate_state(g, y);

	auto helper_path_data = find_path_dfs(start_state, goal_state);

	vector<vertex_type> path; 
	for (auto n : helper_path_data->path_v) {
		path.push_back((n.vertex_wrapper_data)->vertex_data);
	}
	shared_ptr<struct path_data<vertex_type, cost_type>> path_d = make_shared<struct path_data<vertex_type, cost_type>>();
	path_d->path_v = path;
	path_d->path_v_stringified = helper_path_data->path_v_stringified;
	path_d->cost = helper_path_data->cost;
	return path_d;
}

/*
   Uses BFS to find a path (not optimal)
 */
template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<struct path_data<typename G::vertex_type, typename G::edge_type::cost_type>> find_path_bfs(G& g, V x, V y)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;

	shared_ptr<path_state_type> start_state = generate_state(g, x);
	shared_ptr<path_state_type> goal_state = generate_state(g, y);

	auto helper_path_data = find_path_bfs(start_state, goal_state);

	vector<vertex_type> path; 
	for (auto n : helper_path_data->path_v) {
		path.push_back((n.vertex_wrapper_data)->vertex_data);
	}
	shared_ptr<struct path_data<vertex_type, cost_type>> path_d = make_shared<struct path_data<vertex_type, cost_type>>();
	path_d->path_v = path;
	path_d->path_v_stringified = helper_path_data->path_v_stringified;
	path_d->cost = helper_path_data->cost;
	return path_d;
}

/*
   Uses UCS to find shortest path
 */
template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<struct path_data<typename G::vertex_type, typename G::edge_type::cost_type>> find_path_ucs(G& g, V x, V y)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;
	shared_ptr<path_state_type> start_state = generate_state(g, x);
	shared_ptr<path_state_type> goal_state = generate_state(g, y);

	auto helper_path_data = find_path_ucs(start_state, goal_state);

	vector<vertex_type> path; 
	for (auto n : helper_path_data->path_v) {
		path.push_back((n.vertex_wrapper_data)->vertex_data);
	}
	shared_ptr<struct path_data<vertex_type, cost_type>> path_d = make_shared<struct path_data<vertex_type, cost_type>>();
	path_d->path_v = path;
	path_d->path_v_stringified = helper_path_data->path_v_stringified;
	path_d->cost = helper_path_data->cost;
	return path_d;
}

/*
   Uses AST to find shortest path
 */
template<typename G, typename V>
requires Heuristic_graph<G> && Vertex_ptr<V>
shared_ptr<struct path_data<typename G::vertex_type, typename G::edge_type::cost_type>> find_path_ast(G& g, V x, V y)
{
	typedef typename G::vertex_type vertex_type;
	typedef typename G::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;
	shared_ptr<path_state_type> start_state = generate_state(g, x);
	shared_ptr<path_state_type> goal_state = generate_state(g, y);

	auto helper_path_data = find_path_ast(start_state, goal_state);

	vector<vertex_type> path; 
	for (auto n : helper_path_data->path_v) {
		path.push_back((n.vertex_wrapper_data)->vertex_data);
	}
	shared_ptr<struct path_data<vertex_type, cost_type>> path_d = make_shared<struct path_data<vertex_type, cost_type>>();
	path_d->path_v = path;
	path_d->path_v_stringified = helper_path_data->path_v_stringified;
	path_d->cost = helper_path_data->cost;
	return path_d;
}

#endif
