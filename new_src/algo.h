#ifndef ALGO_H
#define ALGO_H

#include "Graph.hpp"
#include <list>
# define INF 0x3f3f3f3f

template <typename I, typename W, typename D>
using EdgeSP = shared_ptr<Edge<I, W, D>>;
template <typename I, typename D>
using NodeSP = shared_ptr<Node<I, D>>;
template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
using GraphSP = shared_ptr<GraphType<I, W, D>>;

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
GraphSP<I, W, D, GraphType> dfs(GraphSP<I, W, D, GraphType> graph, 
	NodeSP<I, D> root){

	/* Initilization */
	list<NodeSP<I, D>> temp;
	map<I, bool> discovered_map;
	map<I, EdgeSP<I, W, D>> predecessor;
	auto tree = create_graph<I, W, D, GraphType>();


	/* Push the root */
	temp.push_front(root);


	while(!temp.empty()){
		auto x = temp.front();
		temp.pop_front();

		if (discovered_map.find(x->get_id()) == discovered_map.end()){
			
			/* Mark x as discovered */
			discovered_map[x->get_id()] = true;

			/* Add the node to the tree we are building */
			add_node(tree, x);
				
			/* Add the edge representig how we got there */
			auto pred_p = predecessor.find(x->get_id());

			/* If prefeccessor exists, add the edge to the graph */
			if(pred_p != predecessor.end()){
				add_edge(tree, (*pred_p).second );
			}

			/* Add all the neighbours to the que */
			for(auto y : graph->neighbours(x)){
				temp.push_front(y);
				predecessor[y->get_id()] = get_edge(graph, x, y);
			}
		}
	}
	return tree;
}

void dijkstra(GraphSP<I, W, D, GraphType> graph, 
	NodeSP<I, D> src){
	/* Initilization */
	/* Create a set to store vertices that are being prerocessed - vertex is 2nd and distance is 1st*/
	set< pair<int, I> > setds;
	map<I, int> distance; // to maintain the distance of each vertex from src
	// initialise map - key is ID, value is distance = INF
	// gets all nodes in graph
	vector<NodeSP<I,D> nodes = get_nodes();
	// maps all node values to infinity
	for(vector<NodeSP<I,D>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    	map[it] = INF;
	}
	// get a list of all 
	/*Insert source itself in Set and initialize its distance as 0.*/
	setds.insert(make_pair(0, src));
	distance[src] = 0;
	while (!setds.empty()){
		/* The first vertex in Set is the minimum distance vertex, extract it from set. */
        pair<int, I> tmp = *(setds.begin());
        setds.erase(setds.begin());
        auto u = temp.second();
        for(auto y : graph->neighbours(u)){
        	// gets weight of that node and its neighbours

        	// HOW DO I GET THE WEIGHTS OF 2 EDGES
        	int weight = get_weight(u,y);
        	if (distance[y] > distance[u] + weight)
            {
                /*  If distance of v is not INF then it must be in
                    our set, so removing it and inserting again
                    with updated less distance.  
                */
                if (distance[y] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));
 					
                // Updating distance of v
                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
            }
        }
	}
}

#endif