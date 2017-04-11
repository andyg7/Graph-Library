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

	/* Add all nodes to the new graph since they are not influenced by directedness */
	add_nodes(initial_graph->get_nodes(), undirected_graph);

	for(auto edge_sp : edges){

		/* If this edge already exists, the connection has been built so we skip */
		if( undirected_graph->adjacent(edge_sp->get_src(), edge_sp->get_dst())){
			continue;
		}

		/* If the back edge exists, we want to combine the two into one, and add that one in both directions */
		if(initial_graph->adjacent(edge_sp->get_dst(), edge_sp->get_src())){
			auto back = initial_graph->get_edge(edge_sp->get_dst(), edge_sp->get_src());
			auto combined_edge = combine(edge_sp, back);
			undirected_graph->add_edge(combined_edge);
			undirected_graph->add_edge(combined_edge->get_dst(), combined_edge->get_weight(), combined_edge->get_src());
			continue;
		}

		/* Otherwise, if no backward edge exist, add the one we have in both directions */
		undirected_graph->add_edge(edge_sp);
		undirected_graph->add_edge(edge_sp->get_dst(), edge_sp->get_weight(), edge_sp->get_src());

	}

	return undirected_graph;
}


#endif