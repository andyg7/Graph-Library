

/* 
These is the copy/paste from wikipedia. These are the operations
that we have to support. 

The basic operations provided by a graph data structure G usually include:[1]

adjacent(G, x, y): tests whether there is an edge from the vertex x to the vertex y;
neighbors(G, x): lists all vertices y such that there is an edge from the vertex x to the vertex y;
add_vertex(G, x): adds the vertex x, if it is not there;
remove_vertex(G, x): removes the vertex x, if it is there;
add_edge(G, x, y): adds the edge from the vertex x to the vertex y, if it is not there;
remove_edge(G, x, y): removes the edge from the vertex x to the vertex y, if it is there;
get_vertex_value(G, x): returns the value associated with the vertex x;
set_vertex_value(G, x, v): sets the value associated with the vertex x to v.


Structures that associate values to the edges usually also provide:[1]
get_edge_value(G, x, y): returns the value associated with the edge (x, y);
set_edge_value(G, x, y, v): sets the value associated with the edge (x, y) to v.
*/

// This is the class the user is going to interact with
#define AL 0
#define AM 1

class Graph{

	// On the basis of this type, different implementation specific
	// functions will be called.
	implementation_type type;

	// By default, use adjacency list representation
	Graph(){
		type = GraphAL;
		// Call the constructor appropriate to the type
		init_Graph(); 
	}

	// The constructor will require specification of what implementation to use
	Graph(int implementation){
		if(implementation == AL)
			type = GraphAL;
		else if(implementation == AM)
			type = GraphAM;
		init_Graph();
	}

	//adjacent()



}

class GraphAM{

	id_type user_type;

	/* The adjacency matrix */
	Matrix<Number> m;
	
	/* Rolling unique id. Give out 0, then 1, then 2, and etc. */
	long next_unique_id;
	
	/* 	After deletion of a node, an id gets freed. 
	Put it here and when creating enxt node, 
	look in this que first */
	vector<int> free_ids;

	// Map internal id's to user id's
	std::map<int, user_type> id_map;

	
	/* Bjarne said to move the locking responsibility ontp the user,
	 * so we do not need this lock. But that is a conscious choice of
	 * ours */
	/* Lock protecting the graph for multithreaded user code. Think 
	additions and deletions*/
	//Lock lock_graph;

	bool adjacent(NodeAM& src, NodeAM& dst){
		// Index into the matrix using the internal ids
		return m[src.id][dst.id];
	}


}

class GraphAL{
	/* Vector of pointers to wrappers */
	vector<Pointer<NodeAL>> adjacency_list;
}

// Adjacency Matrix implementation node
class NodeAM{
	/* Need a pointer back to the matrix, to be able to get neighbors
	of a node with sole knowledge of the node */
	Pointer<GraphAM> self_graph;

	/* Our internal numeric id used to index into adjacency matrix */
	int internal_id;
	Pointer<Node> node; 
}

// Adjacency list implementation node
class NodeAL{
	vector<NodeAL> neighbors;
	Pointer<Node> node;
}

// General node, that is used by the implementations
// DataType must be comparable
class Node{
	Pointer<IdType> id;
	/* Not sure this makes an sense. I think a node 
	shoudly contain the payload? Anyhow, there must be
	a field that is comparable. The way I see this, if I
	were to associate data (say state) with a node, I would have
	a struct{ string id; void * data;} and define == on string.*/
	bool operator==(Node& rhs){
		// Therefore its up to the user to define the equality of nodes
		return this.id==rhs.id;
	}
}

/* This class will represnet an Edge, mainly for purposes of representation :)
   I dont know if we will actually ever need*/
template <typename N> (N must be either a NodeAM or NodeAl)
class Edge{
	N src;
	N dst;
	Number weight;

}




