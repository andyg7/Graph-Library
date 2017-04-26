#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <list>
#include "graph_lib.h"

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

