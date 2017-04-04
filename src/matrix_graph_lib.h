#ifndef MATRIX_GRAPH_LIB_H
#define MATRIX_GRAPH_LIB_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <list>
#include "graph_concepts.h"
#include "graph_structs.h"
#include "graph_create.h"
#include "path_algorithms.h"
#include "node_expander_path_algorithms.h"

using namespace std;
using namespace graph_std_lib;

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
bool vertex_exists(G g, V x)
{
	auto it = (g->id_to_wrapper).find(x->vertex_id);
	if (it == (g->id_to_wrapper).end()) {
		return false;
	} 
	return true;
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
bool add(G g, V x)
{
	typedef typename G::element_type::vertex_wrapper_type vertex_wrapper_type;
	if (vertex_exists(g, x)) {
		return false;
	}
	shared_ptr<vertex_wrapper_type> new_wrapper = make_shared<vertex_wrapper_type>(*x);
	int tmp_id = x->vertex_id;
	(g->id_to_wrapper).insert(make_pair(tmp_id, new_wrapper));
	(g->wrapper_to_id).insert(make_pair(new_wrapper, tmp_id));
	return true;
}

template<typename G, typename E>
requires Matrix_Graph<G> && Edge_ptr<E>
bool add_edge(G g, E e)
{
	int cost = e->cost;
	int v1_index = (e->v1).vertex_id;
	int v2_index = (e->v2).vertex_id;
	auto v_l = (g->underlying_data)[v1_index];
	v_l[v2_index] = cost;
	(g->underlying_data)[v1_index][v2_index] = cost;
	return true;
}

template<typename G>
requires Matrix_Graph<G>
vector<typename G::element_type::vertex_type> get_vertices(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	vector<typename G::element_type::vertex_type> vertices;
	auto it = (g->id_to_wrapper).begin();
	auto it_end = (g->id_to_wrapper).end();

	for (; it != it_end; it++) {
		int id = it->first;
		vertex_type v_d = (it->second)->vertex_data;
		vertices.push_back(v_d);
	}
	return vertices;
}

template<typename G>
requires Matrix_Graph<G>
int num_vertices(G g)
{
	return (g->id_to_wrapper).size();
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
vector<typename G::element_type::edge_type> get_edges_for_vertex(G g, V v)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_header_type::edge_wrapper_type edge_wrapper_type;

	vector<edge_type> edges;
	int id = v->vertex_id;
	auto vector_edges = (g->underlying_data)[id];
	auto it_w = vector_edges.begin();
	auto it_w_end = vector_edges.end();
	int counter = 0;
	for (; it_w != it_w_end; it_w++) {
		int curr_cost = *it_w;
		if (curr_cost != 0) {
			edge_type new_edge;
			new_edge.v1 = *v;
			auto v_w = (g->id_to_wrapper)[counter];
			new_edge.v2 = v_w->vertex_data;
			new_edge.cost = curr_cost;
			edges.push_back(new_edge);
		}
		counter++;
	}
	return edges;
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
shared_ptr<typename G::element_type::vertex_wrapper_type> get_vertex_wrapper(G g, V v)
{
	auto it = (g->id_to_wrapper).find(v->vertex_id);
	if (it == (g->id_to_wrapper).end()) {
		throw invalid_argument{"Unknown vertex"};
	} 
	return it->second;
}

#endif
