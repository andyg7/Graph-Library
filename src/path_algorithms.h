/// \file
/// \brief The 4 main path algorithms are implemented here

#ifndef PATH_ALGORITHMS_H
#define PATH_ALGORITHMS_H

#include <iostream>
#include <memory>
#include "graph_concepts.h"
#include "function_objs.h"
#include "graph_lib_header_helper.h"
#include "node_expander_path_algorithms.h"

using namespace std;

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<path_state<G, typename G::element_type::edge_type::cost_type>> generate_state(G g, V x)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;
	auto v_w = get_vertex_wrapper(g, x);
	shared_ptr<path_state_type> state = make_shared<path_state_type>(v_w, 0, nullptr, g);
	return state;
}

template<typename G>
requires Graph<G>
bool cycle_exists(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;

	auto all_vertices = get_vertices(g);
	for (auto v : all_vertices) {
		shared_ptr<vertex_type> t_v = make_shared<vertex_type>(v);
		auto start_state = generate_state(g, t_v);
		if (path_exists(start_state, start_state)) {
			return true;
		}
	}
	return false;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool cycle_exists(G g, V v)
{
	typedef typename G::element_type::edge_type::cost_type cost_type;
	typedef path_state<G, cost_type> path_state_type;

	shared_ptr<path_state_type> start_state = generate_state(g, v);
	if (path_exists(start_state, start_state)) {
		return true;
	}
	return false;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool path_exists(G g, V x, V y)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
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
shared_ptr<struct path_data<typename G::element_type::vertex_type, typename G::element_type::edge_type::cost_type>> find_path_dfs(G g, V x, V y)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
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
shared_ptr<struct path_data<typename G::element_type::vertex_type, typename G::element_type::edge_type::cost_type>> find_path_bfs(G g, V x, V y)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
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
shared_ptr<struct path_data<typename G::element_type::vertex_type, typename G::element_type::edge_type::cost_type>> find_path_ucs(G g, V x, V y)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
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
shared_ptr<struct path_data<typename G::element_type::vertex_type, typename G::element_type::edge_type::cost_type>> find_path_ast(G g, V x, V y)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::edge_type::cost_type cost_type;
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
