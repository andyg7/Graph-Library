#ifndef GRAPH_LIB_HEADER_H
#define GRAPH_LIB_HEADER_H

#include "graph_concepts.h"

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool add(G&, V);

template <typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool adjacent(G&, V, V);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
void remove(G&, V);

template<typename G, typename V>
bool add_edge_blindly(Graph&, V, V);

template<typename G, typename E>
bool add_edge_blindly_w_edge(G&, E);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool add_edge(G&, V, V);

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E>
bool add_edge(G&, E);

template<typename G, typename V>
requires DAG_Graph<G> && Vertex_ptr<V>
bool add_edge(G&, V, V);

template<typename G, typename E>
requires DAG_Graph<G> && Edge_ptr<E>
bool add_edge(G&, E);

template<typename G, typename V>
requires DT_Graph<G> && Vertex_ptr<V>
bool add_edge(G&, V, V);

template<typename G, typename E>
requires DT_Graph<G> && Edge_ptr<E>
bool add_edge(G&, E);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool vertex_exists(G&, V);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool path_exists(G&, V, V);

template<typename G>
requires Graph<G>
bool cycle_exists(G&);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool has_parent(G&, V);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool has_child(G&, V);

template<typename G>
requires Graph<G>
shared_ptr<typename G::vertex_type> top(G&);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
vector<typename G::vertex_type> neighbors(G&, V);

template<typename G>
requires Graph<G>
int num_vertices(G&);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
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

#endif
