#ifndef GRAPH_AM_H
#define GRAPH_AM_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <assert.h>
#include <stdexcept>
#include <utility>

#include "graph_concepts.h"
#include "Graph.hpp"
#include "SquareMatrix.h"


using namespace std;

template <typename IdType, typename WeightType, typename DataType>
class NodeAM;
template <typename IdType, typename WeightType, typename DataType>
//requires Comparable<IdType>
class GraphAM;


/************************* GraphAL Class ****************************/
template <typename IdType, typename WeightType, typename DataType>
//requires Comparable<IdType>
class GraphAM{
friend class NodeAM<IdType, WeightType, DataType>;
public:

	using id_type = IdType;
	using weight_type = WeightType;
	using data_type = DataType;

	static inline shared_ptr<GraphAM<IdType, WeightType, DataType>> create_graph(){
		shared_ptr<GraphAM<IdType, WeightType, DataType>> p = make_shared<GraphAM<IdType, WeightType, DataType>>();
		return p;
	}

	// ~GraphAM(){
	// 	delete adjacency_matrix;
	// }

	// /* Checks if the node is in the graph */
	// inline bool has_node(const shared_ptr<Node<IdType, DataType>> x){
	// 	return node_in_graph(x);
	// }


	// bool has_edge(const shared_ptr<Node<IdType, DataType>> src, const WeightType w, 
	// 	const shared_ptr<Node<IdType, DataType>> dst);

	// /* Returns all the outgoing edges from a given node */
	// vector<shared_ptr<Edge<IdType, WeightType, DataType>>> edges_of_node(const shared_ptr<Node<IdType, DataType>> x);

	// /* Returns a vector of all eges in the graph */
	// vector<shared_ptr<Edge<IdType, WeightType, DataType>>> get_edges();

	// /* Returns an edge between two nodes in a graph, if such exists. Throws exp otherwise */
	// shared_ptr<Edge<IdType, WeightType, DataType>> get_edge(shared_ptr<Node<IdType, DataType>> src,
	// 	shared_ptr<Node<IdType, DataType>> dst);

	// /* Returns the nodes of the graph */
	// vector<shared_ptr<Node<IdType, DataType>>> get_nodes();

	// /* Function return the neighbours of the node */
	// vector<shared_ptr<Node<IdType, DataType>>> neighbours(const shared_ptr<Node<IdType, DataType>> src);

	// /* Checks if exists a directed edge from src to dst */
	bool adjacent(const shared_ptr<Node<IdType, DataType>> src, const shared_ptr<Node<IdType, DataType>> dst){

		/* First we need to check if the nodes are in the graph */
		if(!nodes_in_graph(src, dst)){
			throw std::invalid_argument("src or dst of the edge not in the graph");
		}

		/* Get hold of the wrappers */
		auto src_p = get_wrapper_p(src);
		auto dst_p = get_wrapper_p(dst);

		return adjacent(src_p, dst_p);
	}

	/* Adds a node to the graph */
	bool add_node(const shared_ptr<Node<IdType, DataType>> x){

		/* Check if the vertex is already in the graph */
		if(node_in_graph(x)){
			throw std::invalid_argument("node already added");
		}

		/* Create the wrapper and add it to adjacency list */
		NodeAM<IdType, WeightType, DataType>* vertex_p = 
			new NodeAM<IdType, WeightType, DataType>(this, x);
		int internal_id = vertex_p->internal_id;

		/* Update the knowledge about highest active id */
		if(internal_id > highest_active_id){
			highest_active_id = internal_id;
			adjacency_matrix.inc_used();
		}

		/* Check if our adjacency matrix needs resizing */
		if(adjacency_matrix.full())
			adjacency_matrix.resize();

		/* Add the new mapping into the map */
		id_map[x->get_id()] = vertex_p;
		assert(id_map.find(x->get_id())->second == vertex_p); //ASSERT
		return true;

	}

	// /* Removes a node from a graph */
	bool remove_node(const shared_ptr<Node<IdType, DataType>> x){

		/* Check if the vertex is already in the graph */
		if(!node_in_graph(x)){
			throw std::invalid_argument("node not in the graph");
		}

		auto wrapper_p = get_wrapper_p(x);
		int internal_id = wrapper_p->internal_id;

		/* Erase the row an the column */
		adjacency_matrix.zero_row(internal_id);
		adjacency_matrix.zero_column(internal_id);

		/* Delete the wrapper */
		delete wrapper_p;

		/* Get the unique id back for id recycling */
		return_id(internal_id);

		/* Erase the vertex from the wrapper map */
		id_map.erase(x->get_id());

		return true;
	}

