#ifndef GRAPH_LIB_HEADER_H
#define GRAPH_LIB_HEADER_H

#include "graph_concepts.h"

template<typename G>
requires Graph<G> && Vertex_numeric_id<typename G::vertex_type>
shared_ptr<typename G::vertex_type> create_vertex(G&);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
shared_ptr<typename G::edge_type> create_edge(G&, V, V);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool add(G&, V);

template <typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool adjacent(G&, V, V);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool add_edge_blindly(Graph&, V, V);

template<typename G, typename V, typename E>
requires Graph_and_Vertex_ptr<G, V> && Graph_and_Edge_ptr<G, E>
bool add_edge_blindly_w_edge(G&, V, V, E);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool add_edge(G&, V, V);

template<typename G, typename E>
requires Graph_and_Edge_ptr<G, E>
bool add_edge(G&, E);

template<typename G, typename V>
requires DAG_Graph<G> && Graph_and_Vertex_ptr<G, V>
bool add_edge(G&, V, V);

template<typename G, typename E>
requires DAG_Graph<G> && Graph_and_Edge_ptr<G, E>
bool add_edge(G&, E);

template<typename G, typename V>
requires DT_Graph<G> && Graph_and_Vertex_ptr<G, V>
bool add_edge(G&, V, V);

template<typename G, typename E>
requires DT_Graph<G> && Graph_and_Edge_ptr<G, E>
bool add_edge(G&, E);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
Value value(G&, V);

template<typename G, typename E>
requires Graph_and_Edge_ptr<G, E>
Value value(G&, E);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
void set_value(G&, V, Value);

template<typename G, typename E>
requires Graph_and_Edge_ptr<G, E>
void set_value(G&, E, Value);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool vertex_exists(G&, V);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
void remove(G&, V);

template<typename G>
requires Vertex_numeric_id<typename G::vertex_type>
int get_unique_id(G&);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V> && Edge_cost<typename G::edge_type>
bool path_exists(G&, V, V);

template<typename G, typename V>
bool path_exists(G&, V, V);

template<typename G>
requires Graph<G>
bool cycle_exists(G&);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool has_parent(G&, V);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool has_child(G&, V);

template<typename G>
requires Graph<G>
shared_ptr<typename G::vertex_type> top(G&);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
vector<typename G::vertex_type> neighbors(G&, V);

template<typename G>
requires Graph<G>
int num_vertices(G&);

template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V>
bool reachable_from_top(G&, V);

template<typename G>
requires Graph<G> 
bool all_reachable_from_top(G&);

template<typename G>
requires Graph<G> 
bool compare_vertex_wrapper(typename G::vertex_header_type::vertex_wrapper_type, typename G::vertex_header_type::vertex_wrapper_type);

template<typename G>
requires Graph<G> 
vector<typename G::vertex_type> get_vertices_by_value(G&);

template<typename G>
requires Graph<G> 
bool compare_edge_wrapper(typename G::vertex_header_type::edge_wrapper_type, typename G::vertex_header_type::edge_wrapper_type);

template<typename G>
requires Graph<G> 
vector<typename G::edge_type> get_edges(G&);

template<typename G>
requires Graph<G> 
vector<typename G::edge_type> get_edges_by_value(G&);

/*
template<typename G, typename V>
requires Graph_and_Vertex_ptr<G, V> && Edge_cost<typename G::edge_type>
vector<typename G::vertex_type> get_shortest_path(G&, V, V);

template<typename G, typename V>
requires Heuristic_graph_and_Vertex_ptr<G, V> && Edge_cost<typename G::edge_type>
vector<typename G::vertex_type> ast_get_shortest_path(G&, V, V);

template<typename V, typename F, typename Insert, typename Remove, typename Top>
struct path_data<vector<typename V::element_type>, typename V::cost_type> find_path_generic(V, V, F, Insert, Remove, Top);

template<typename V>
 find_path_dfs(V, V);

template<typename V>
vector<typename V::element_type> find_path_bfs(V, V);

template<typename V>
vector<typename V::element_type> find_path_ucs(V, V);

template<typename V>
vector<typename V::element_type> find_path_ast(V, V);
*/

#endif
