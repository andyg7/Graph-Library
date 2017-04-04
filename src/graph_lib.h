#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

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
requires Graph<G> && Vertex_ptr<V>
bool vertex_exists(G g, V x)
{
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == *x) {
			return true;
		}
	}
	return false;
}

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
requires Graph<G> && Vertex_ptr<V>
bool add(G g, V x)
{
	typedef typename G::element_type::vertex_header_type vertex_header_type;
	if (vertex_exists(g, x)) {
		return false;
	}
	vertex_header_type new_header {*x}; 
	int container_size = g->underlying_data.size();
	auto it = g->underlying_data.begin();
	advance(it, container_size);
	g->underlying_data.insert(it, new_header);
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

template <typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool adjacent(G g, V x, V y)
{
	auto it_x = g->underlying_data.begin();
	auto it_x_end = g->underlying_data.end();
	for (; it_x != it_x_end; it_x++) {
		auto t_v = (*it_x);
		if (t_v.vertex_wrapper_data->vertex_data == *x) {
			break;
		}
	}
	if (it_x == it_x_end) {
		throw invalid_argument{"Unknown vertex"};
	}
	for (const auto& n : it_x->neighbors) {
		if (n->vertex_data == *y) {
			return true;
		}
	}
	return false;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
void remove(G g, V x)
{
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == *x) {
			g->underlying_data.erase(it);
			break;
		} 	
	}
	if (it == it_end) {
		throw invalid_argument{"Unknown vertex"};
	}
	for (it = g->underlying_data.begin(); it != g->underlying_data.end(); it++) {
		auto inner_it = (*it).neighbors.begin();
		auto inner_it_end = (*it).neighbors.end();
		while (inner_it != inner_it_end) {	
			auto inner_curr_it = inner_it++;
			if ((*inner_curr_it)->vertex_data == *x) {
				(*it).neighbors.erase(inner_curr_it);	
			} 			
		}
	}
	for (it = g->underlying_data.begin(); it != g->underlying_data.end(); it++) {
		auto inner_it = (*it).edges.begin();
		auto inner_it_end = (*it).edges.end();
		while (inner_it != inner_it_end) {	
			auto inner_curr_it = inner_it++;
			if ((*inner_curr_it)->edge.v1 == *x || (*inner_curr_it)->edge.v2 == *x) {
				(*it).edges.erase(inner_curr_it);	
			} 			
		}
	}
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V> 
Value value(G g, V x)
{
	Value v;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == *x) {
			return (*it).vertex_wrapper_data->value;
		}
	}
	throw invalid_argument{"Unknown vertex"};
}

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E>
Value value(G g, E e)
{
	Value v;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		auto it_inner = it->edges.begin();
		auto it_inner_end = it->edges.end();
		for (; it_inner != it_inner_end; it_inner++) {
			if (((*it_inner)->edge.v1 == e->v1)) {
				if (((*it_inner)->edge.v2 == e->v2)) {
					return (*it_inner)->value;
				}

			}
		}
	}
	throw invalid_argument{"Unknown edge"};
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
void set_value(G g, V x, Value v)
{
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == *x) {
			(*it).vertex_wrapper_data->value = v;
		} else {
			for (auto& n : it->neighbors) {
				if (n->vertex_data == *x) {
					n->value = v;
				}
			}
		}
	}
}

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E> && Same_type<typename G::element_type::edge_type, typename E::element_type>
void set_value(G g, E e, Value v)
{
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == e->v1) {
			for (auto& n : it->edges) {
				if (n->edge.v2 == e->v2) {
					Value new_v(v.first, v.second);
					n->value = new_v;
				}
			}
		}
	}
}

template<typename G, typename V>
bool add_edge_blindly(G g, V x, V y)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_type vertex_type;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == *x) {
			shared_ptr<vertex_wrapper<vertex_type>> v_w = make_shared<vertex_wrapper<vertex_type>>(*y);
			Value t_v = value(g, y);
			v_w->value = t_v;
			(*it).neighbors.insert((*it).neighbors.begin(), v_w);
			shared_ptr<edge_wrapper<vertex_type, edge_type>> new_edge_wrapper = make_shared<edge_wrapper<vertex_type, edge_type>>(); 
			edge_type new_edge;
			new_edge.v1 = *x; 
			new_edge.v2 = *y; 
			new_edge_wrapper->edge = new_edge; 
			(*it).edges.insert((*it).edges.begin(), (new_edge_wrapper));
		}
	}
	return true;
}

