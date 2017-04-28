/// \file
/// \brief Adjacency Matrix implementation for a Graph

#ifndef MATRIX_GRAPH_LIB_H
#define MATRIX_GRAPH_LIB_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <list>
#include "graph_concepts.h"
#include "graph_create.h"
#include "path_algorithms.h"
#include "node_expander_path_algorithms.h"

using namespace std;

template <typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
bool adjacent(G g, V x, V y)
{
	int x_id = (g->vertex_to_id).find(*x)->second;
	int y_id = (g->vertex_to_id).find(*y)->second;
	if (g->underlying_data[x_id][y_id] == 0) {
		return false;
	} else {
		return true;
	}
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
bool vertex_exists(G g, V x)
{
	auto it = (g->vertex_to_id).find(*x);
	if (it == (g->vertex_to_id).end()) {
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
	int new_internal_id = get_unique_id(g, [] (G g) { return get_vertex_wrapper_ids(g); });
	if (new_internal_id >= g->underlying_data.size()) {
		throw logic_error("No room for new node");
	}
	shared_ptr<vertex_wrapper_type> new_wrapper = make_shared<vertex_wrapper_type>(*x);
	new_wrapper->internal_id = new_internal_id;
	(g->id_to_wrapper).insert(make_pair(new_internal_id, new_wrapper));
	(g->wrapper_to_id).insert(make_pair(new_wrapper, new_internal_id));
	(g->id_to_vertex).insert(make_pair(new_internal_id, *x));
	(g->vertex_to_id).insert(make_pair(*x, new_internal_id));
	return true;
}

template<typename G, typename E>
requires Matrix_Graph<G> && Edge_ptr<E>
bool add_edge(G g, E e)
{
	typedef typename G::element_type::edge_wrapper_type edge_wrapper_type;

	int cost = e->cost;
	int v1_index = (g->vertex_to_id).find(e->v1)->second;
	int v2_index = (g->vertex_to_id).find(e->v2)->second;
	(g->underlying_data)[v1_index][v2_index] = cost;
	shared_ptr<edge_wrapper_type> new_e_w = make_shared<edge_wrapper_type>();
	new_e_w->edge = *e;
	(g->id_to_edges[v1_index]).push_back(new_e_w);
	return true;
}

template<typename G, typename E>
requires Matrix_Graph<G> && Edge_ptr<E>
bool remove_edge(G g, E e)
{
	int cost = e->cost;
	int v1_index = (g->vertex_to_id).find(e->v1)->second;
	int v2_index = (g->vertex_to_id).find(e->v2)->second;
	(g->underlying_data)[v1_index][v2_index] = 0;
	(g->underlying_data)[v2_index][v1_index] = 0;
	auto curr_edges = g->id_to_edges[v1_index];
	auto it = curr_edges.begin();
	auto it_end = curr_edges.end();
	for (; it != it_end; it++) {
		if (it->edge == e) {
			break;
		}
	}
	if (it == it_end) {
		throw invalid_argument{"Unknown vertex"};
	}
	curr_edges.erase(it);
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
vector<int> get_vertices_ids(G g)
{
	vector<int> vertices;
	auto it = (g->id_to_wrapper).begin();
	auto it_end = (g->id_to_wrapper).end();

	for (; it != it_end; it++) {
		int id = it->first;
		auto v_d = (it->second)->vertex_data;
		vertices.push_back(v_d.vertex_id);
	}
	return vertices;
}

template<typename G>
requires Matrix_Graph<G>
vector<shared_ptr<typename G::element_type::vertex_wrapper_type>> get_vertices_wrappers(G g)
{
	typedef typename G::element_type::vertex_wrapper_type vertex_wrapper_type;
	vector<vertex_wrapper_type> vertices(0);
	auto it = (g->id_to_wrapper).begin();
	auto it_end = (g->id_to_wrapper).end();

	for (; it != it_end; it++) {
		int id = it->first;
		auto v_w = (it->second);
		vertices.push_back(v_w);
	}
	return vertices;
}

template<typename G>
requires Matrix_Graph<G>
vector<int> get_vertex_wrapper_ids(G g)
{
	vector<int> vertices(0);
	auto it = (g->id_to_wrapper).begin();
	auto it_end = (g->id_to_wrapper).end();

	for (; it != it_end; it++) {
		int id = it->first;
		auto v_w = (it->second);
		vertices.push_back(v_w->internal_id);
	}
	return vertices;
}

template<typename G>
requires Matrix_Graph<G>
vector<typename G::element_type::vertex_type> get_vertices_by_value(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::vertex_wrapper_type vertex_wrapper_type;
	auto it = (g->id_to_wrapper).begin();
	auto it_end = (g->id_to_wrapper).end();

	vector<shared_ptr<vertex_wrapper_type>> vertices_w;
	for (; it != it_end; it++) {
		vertices_w.push_back(it->second);
	}
	sort(vertices_w.begin(), vertices_w.end(), [](const shared_ptr<vertex_wrapper_type>& v1, const shared_ptr<vertex_wrapper_type>& v2) -> bool	 
			{
			return v1->value > v2->value;
			});
	vector<vertex_type> vertices;
	for (auto v_w : vertices_w) {
		vertices.push_back(v_w->vertex_data);
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
	int id = (g->vertex_to_id).find(*v)->second;
	auto vector_edges = (g->underlying_data)[id];
	auto curr_edges = g->id_to_edges[id];
	for (auto e : curr_edges) {
		edges.push_back(e->edge);
	}
	return edges;
}

template<typename G>
requires Matrix_Graph<G> 
vector<typename G::element_type::edge_type> get_edges(G g)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_header_type::edge_wrapper_type edge_wrapper_type;

	vector<edge_type> edges;
	vector<int> keys;
	auto it = (g->id_to_edges).begin();
	auto it_end = (g->id_to_edges).end();
	for (; it != it_end; it++) {
		keys.push_back(it->first);
	}
	for (auto k : keys) {
		auto curr_edges = (g->id_to_edges)[k];
		for (auto e : curr_edges) {
			edges.push_back(e->edge);
		}
	}
	return edges;
}

template<typename G>
requires Matrix_Graph<G> 
vector<typename G::element_type::edge_type> get_edges_by_value(G g)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::edge_wrapper_type edge_wrapper_type;

	vector<shared_ptr<edge_wrapper_type>> edges_w;
	vector<int> keys;
	auto it = (g->id_to_edges).begin();
	auto it_end = (g->id_to_edges).end();
	for (; it != it_end; it++) {
		keys.push_back(it->first);
	}
	for (auto k : keys) {
		auto curr_edges = (g->id_to_edges)[k];
		for (auto e : curr_edges) {
			edges_w.push_back(e);
		}
	}
	sort(edges_w.begin(), edges_w.end(), [](const shared_ptr<edge_wrapper_type>& e1, const shared_ptr<edge_wrapper_type>& e2) -> bool	 
			{ 
			return e1->value > e2->value;
			});
	vector<edge_type> edges;
	for (auto e_w : edges_w) {
		edges.push_back(e_w->edge);
	}
	return edges;
}

template<typename G>
requires Matrix_Graph<G> 
int num_edges(G g)
{
	auto it = (g->id_to_edges).begin();
	auto it_end = (g->id_to_edges).end();
	int counter = 0;
	for (; it != it_end; it++) {
		counter++;
	}
	return counter;
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
shared_ptr<typename G::element_type::vertex_wrapper_type> get_vertex_wrapper(G g, V v)
{
	int curr_id = (g->vertex_to_id).find(*v)->second;
	auto it = (g->id_to_wrapper).find(curr_id);
	if (it == (g->id_to_wrapper).end()) {
		throw invalid_argument{"Unknown vertex"};
	} 
	return it->second;
}

template<typename G, typename E>
requires Matrix_Graph<G> && Edge_ptr<E>
shared_ptr<typename G::element_type::edge_wrapper_type> get_edge_wrapper(G g, E e)
{
	int curr_id = (g->vertex_to_id).find(e->v1)->second;
	auto it = (g->id_to_edges).find(curr_id);
	auto v_e = it->second;
	for (auto c_e : v_e) {
		if (c_e->edge == *e) {
			return c_e;
		}
	}
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
vector<typename G::element_type::vertex_type> neighbors(G g, V x)
{
	typedef typename G::element_type::vertex_type vertex_type;
	vector<vertex_type> neighbors(0);

	int curr_id = (g->vertex_to_id).find(*x)->second;
	auto v_neighbors = g->underlying_data[curr_id];
	for (auto n : v_neighbors) {
		if (n != 0) {
			auto neigh = g->id_to_wrapper[n];
			neighbors.push_back(neigh->vertex_data);
		}
	}
	return neighbors;
}

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
void remove(G g, V x)
{
	int curr_id = (g->vertex_to_id).find(*x)->second;
	auto v_w = get_vertex_wrapper(g, x);

	auto v_neigbors = g->underlying_data[curr_id];
	for (int i = 0; i < v_neigbors.size(); i++) {
		v_neigbors[i] = 0;
	}

	for (int i = 0; i < g->underlying_data.size(); i++) {
		auto curr_col = g->underlying_data[i];
		curr_col[curr_id] = 0;
	}

	g->id_to_wrapper.erase(curr_id);
	g->id_to_edges.erase(curr_id);
	g->wrapper_to_id.erase(v_w);
	g->id_to_vertex.erase(curr_id);
	g->vertex_to_id.erase(*x);
}

#endif