	bool add_edge(const shared_ptr<Node<IdType, DataType>> src, const WeightType w, 
		const shared_ptr<Node<IdType, DataType>> dst){

		/* First we need to check if the nodes are in the graph */
		if(!nodes_in_graph(src, dst)){
			throw std::invalid_argument("src or dst of the edge not in the graph");
		}

		/* Get hold of the wrappers */
		auto src_p = get_wrapper_p(src);
		auto dst_p = get_wrapper_p(dst);

		/* Get the entry of the adjacency matrix to access */
		int row = src_p->internal_id;
		int column = dst_p->internal_id;

		/* Check if the edge already exists, if it does, 
		throw an exception */
		if(adjacent(src_p, dst_p)){
			throw std::invalid_argument("edge already exists");
		}

		/* If does not exist, lets add it by adding the weight */
		adjacency_matrix.set_entry(row, column, w);

		return true;
	}

	/* Removes an edge from the graph */
	bool remove_edge(const shared_ptr<Node<IdType, DataType>> src,
		const shared_ptr<Node<IdType, DataType>> dst){

		/* First we need to check if the nodes are in the graph */
		if(!nodes_in_graph(src, dst)){
			throw std::invalid_argument("src or dst of the edge not in the graph");
		}

		/* Get hold of the wrappers */
		auto src_p = get_wrapper_p(src);
		auto dst_p = get_wrapper_p(dst);

		/* Get the entry of the adjacency matrix to access */
		int row = src_p->internal_id;
		int column = dst_p->internal_id;

		/* Check if the edge already exists, if it does, 
		throw an exception */
		if(!adjacent(src_p, dst_p)){
			throw std::invalid_argument("nodes not adjacent");
		}

		/* If does not exist, lets add it by adding the weight */
		adjacency_matrix.zero_entry(row, column);

	}

	void print_graph(){
		adjacency_matrix.print_matrix();
	}

	/* Need to add more constructors such as list initialization here*/
	GraphAM(){
		next_unique_id = 0;
		//adjacency_matrix = SquareMatrix<WeightType>();
	}

private:
	
	/* Vector of smart pointers to wrappers. This allows direct access
	to the neighbours of the node from its wrapper. The penalty – vertex
	removal */
	SquareMatrix<WeightType> adjacency_matrix;
	// Need this map to go from Node -> NodeAL
	map<IdType, NodeAM<IdType, WeightType, DataType>*> id_map;

	/* Same idea as for GraphAl here */
	long next_unique_id;
	vector<int> free_ids;

	int highest_active_id;

	/* Function hands out the new id when a vertex is added*/
	inline long get_new_id(){
		if(free_ids.empty()){
			return next_unique_id++;
		}else{
			int temp = free_ids.back();
			free_ids.pop_back();
			return temp;
		}
	}

	inline bool return_id(int internal_id){
		free_ids.push_back(internal_id);
	}

	inline bool node_in_graph(const shared_ptr<Node<IdType, DataType>> x){
		if(id_map.find(x->get_id()) != id_map.end()){
			return true;
		}
		return false;
	}

	inline bool nodes_in_graph(const shared_ptr<Node<IdType, DataType>> x,
		const shared_ptr<Node<IdType, DataType>> y){
		return (node_in_graph(x) && node_in_graph(y));
	}

	/* NOTE: Assumes x is in the graph */
	NodeAM<IdType, WeightType, DataType>* get_wrapper_p(const shared_ptr<Node<IdType, DataType>> x){
		return id_map.find(x->get_id())->second;
	}

	bool adjacent(const NodeAM<IdType, WeightType, DataType> * src_p, 
		const NodeAM<IdType, WeightType, DataType> * dst_p){

		if(adjacency_matrix.get_entry(src_p->internal_id, dst_p->internal_id) == 0)
			return false;
		
		return true;
	}

	// auto get_edge(const NodeAL<IdType, WeightType, DataType> * src_p, 
	// 	const NodeAL<IdType, WeightType, DataType> * dst_p){

	// 	/*Lets findout if dst_p in in neghbours of src_p */
	// 	auto it = 
	// 	find_if(src_p->neighbours.begin(), 
	// 	src_p->neighbours.end(),
 //    	[&](const pair<NodeAL<IdType, WeightType, DataType>*, WeightType>& element)
 //    		{return element.first == dst_p;});

	// 	if(it != src_p->neighbours.end())
	// 		return it;
		
	// 	//TODO: FIX
	// 	return it;
	// }
};

/************************* NodeAM Class ****************************/

/* Adjacency list implementation node wrapper */
//TODO: Need Comparable on ID type here
template <typename IdType, typename WeightType, typename DataType>
class NodeAM{
friend class GraphAM<IdType, WeightType, DataType>;
public:

	/* Need to think about other constructors here a little */
	/* Existance of NodeAL only maks sense in the context of a graph */
	NodeAM(GraphAM<IdType, WeightType, DataType>* graph,
		const shared_ptr<Node<IdType, DataType>> user_node){
		/* Get the new internal id */
		internal_id = graph->get_new_id();

		user_node_p = user_node;
	}

private:
	/* Used to boost the performance of implementation graph*/
	long internal_id;
	
	/* Pointer to the user created node */
	shared_ptr<Node<IdType, DataType>> user_node_p;


	bool operator==(const NodeAM& rhs){
		return (*(this->user_node_p))==(*(rhs.user_node_p));
	}
};

#endif