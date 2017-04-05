#ifndef GRAPH_AL
#define GRAPH_AL

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <assert.h>
#include <stdexcept>
#include <utility>
#include "graph_concepts.h"

//typedef std::shared_ptr<IdType> IdPtr;
// template <typename IdType>
// typedef std::shared_ptr<NodeAL<IdType>> NodeALPtr;



using namespace std;

template <typename IdType, typename WeightType>
class NodeAL;
template <typename IdType, typename WeightType>
requires Comparable<IdType>
class GraphAL;

/************************* GraphAL Class ****************************/
template <typename IdType, typename WeightType>
requires Comparable<IdType>
class GraphAL{
friend class NodeAL<IdType, WeightType>;
public:
	/* Need to add more constructors such as list initialization here*/
	GraphAL(){
		next_unique_id = 0;
		cout << "created a graph\n";
	}

	// Function return the neighbours of the node
	// vector<shared_ptr<NodeAL<IdType>>>& neighbours(IdType& src){
	// 	Pointer<NodeAL> _src = id_map.find(src.id);
	// 	return _src->neighbours;
	// }

/* 	TODO: For these we need to decide what we do if the operation 
 *	is already true. ex. add_vertex when the vertex is already there.
 *	Exception? return false? */
	bool adjacent(const IdType& src, const IdType& dst){

		if(!vertices_in_graph(src, dst)){
			throw std::invalid_argument("vertex not in the graph");
		}

		if(adjacent(get_wrapper_p(src), get_wrapper_p(dst))){
			return true;
		}

		return false;
	}

	bool add_vertex(IdType x){
		
		/* Check if the vertex is already in the graph */
		if(id_map.find(x) != id_map.end()){
			throw std::invalid_argument("vertex already added");
		}

		/* Create the wrapper and add it to adjacency list */
		NodeAL<IdType, WeightType>* vertex_p = 
			new NodeAL<IdType, WeightType>(*this, x);
		int internal_id = vertex_p->internal_id;

		//TODO: factor this out into a helper?
		if(internal_id == next_unique_id - 1){
			adjacency_list.push_back(vertex_p);
		}else{
			adjacency_list[internal_id] = vertex_p;
		}
		
		/* Add the new mapping into the map */
		id_map[x] = vertex_p;
		assert(id_map.find(x)->second == vertex_p); //ASSERT
		return true;
	}

	bool remove_vertex(IdType x){

		/* Check if the vertex is not in the graph */
		if(id_map.find(x) == id_map.end()){
			throw std::invalid_argument("vertex not in the graph");
		}

		/* Get the internal id of the wrapper of x */
		int internal_id = id_map.find(x)->second->internal_id;

		/* Remove all outgoing endes from the vertex */
		adjacency_list[internal_id]->neighbours.clear();

		/* Destroy incoming edges */
		for(auto node_p : adjacency_list){
			if(node_p == nullptr) continue;
			for(int i = 0; i < node_p->neighbours.size(); ++i){
				if((node_p->neighbours[i]).first == get_wrapper_p(x))
					node_p->neighbours.erase(node_p->neighbours.begin() + i);
			}
		}

		/* Delete the wrapper */
		//TODO: discuss the naked delete and smart pointers and etc
		delete adjacency_list[internal_id];

		/* This slot is going t be resused when id recycling kicks in*/
		adjacency_list[internal_id] = nullptr;


		/* Get the unique id back for id recycling */
		return_id(internal_id);

		/* Erase the vertex from the wrapper map */
		id_map.erase(x);
		return true;
	}

	/* notice how these functions avoid the adjacency list structure
	in the graph all together*/
	//TODO: figure out how to give a WeightType a default value
	bool add_edge(const IdType& src, const IdType& dst){
		throw std::invalid_argument("NEED DEFAULT VALUE DECISION HERE!");
		return true;
	}

	bool add_edge(const IdType& src, const WeightType w, 
		const IdType& dst){
		/* All we need to do here is to add a pointer
		to n2 to the neighbours of n1*/

		/* First we need to check if the nodes are in the graph */
		if(!vertices_in_graph(src, dst)){
			throw std::invalid_argument("src or dst of the edge not in the graph");
		}

		/* Get hold of the wrappers */
		NodeAL<IdType, WeightType> * src_p = get_wrapper_p(src);
		NodeAL<IdType, WeightType> * dst_p = get_wrapper_p(dst);

		/* Check if the edge already exists, if it does, 
		throw an exception */
		if(adjacent(src_p, dst_p)){
			throw std::invalid_argument("edge already exists");
		}

		/* Now we are sure the edge is not already represented,
		so lets just add it to the back of the vector */
		src_p->neighbours.push_back(make_pair(dst_p, w));

		return true;
	}

