

/* 
These is the copy/paste from wikipedia. These are the operations
that we have to support. 

The basic operations provided by a graph data structure G usually include:[1]

*adjacent(G, x, y): tests whether there is an edge from the vertex x to the vertex y;
*neighbors(G, x): lists all vertices y such that there is an edge from the vertex x to the vertex y;
add_vertex(G, x): adds the vertex x, if it is not there;
*remove_vertex(G, x): removes the vertex x, if it is there;
*add_edge(G, x, y): adds the edge from the vertex x to the vertex y, if it is not there;
*remove_edge(G, x, y): removes the edge from the vertex x to the vertex y, if it is there;
get_vertex_value(G, x): returns the value associated with the vertex x;
set_vertex_value(G, x, v): sets the value associated with the vertex x to v.


Structures that associate values to the edges usually also provide:[1]
get_edge_value(G, x, y): returns the value associated with the edge (x, y);
set_edge_value(G, x, y, v): sets the value associated with the edge (x, y) to v.
*/

// This is the class the user is going to interact with
#define AL 0
#define AM 1
#define NO_EDGE 0

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

	
	//Lock lock_graph;
	bool adjacent(Node& src, Node& dst){
		// Index into the matrix using the internal ids
		return (bool) m[id_map.find(src.id)][id_map.find(dst.id)];
	}

	// Function return the neighbours of the node
	vector<Pointer<Node>>& neighbours(Node& src){
		int internal_id = get_internal_id(src);
		vector<Pointer<Node>> neighbours;
		// Not sure how to express it proprly, but you get the idea
		for(int i = 0; i < m.columns(); i++){
			if(m[internal_id][i] == NO_EDGE)
				continue;
			neighbours.add(get_user_node(i));
		}
		return neighbours;
	}

	// Should we throw an exception if the nodes are not part of the graph,
	// or should we quietly add them? 
	bool add_edge(Edge& e){
		int row = get_internal_id(e.src.internal_id);
		int column = get_internal_id(e.dst.internal_id);
		m[row][column] = e.weight;
		return true;

	}
	bool add_edge(Node& src, Number weight, Node& dst){
		add_edge(Edge e(src, weight, dst));
	}


	bool remove_edge(Node& src, Number weight, Node& dst){
		remove_edge(Edge e(src, weight, dst));
	}
	bool remove_edge(Edge& e){
		int row = get_internal_id(e.src.internal_id);
		int column = get_internal_id(e.dst.internal_id);
		m[row][column] = NO_EDGE; // need to figure out what is this no edge
		return true;

	}


	// Should it maybe throw an exception the node was not in 
	// the graph for starters
	bool remove_node(Node& n){
		Pointer<NodeAM> _n = get_wrapper(n);
		int internal_id = _src->internal_id;

		// We want to zero out the column and the row
		for(int i = 0; i < m.columns(); i++){
			// Call routine here to zero out row internal_id
		}
		for(int i = 0; i < m.rows(); i++){
			// To zero out a column here
		}
		// Puts the id beack into the list of free ids for id recycle
		return_id(internal_id);

		// The destructor of the wrapper should destroy the wrapper at this
		// point
		return true;
		
	}

	bool add_node(Node& n){
		// Get the constructor of NodeAM to init everything
		Pointer<NodeAM> nam = new NodeAM(next_unique_id++, n);
		
		// Resize the matrix
		m.add_row();
		m.add_column();

		return true;
	}

private:
	id_type user_type;

	/* The adjacency matrix, where each entry is a numeric weight(?) */
	Matrix<Number> m;

	/* Rolling unique id. Give out 0, then 1, then 2, and etc. */
	long next_unique_id;
	
	/* 	After deletion of a node, an id gets freed. 
	Put it here and when creating enxt node, 
	look in this que first */
	vector<int> free_ids;

	// Map user node id to the implementation wrapper
	map<user_type, Pointer<NodeAM>> id_map;
	// Map internal id back to the user node 
	map<int, Pointer<Node>> node_map;

	Pointer<GraphAM> get_wrapper(Node& n){
		return id_map.find(n.id);
	}

	Pointer<Node> get_user_node(int internal_id){
		return node_map.find(internal_id);
	}
	int get_internal_id(Node& n){
		return get_wrapper(src)->internal_id
	}
	bool return_id(internal_id){
		free_ids.add(internal_id);
	}
}

class GraphAL{
	/* Vector of pointers to wrappers */
	vector<Pointer<NodeAL>> adjacency_list;
	// Need this map to go from Node -> NodeAL
	map<user_type, Pointer<NodeAM>> id_map;

	/* Same idea as for GraphAM here */
	long next_unique_id;
	vector<int> free_ids;

	// Function return the neighbours of the node
	vector<Pointer<Node>>& neighbours(Node& src){
		Pointer<NodeAL> _src = id_map.find(src.id);
		return _src->neighbours;
	}

}

// Adjacency Matrix implementation node
class NodeAM{

	/* Our internal numeric id used to index into adjacency matrix */
	int internal_id;

	Pointer<Node> node; 
}

// Adjacency list implementation node
class NodeAL{
	// Necessary to distinguis the wrappers withing the graph implementation
	int internal_id;
	vector<NodeAL> neighbors;

	Pointer<Node> node;
}

// General node, that is used by the implementations
// DataType must be comparable
template <typename IdType>
requires Comparable // we want == defined
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

/* We need to think about this a litle more. An edge can exist without 
a graph coming with it. I can say add this edge, created long before, to
this graph. Edges represent a realationship. One can think of Edge
object as a function, that when applied to a Graph object, mutates
the graph object. Edge is always this object, but when it is applied to
different implementations different code gets executed on that basis. */
class Edge{
	Node src;
	Node dst;
	Number weight;
}