template<typename G, typename E>
bool add_edge_blindly_w_edge(G g, E e)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_type vertex_type;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	for (; it != it_end; it++) {
		if ((*it).vertex_wrapper_data->vertex_data == e->v1) {
			shared_ptr<vertex_wrapper<vertex_type>> v_w = std::make_shared<vertex_wrapper<vertex_type>>(e->v2);
			shared_ptr<vertex_type> tmp_v = make_shared<vertex_type>(e->v2);
			Value t_v = value(g, tmp_v);
			v_w->value = t_v;
			(*it).neighbors.insert((*it).neighbors.begin(), v_w);
			shared_ptr<edge_wrapper<vertex_type, edge_type>> new_edge_wrapper = make_shared<edge_wrapper<vertex_type, edge_type>>(); 
			new_edge_wrapper->edge = *e;
			(*it).edges.insert((*it).edges.begin(), (new_edge_wrapper));
		}
	}
	return true;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool add_edge(G g, V x, V y)
{
	bool added_edge = add_edge_blindly(g, x, y);
	return added_edge;
}

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E>
bool add_edge(G g, E e)
{
	bool added_edge = add_edge_blindly_w_edge(g, e);
	return added_edge;
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

template<typename G, typename V>
requires DAG_Graph<G> && Vertex_ptr<V>
bool add_edge(G g, V x, V y)
{
	bool path_ex = path_exists(g, y, x);
	if (path_ex == true) {
		return false;
	}
	bool added_edge = add_edge_blindly(g, x, y);
	return added_edge;
}

template<typename G, typename E>
requires DAG_Graph<G> && Edge_ptr<E>
bool add_edge(G g, E e)
{

	typedef typename G::element_type::vertex_type vertex_type;
	shared_ptr<vertex_type> tmp_v1 = make_shared<vertex_type>(e->v1);
	shared_ptr<vertex_type> tmp_v2 = make_shared<vertex_type>(e->v2);
	bool path_ex = path_exists(g, tmp_v2, tmp_v1);
	if (path_ex == true) {
		return false;
	} 
	bool added_edge = add_edge_blindly_w_edge(g, e);
	return added_edge;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool has_parent(G g, V x)
{
	auto nodes = g->underlying_data;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto neighbors = it->neighbors;
		for (auto &n : neighbors) {
			if (n->vertex_data == *x) {
				return true;
			}
		}
	}
	return false;
}

template<typename G, typename V>
requires DT_Graph<G> && Vertex_ptr<V>
bool add_edge(G g, V x, V y)
{
	bool path_ex = path_exists(g, y, x);
	if (path_ex == true) {
		return false;
	}
	bool has_par = has_parent(g, y);
	if (has_par == true) {
		return false;
	}
	bool added_edge = add_edge_blindly(g, x, y);
	return added_edge;
}


template<typename G, typename E>
requires DT_Graph<G> && Edge_ptr<E>
bool add_edge(G g, E e)
{
	typedef typename G::element_type::vertex_type vertex_type;
	shared_ptr<vertex_type> tmp_v1 = make_shared<vertex_type>(e->v1);
	shared_ptr<vertex_type> tmp_v2 = make_shared<vertex_type>(e->v2);
	bool path_ex = path_exists(g, tmp_v2, tmp_v1);
	if (path_ex == true) {
		return false;
	}
	bool has_par = has_parent(g, tmp_v2);
	if (has_par == true) {
		return false;
	}
	bool added_edge = add_edge_blindly_w_edge(g, e);
	return added_edge;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool has_child(G g, V x)
{
	auto nodes = g->underlying_data;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto neighbors = it->neighbors;
		if (neighbors.size() > 0) {
			return true;
		}
	}
	return false;
}

template<typename G>
requires Graph<G>
shared_ptr<typename G::element_type::vertex_type> top(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto curr_v_h = (*it);
		auto curr_v = curr_v_h.vertex_wrapper_data->vertex_data;
		shared_ptr<vertex_type> tmp_p = make_shared<vertex_type>(curr_v); 
		if (has_child(g, tmp_p) == true) {
			return tmp_p;
		}
	}
	it = g->underlying_data.begin();
	shared_ptr<vertex_type> tmp_p = make_shared<vertex_type>(it->vertex_wrapper_data->vertex_data);
	return tmp_p;
}

template<typename G>
requires Graph<G>
vector<typename G::element_type::vertex_type> get_vertices(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	vector<typename G::element_type::vertex_type> vertices;

	for (; it != it_end; it++) {
		auto curr_v_h = (*it);
		auto curr_v = curr_v_h.vertex_wrapper_data->vertex_data;
		vertices.push_back(curr_v);
	}
	return vertices;
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

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
vector<typename G::element_type::vertex_type> neighbors(G g, V x)
{
	typedef typename G::element_type::vertex_type vertex_type;
	vector<vertex_type> neighbors(0);

	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	
	for (; it != it_end; it++) {
		auto curr_v_h = (*it);
		auto curr_v = curr_v_h.vertex_wrapper_data->vertex_data;
		if (curr_v == *(x)) {
			auto it_inner = (it)->neighbors.begin();
			auto it_end_inner = (it)->neighbors.end();
			for (; it_inner != it_end_inner; it_inner++) {
				neighbors.push_back((*it_inner)->vertex_data);
			}
		}
	}
	return neighbors;
}

template<typename G>
requires Graph<G>
int num_vertices(G g)
{
	return g->underlying_data.size();
}

template<typename G>
requires Matrix_Graph<G>
int num_vertices(G g)
{
	return (g->id_to_wrapper).size();
}

template<typename G>
requires Graph<G>
int num_edges(G g)
{
	int num_edges = 0;
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();
	
	for (; it != it_end; it++) {
		auto curr_edges = it->neighbors;
		num_edges += curr_edges.size();
	}
	return num_edges;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool reachable_from_top(G g, V x)
{
	auto curr_top = top(g);
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		if (path_exists(g, curr_top, x)) {
			return true;
		}
	}
	return false;
}

template<typename G>
requires Graph<G>
bool all_reachable_from_top(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	auto curr_top = top(g);
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		shared_ptr<vertex_type> tmp_p = make_shared<vertex_type>(it->vertex_wrapper_data->vertex_data);
		if (*(curr_top) != *(tmp_p)) { 
			if (reachable_from_top(g, tmp_p) == false) {
				return false;
			}
		}
	}
	return true;
}

