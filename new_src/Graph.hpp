#ifndef GRAPH_H
#define GRAPH_H

template <typename IdType, typename DataType>
class Node;
template <typename IdType, typename WeightType, typename DataType>
class Edge;

//TODO:Make it a smart pointer
//TODO:add creation that deduces the id using concepts like Andrew described

/* If we offer this one, we shuld make sure user cannot create a Node using the constructor i.e
   we need to rewrite this function if we decide to go with it */
template <typename IdType, typename DataType>
Node<IdType, DataType>* create_node(IdType id, DataType* data){
	return new Node<IdType, DataType>(id, data); 
}

template <typename IdType, typename WeightType, typename DataType>
Edge<IdType, WeightType, DataType>* create_edge(
	const Node<IdType, DataType>& src,
	const WeightType w,
	const Node<IdType, DataType>& dst){

	return new Edge<IdType, WeightType, DataType>(src, w, dst); 
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

	bool operator==(const Node& rhs){
		return (this->id==rhs.id);
	}

};



#endif