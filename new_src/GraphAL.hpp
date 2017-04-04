#ifndef GRAPH_AL
#define GRAPH_AL

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>


//typedef std::shared_ptr<IdType> IdPtr;
// template <typename IdType>
// typedef std::shared_ptr<NodeAL<IdType>> NodeALPtr;



using namespace std;

template <typename IdType>
class NodeAL;

template <typename IdType>
class GraphAL;

/* Adjacency list implementation node wrapper */
//TODO: Need Comparable on ID type here
template <typename IdType>
class NodeAL{

public:
	/* Need to think about other constructors here a little */
	/* Existance of NodeAL only makes sense in the context of a graph */
	NodeAL(GraphAL<IdType>& graph, IdType& user_id){
		/* Get the new internal id */
		internal_id = graph.get_new_id();
		
		/* No neighbours yet, so empty vector */
		neighbours = vector<shared_ptr<NodeAL<IdType>>>();

		user_id_p = &user_id;
	}

private:
	/* Necessary to distinguish the node within the graph*/
	long internal_id;
	/* This way, we avoid indexing into the adjacency list*/
	vector<shared_ptr<NodeAL<IdType>>> neighbors;
	
	/* Smart pointer to the user created object, my be comparable */
	IdType* user_id_p;

	bool operator==(const NodeAL& rhs){
		return (*(this->user_id_p))==(*(rhs.user_id_p));
	}
};


template <typename IdType>
class GraphAL{

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
	bool adjacent(IdType x, IdType y){
		return true;
	}
	bool add_vertex(IdType x){
		return true;
	}
	bool remove_vertex(IdType x){
		return true;
	}
	bool add_edge(IdType x, IdType y){
		return true;
	}
	bool remove_edge(IdType x, IdType y){
		return true;
	}

/*	TODO: Not sure how these factor into our library
 *	get_vertex_value(G, x): returns the value associated with the vertex x;
 *	set_vertex_value(G, x, v): sets the value associated with the vertex x to v. */
private:
	
	/* Vector of smart pointers to wrappers */
	vector<shared_ptr<NodeAL<IdType>>> adjacency_list;
	// Need this map to go from Node -> NodeAL
	std::map<IdType, shared_ptr<NodeAL<IdType>> > id_map;

	/* Same idea as for GraphAM here */
	long next_unique_id;
	vector<int> free_ids;

	/* Function hands out the new id when a vertex is added*/
	long get_new_id(){
		return next_unique_id++;
	}

};

#endif
