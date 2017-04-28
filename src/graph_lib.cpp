#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <list>
#include "graph_lib.h"

/*

\mainpage The mainpage documentation

It's a graph library, built in C++, that makes it easy to create and use graphs. Currently the library supports the following graphs: DG (directed graph), DAG (directed acyclic graph), DT (directed tree), Matrix(undirected). The idea is that users define their own vertex and edge data types, and then the library handles everything else under the hood.

Conceptually, a graph is made up of a bunch of vertices and edges. At a minimum there must be some way to distinguish between vertices, distinguish between edges, and define edges as made up of two vertices. Nontheless, users often want to embed extra information in these ADTs. For example, a user may want a graph representing cities and the highways between them. The user may have a City class; cities must of course have some unique id (e.g. city name), but they may also have extra information such as population, GDP, etc. The same goes for edges; maybe a Road class is used, and the class also has miles, age of road etc. This library makes it easy for users to provide their own ADTs, and immediately start creating graphs, and run algoritms on them.



*/


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

