#ifndef GRAPH_H
#define GRAPH_H


/* THE TODO LIST 
1) Fix the move, assignment adn copy constructors of Node.
Remember, it should not be possible to make a copy of a Node.
User must go through create_node function*
2) Provide the deletion and creation functions
3) node.is_in(graph) to quickly check memmbership 
4) Overrid comparisons for Edges and maybe few more useful operators */


template <typename IdType, typename DataType>
class Node;
template <typename IdType, typename WeightType, typename DataType>
class Edge;

//TODO:Make it a smart pointer
//TODO:add creation that deduces the id using concepts like Andrew described

/* If we offer this one, we shuld make sure user cannot create a Node using the constructor i.e
   we need to rewrite this function if we decide to go with it */
template <typename IdType, typename DataType>
Node<IdType, DataType>& create_node(IdType id, DataType* data){
	return *(new Node<IdType, DataType>(id, data)); 
}

template <typename IdType, typename WeightType, typename DataType>
Edge<IdType, WeightType, DataType>& create_edge(
	const Node<IdType, DataType>& src,
	const WeightType w,
	const Node<IdType, DataType>& dst){

	return *(new Edge<IdType, WeightType, DataType>(src, w, dst)); 
}

//TODO: Decide if we offer this one
template <typename IdType, typename DataType>
void delete_node(Node<IdType, DataType>& node){
	delete &node; 
}

template <typename IdType, typename WeightType, typename DataType>
class Edge{
	const Node<IdType, DataType>* src;
	const Node<IdType, DataType>* dst;
	WeightType w;

	Edge(const Node<IdType, DataType>& src, WeightType w,
	 const Node<IdType, DataType>& dst){
		this->src = &src;
		this->dst = &dst;
		this->w = w;
	}
};

template <typename IdType, typename DataType>
class Node{
	IdType id;
	DataType* data;
	/* We can add other bookeeping field here to boost
	performace of some algorithms */
	Node(IdType id, DataType* data){
		this->id = id;
		this->data = data;
	}

	IdType get_key() const {
		return this->id;
	}

	DataType* get_data(){
		return this->data;
	}

	bool operator==(const Node& rhs){
		return (this->id==rhs.id);
	}

	void print_node() const {
		cout << get_key();
	}

};

template <typename IdType, typename DataType>
void print_nodes(vector<const Node<IdType, DataType>*>& node_ps){
	for(auto node_p : node_ps){
		node_p->print_node();
		cout << " ";
	}
	cout << endl;
}




#endif