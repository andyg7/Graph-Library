#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

#include "adjacency_list_graph_lib.h"
#include "matrix_graph_lib.h"

/*

\mainpage The mainpage documentation

It's a graph library, built in C++, that makes it easy to create and use graphs. Currently the library supports the following graphs: DG (directed graph), DAG (directed acyclic graph), DT (directed tree), Matrix(undirected). The idea is that users define their own vertex and edge data types, and then the library handles everything else under the hood.

Conceptually, a graph is made up of a bunch of vertices and edges. At a minimum there must be some way to distinguish between vertices, distinguish between edges, and define edges as made up of two vertices. Nontheless, users often want to embed extra information in these ADTs. For example, a user may want a graph representing cities and the highways between them. The user may have a City class; cities must of course have some unique id (e.g. city name), but they may also have extra information such as population, GDP, etc. The same goes for edges; maybe a Road class is used, and the class also has miles, age of road etc. This library makes it easy for users to provide their own ADTs, and immediately start creating graphs, and run algoritms on them.



*/


/// \file
/// \brief The main file that contains that the graph definitions - adjacency matrix, list, etc


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
