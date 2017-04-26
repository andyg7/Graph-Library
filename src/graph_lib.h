#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

#include "adjacency_list_graph_lib.h"
#include "matrix_graph_lib.h"

/*
Implementation independent functions go here
*/

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
bool set_value(G g, V x, Value v)
{
	try {
		auto v_w = get_vertex_wrapper(g, x);
		v_w->value = v;
		return true;
	} catch (invalid_argument e) {
		return false;
	}
}

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E> && Same_type<typename G::element_type::edge_type, typename E::element_type>
bool set_value(G g, E e, Value v)
{
	try {
		auto e_w = get_edge_wrapper(g, e);
		e_w->value = v;
		return true;
	} catch (invalid_argument e) {
		return false;
	}
}

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E>
Value value(G g, E e)
{
	auto e_w = get_edge_wrapper(g, e);
	return e_w->value;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V> 
Value value(G g, V x)
{
	auto v_w = get_vertex_wrapper(g, x);
	return v_w->value;
}

#endif
