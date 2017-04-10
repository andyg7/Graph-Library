#ifndef ALGO_H
#define ALGO_H

#include "Graph.hpp"
#include <list>

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
shared_ptr<GraphType<I, W, D>> dfs(shared_ptr<GraphType<I, W, D>> graph, 
	shared_ptr<Node<I, D>> root){
	
	using node_p = shared_ptr<Node<I, D>>;
	using grap_p = shared_ptr<GraphType<I, W, D>>;

	/* Initilization */
	list<node_p> temp;
	map<I, bool> discovered_map;
	map<I, shared_ptr<Edge<I, W, D>>> predecessor;
	grap_p tree = create_graph<I, W, D, GraphType>();


	/* Push the root */
	temp.push_front(root);


	while(!temp.empty()){
		auto x = temp.front();
		temp.pop_front();

		if (discovered_map.find(x->get_id()) == discovered_map.end()){
			
			/* Mark x as discovered */
			discovered_map[x->get_id()] = true;

			/* Add the node to the tree we are building */
			tree->add_node(x);
				
			/* Add the edge representig how we got there */
			auto pred_p = predecessor.find(x->get_id());

			if(pred_p != predecessor.end()){
				tree->add_edge( (*pred_p).second );
			}

			/* Add all the neighbours to the que */
			for(auto y : graph->neighbours(x)){
				temp.push_front(y);
				predecessor[y->get_id()] = graph->get_edge(x, y);
			}

		}

	}

	return tree;
}


#endif