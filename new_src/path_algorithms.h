#ifndef PATH_ALGOS_H
#define PATH_ALGOS_H

#include <memory>
#include "path_algorithms_structs.h"
#include "node_expander_path_algorithms.h"


template<typename G, typename N>
bool path_exists(G graph_data, N start_node, N goal_node)
{

	using weight_type = typename G::element_type::weight_type;
	using path_state_type = path_state<G, N, weight_type>;
	shared_ptr<path_state_type> start_state = make_shared<path_state_type>(start_node, 0, nullptr, graph_data);
	shared_ptr<path_state_type> goal_state = make_shared<path_state_type>(goal_node, 0, nullptr, graph_data);
	return path_exists(start_state, goal_state);
}

template<typename G, typename N>
void find_path_dfs(G graph_data, N start_node, N goal_node)
{
	using weight_type = typename G::element_type::weight_type;
	using path_state_type = path_state<G, N, weight_type>;
	shared_ptr<path_state_type> start_state = make_shared<path_state_type>(start_node, 0, nullptr, graph_data);
	shared_ptr<path_state_type> goal_state = make_shared<path_state_type>(goal_node, 0, nullptr, graph_data);
	auto path_data = find_path_dfs(start_state, goal_state);
	auto string_path = path_data->to_string();
	cout << string_path << '\n';
}

template<typename G, typename N>
void find_path_bfs(G graph_data, N start_node, N goal_node)
{
	using weight_type = typename G::element_type::weight_type;
	using path_state_type = path_state<G, N, weight_type>;
	shared_ptr<path_state_type> start_state = make_shared<path_state_type>(start_node, 0, nullptr, graph_data);
	shared_ptr<path_state_type> goal_state = make_shared<path_state_type>(goal_node, 0, nullptr, graph_data);
	auto path_data = find_path_bfs(start_state, goal_state);
	auto string_path = path_data->to_string();
	cout << string_path << '\n';
}

template<typename G, typename N>
void find_path_ucs(G graph_data, N start_node, N goal_node)
{
	using weight_type = typename G::element_type::weight_type;
	using path_state_type = path_state<G, N, weight_type>;
	shared_ptr<path_state_type> start_state = make_shared<path_state_type>(start_node, 0, nullptr, graph_data);
	shared_ptr<path_state_type> goal_state = make_shared<path_state_type>(goal_node, 0, nullptr, graph_data);
	auto path_data = find_path_ucs(start_state, goal_state);
	auto string_path = path_data->to_string();
	cout << string_path << '\n';
}

#endif