template<typename G>
requires Graph<G> 
bool compare_vertex_wrapper(typename G::element_type::vertex_header_type::vertex_wrapper_type w1, typename G::element_type::vertex_header_type::vertex_wrapper_type w2)
{
	return w1->value.second > w2->value.second;
}

template<typename G>
requires Graph<G> 
vector<typename G::element_type::vertex_type> get_vertices_by_value(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	typedef typename G::element_type::vertex_header_type::vertex_wrapper_type vertex_wrapper_type;
	vector<vertex_type> vec;
	vector<vertex_wrapper_type> vec_w;

	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto tmp_w = it->vertex_wrapper_data;
		vec_w.push_back(tmp_w);
	}
	sort(vec_w.begin(), vec_w.end(), compare_vertex_wrapper<G>);

	auto it_w = vec_w.begin();
	auto it_end_w = vec_w.end();
	for (; it_w != it_end_w; it_w++) {
		auto tmp_v = (*it_w)->vertex_data;
		vec.push_back(tmp_v);
	}
	return vec;
}

template<typename G>
requires Graph<G> 
bool compare_edge_wrapper(typename G::element_type::vertex_header_type::edge_wrapper_type e1, typename G::element_type::vertex_header_type::edge_wrapper_type e2)
{
	return e1->value.second > e2->value.second;
}

template<typename G>
requires Graph<G> 
vector<typename G::element_type::edge_type> get_edges(G g)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_header_type::edge_wrapper_type edge_wrapper_type;
	vector<edge_type> edges;
	vector<edge_wrapper_type> edge_w;

	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto it_inner = it->edges.begin();
		auto it_end_inner = it->edges.end();
		for (; it_inner != it_end_inner; it_inner++) {
			auto tmp_w = *it_inner;
			edge_w.push_back(tmp_w);
		}
	}

	auto it_w = edge_w.begin();
	auto it_end_w = edge_w.end();
	for (; it_w != it_end_w; it_w++) {
		edge_type tmp_e = (*it_w)->edge;
		edges.push_back(tmp_e);
	}
	return edges;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
vector<typename G::element_type::edge_type> get_edges_for_vertex(G g, V v)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_header_type::edge_wrapper_type edge_wrapper_type;

	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		if ((it->vertex_wrapper_data)->vertex_data == *v) {
			break;
		}
	}

	vector<edge_type> edges;
	auto it_w = it->edges.begin();
	auto it_w_end = it->edges.end();
	for (; it_w != it_w_end; it_w++) {
		edge_type tmp_e = (*it_w)->edge;
		edges.push_back(tmp_e);
	}
	return edges;
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

template<typename G>
requires Graph<G> 
vector<typename G::element_type::edge_type> get_edges_by_value(G g)
{
	typedef typename G::element_type::edge_type edge_type;
	typedef typename G::element_type::vertex_header_type::edge_wrapper_type edge_wrapper_type;
	vector<edge_wrapper_type> edge_w;

	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto it_inner = it->edges.begin();
		auto it_end_inner = it->edges.end();
		for (; it_inner != it_end_inner; it_inner++) {
			auto tmp_w = (*it_inner);
			edge_w.push_back(tmp_w);
		}
	}
	sort(edge_w.begin(), edge_w.end(), compare_edge_wrapper<G>);

	auto it_w = edge_w.begin();
	auto it_end_w = edge_w.end();
	vector<edge_type> edges;
	for (; it_w != it_end_w; it_w++) {
		edge_type tmp_e = (*it_w)->edge;
		edges.push_back(tmp_e);
	}
	return edges;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<typename G::element_type::vertex_wrapper_type> get_vertex_wrapper(G g, V v)
{
	auto it = g->underlying_data.begin();
	auto it_end = g->underlying_data.end();

	for (; it != it_end; it++) {
		auto curr_v_h = *it;
		auto curr_v = curr_v_h.vertex_wrapper_data->vertex_data;
		if (curr_v == *v) {
			return curr_v_h.vertex_wrapper_data;
		}
	}
	throw invalid_argument{"Unknown vertex"};
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