	bool remove_edge(const IdType& src, const IdType& dst){

		if(!vertices_in_graph(src, dst)){
			throw std::invalid_argument("src or dst of the edge not in the graph");
		}

		/* Get hold of the wrappers */
		NodeAL<IdType, WeightType> * src_p = get_wrapper_p(src);
		NodeAL<IdType, WeightType> * dst_p = get_wrapper_p(dst);

		/* If they are already not adjacent, nothing to remove*/
		if(!adjacent(src_p, dst_p)){
			throw std::invalid_argument("edge does not exist");
		}

		/* Erase the neighbour element. Should not fail
		since we know they are adjacent. */
		/* #readability */
		src_p->neighbours.erase(find_if(src_p->neighbours.begin(), 
		src_p->neighbours.end(),
    	[&](const pair<NodeAL<IdType, WeightType>*, WeightType>& element)
    		{return element.first == dst_p;}));

		return true;
	}

	void print_graph() {
		for(auto node_p : this->adjacency_list){
			if(node_p == nullptr) continue;
			cout << *(node_p->user_id_p) << ": ";
			for(auto edge : node_p->neighbours){
				cout << *((edge.first)->user_id_p) << " ";
			}
			cout << endl;
		}
	}
/*	TODO: Not sure how these factor into our library
 *	get_vertex_value(G, x): returns the value associated with the vertex x;
 *	set_vertex_value(G, x, v): sets the value associated with the vertex x to v. */
private:
	
	/* Vector of smart pointers to wrappers. This allows direct access
	to the neighbours of the node from its wrapper. The penalty – vertex
	removal */
	vector<NodeAL<IdType, WeightType>*> adjacency_list;
	// Need this map to go from Node -> NodeAL
	map<IdType, NodeAL<IdType, WeightType>*> id_map;

	/* Same idea as for GraphAM here */
	long next_unique_id;
	vector<int> free_ids;

	/* Function hands out the new id when a vertex is added*/
	long get_new_id(){
		if(free_ids.empty()){
			return next_unique_id++;
		}else{
			int temp = free_ids.back();
			free_ids.pop_back();
			return temp;
		}
	}

	bool return_id(int internal_id){
		free_ids.push_back(internal_id);
	}

	bool vertex_in_graph(const IdType& x){
		if(id_map.find(x) != id_map.end()){
			return true;
		}
		return false;
	}

	bool vertices_in_graph(const IdType& x, const IdType& y){
		return (vertex_in_graph(x) && vertex_in_graph(y));
	}

	/* NOTE: Assumes x is in the graph */
	NodeAL<IdType, WeightType>* get_wrapper_p(const IdType& x){
		return id_map.find(x)->second;
	}

	bool adjacent(const NodeAL<IdType, WeightType> * src_p, 
		const NodeAL<IdType, WeightType> * dst_p){
		// if(find(src_p->neighbours.begin(), 
		// 	src_p->neighbours.end(), dst_p) != src_p->neighbours.end()){
		// 	return true;
		// }

		/* Lets findout if dst_p in in neghbours of src_p */
		auto it = 
		find_if(src_p->neighbours.begin(), 
		src_p->neighbours.end(),
    	[&](const pair<NodeAL<IdType, WeightType>*, WeightType>& element)
    		{return element.first == dst_p;});

		if(it != src_p->neighbours.end())
			return true;
		
		return false;
	}
};

/************************* NodeAL Class ****************************/

/* Adjacency list implementation node wrapper */
//TODO: Need Comparable on ID type here
template <typename IdType, typename WeightType>
class NodeAL{
friend class GraphAL<IdType, WeightType>;
public:
	/* Need to think about other constructors here a little */
	/* Existance of NodeAL only makes sense in the context of a graph */
	NodeAL(GraphAL<IdType, WeightType>& graph, IdType& user_id){
		/* Get the new internal id */
		internal_id = graph.get_new_id();
		
		/* No neighbours yet, so empty vector */
		//neighbours = vector<NodeAL<IdType, WeightType>*>();

		user_id_p = &user_id;
	}

private:
	/* Necessary to distinguish the node within the graph*/
	long internal_id;

	/* This way, we avoid indexing into the adjacency list */
	/* For now, lets store the Weight by value */
	vector<pair<NodeAL<IdType, WeightType>*, WeightType>> neighbours;
	
	/* Smart pointer to the user created object, my be comparable */
	IdType* user_id_p;

	bool operator==(const NodeAL& rhs){
		return (*(this->user_id_p))==(*(rhs.user_id_p));
	}
};


// class Edge {
// public:
//     NodeAL* start;    // edge's starting vertex (required by Graph)
//     NodeAL* finish;   // edge's ending vertex (required by Graph)
//     double cost;      // edge weight (required by Graph)
//     double& weight;   // alias of cost; they are the same field
//     bool visited;     // whether this edge has been visited before (initally false; you can set this)

//     Edge(Vertex* start = nullptr, NodeAL* finish = nullptr, double cost = 0.0) : start(start),
//     finish(finish), cost(cost), weight(this->cost)
//     {
//     this->extraData = nullptr;
//     this->resetData();
//     }

//     /*
//      * Frees up any memory dynamically allocated by this edge.
//      */
// 	~Edge() {
//     if (this->extraData != nullptr) {
//         // delete this->extraData;
//     	}
// 	}


//     /*
//      * Wipes the supplementary data of this vertex back to its initial state.
//      * Specifically, sets visited to false.
//      */
//     void resetData(){
//     	this->visited = false;
//     }

// };
#endif
