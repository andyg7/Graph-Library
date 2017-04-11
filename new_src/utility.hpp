#ifndef UTILITY_H
#define UTILITY_H

#include "Graph.hpp"
#include <algorithm>
using namespace std;


template <typename I, typename W, typename D>
using EdgeSP = shared_ptr<Edge<I, W, D>>;

template <typename I, typename W, typename D>
inline EdgeSP<I, W, D> average_combine(EdgeSP<I, W, D> forward, EdgeSP<I, W, D> backward){
	return create_edge<I, W, D>(forward->get_src(), (forward->get_weight() + backward->get_weight()) / 2, forward->get_dst());
}

/* Algorithm makes an undirected graph from a directed graph */
/* combine - function that dictates how to combine opposite directed edges between two nodes */
template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
shared_ptr<GraphType<I, W, D>> make_undirected_from(shared_ptr<GraphType<I, W, D>> initial_graph,
	std::function<EdgeSP<I, W, D>(EdgeSP<I, W, D>, EdgeSP<I, W, D>)> combine){

	auto undirected_graph = create_graph<I, W, D, GraphType>();
	auto edges = initial_graph->get_edges();
	print_edges(edges);
	std::sort(edges.begin(), edges.end(), compare_edges<I, W, D>);

	print_edges(edges);

	return initial_graph;

}


#endif