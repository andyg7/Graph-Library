#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "Graph.hpp"
using namespace std;

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

/* CREATION functions for user types */
template <typename IdType, typename DataType>
inline shared_ptr<Node<IdType, DataType>> create_node(IdType id, DataType* data){
	return Node<IdType, DataType>::create_node(id, data);
}

template <typename IdType, typename WeightType, typename DataType>
inline shared_ptr<Edge<IdType, WeightType, DataType>> create_edge(
	const shared_ptr<Node<IdType, DataType>> src,
	const WeightType w,
	const shared_ptr<Node<IdType, DataType>> dst){
	return Edge<IdType, WeightType, DataType>::create_edge(src, w, dst); 
}

//TODO: Add the concepts for GraphType, IdType and WeightType
template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline shared_ptr<GraphType<I, W, D>> create_graph(){
	return GraphType<I, W, D>::create_graph();
}


/* DELETION functions for user types (might reimplement this as smart poitners later) */ 
// template <typename IdType, typename DataType>
// inline void delete_node(shared_ptr<Node<IdType, DataType>> node){
// 	delete node; 
// }

// I dont think this is needed anymore due to smart pointers
// template <typename IdType, typename WeightType, typename DataType>
// inline void delete_edge(Edge<IdType, WeightType, DataType>* e){
// 	delete e;
// }
// template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
// inline void delete_graph(GraphType<I, W, D>* g){
// 	delete g;
// }

/************************* Edge Class ****************************/
template <typename IdType, typename WeightType, typename DataType>
class Edge{
public:

	/* Same as for edges, we don't want these to be copied by accident */
	Edge(Edge<IdType, WeightType, DataType> const&) = delete;
	void operator=(Edge<IdType, WeightType, DataType> const&) = delete;

	inline const shared_ptr<Node<IdType, DataType>> get_src() const {
		return src;
	}

	inline const shared_ptr<Node<IdType, DataType>> get_dst() const {
		return dst;
	}

	inline WeightType get_weight() const {
		return w;
	}

	inline WeightType set_weight(WeightType new_w){
		w = new_w;
	}

	inline static shared_ptr<Edge<IdType, WeightType, DataType>> create_edge(
		const shared_ptr<Node<IdType, DataType>> src,
		const WeightType w,
		const shared_ptr<Node<IdType, DataType>> dst){
		//return (new Edge<IdType, WeightType, DataType>(src, w, dst));
		shared_ptr<Edge<IdType, WeightType, DataType>> p  = make_shared<Edge<IdType, WeightType, DataType>>(src, w, dst);
		return p;
	}

	void print_edge() const {
		cout << "(" << this->src->get_id() << ", " << w << ", " << this->dst->get_id() << ")";
	}

	Edge(const shared_ptr<Node<IdType, DataType>> src, WeightType w,
	 const shared_ptr<Node<IdType, DataType>> dst){
		this->src = src;
		this->dst = dst;
		this->w = w;
	}

private:
	shared_ptr<Node<IdType, DataType>> src;
	shared_ptr<Node<IdType, DataType>> dst;
	WeightType w;
};

template <typename IdType, typename Weight, typename DataType>
inline bool compare_edges(const shared_ptr<Edge<IdType, Weight, DataType>> lhs,
	const shared_ptr<Edge<IdType, Weight, DataType>> rhs){
	cout << "hello\n";
	return lhs->get_weight() < rhs->get_weight();
}


/************************* Node Class ****************************/
template <typename IdType, typename DataType>
class Node{

private:
	IdType id;
	DataType* data;

public:

	using id_type = IdType;
	using data_type = DataType;

	Node(IdType id, DataType* data){
		//cout << id << " created\n";
		this->id = id;
		this->data = data;
	}

	/* We want to enforce existance of these objects in singular form,
	if somebody tries to copy them, we shall not let them do so!*/
	Node(Node<IdType, DataType> const&) = delete;
	void operator=(Node<IdType, DataType> const&) = delete;

	/* We can add other bookeeping field here to boost
	performace of some algorithms */
	inline IdType get_id() const {
		return this->id;
	}

	inline DataType* get_data(){
		return this->data;
	}

	inline void set_data(DataType * data){
		this->data = data;
	}

	inline bool operator==(const Node& rhs){
		return (this->id==rhs.id);
	}

	inline void print_node() const {
		cout << get_id();
	}

	inline static shared_ptr<Node<IdType, DataType>> create_node(IdType id, DataType* data){
		shared_ptr<Node<IdType, DataType>> p = make_shared<Node<IdType, DataType>>(id, data);
		return p;
	}

};

/* PRINTERS */
template <typename IdType, typename DataType>
void print_nodes(vector<shared_ptr<Node<IdType, DataType>>>& node_ps){
	for(auto node_p : node_ps){
		node_p->print_node();
		cout << " ";
	}
	cout << endl;
}

template <typename IdType, typename WeightType, typename DataType>
void print_edges(vector<shared_ptr<Edge<IdType, WeightType, DataType>>>& edges){
	for(auto edge : edges){
		edge->print_edge();
		cout << " ";
	}
	cout << endl;
}

/* Utility for creation */
template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline void add_nodes(const vector<shared_ptr<Node<I, D>>>& node_ps, shared_ptr<GraphType<I, W, D>> g){

	for(auto node_p : node_ps){
		g->add_node(node_p);
	}

	return;
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline void add_edges(const vector<shared_ptr<Edge<I, W, D>>>& edge_ps, shared_ptr<GraphType<I, W, D>> g){

	for(auto edge_p : edge_ps){
		g->add_edge(edge_p);
	}

	return;
}

/*                     IMPLEMENTATION WRAPPERS                          */
/* These are the wrappers around the implementation dependent function. */

template <typename I, typename W, typename D>
using EdgeSP = shared_ptr<Edge<I, W, D>>;\
template <typename I, typename D>
using NodeSP = shared_ptr<Node<I, D>>;
template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
using GraphSP = shared_ptr<GraphType<I, W, D>>;


template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline bool has_node(const GraphSP<I, W, D, GraphType> graph, const NodeSP<I, D> x){
	return graph->has_node(x);
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline bool has_edge(const GraphSP<I, W, D, GraphType> graph, EdgeSP<I, W, D> e){
	return graph->has_edge(e->get_src(), e->get_weight(), e->get_dst());
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline bool has_edge(const GraphSP<I, W, D, GraphType> graph, const NodeSP<I, D> src, const W w, 
		const NodeSP<I, D> dst){
	return graph->has_edge(src, w, dst);
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline vector<EdgeSP<I, W, D>> edges_of_node(const GraphSP<I, W, D, GraphType> graph,
	const NodeSP<I, D> x){
	return graph->edges_of_node(x);
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline vector<EdgeSP<I, W, D>> get_edges(const GraphSP<I, W, D, GraphType> graph){
	return graph->get_edges();
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline EdgeSP<I, W, D> get_edge(const GraphSP<I, W, D, GraphType> graph, NodeSP<I, D> src, NodeSP<I, D> dst){
	return graph->get_edge(src, dst);
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline vector<NodeSP<I, D>> get_nodes(const GraphSP<I, W, D, GraphType> graph){
	return graph->get_nodes();
}

template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline vector<NodeSP<I, D>> neighbours(const GraphSP<I, W, D, GraphType> graph, const NodeSP<I, D> src){
	return graph->neighbours(src);
}


template <typename I, typename W, typename D, template <typename, typename, typename> typename GraphType>
inline bool adjacent(const GraphSP<I, W, D, GraphType> graph, 
	const NodeSP<I, D> src, 
	const NodeSP<I, D> dst){
	return graph->adjacent(src, dst);
}








/* OPERATORS ON NODE SPs */
template <typename I, typename D>
inline bool operator==(const NodeSP<I, D>& lhs, const NodeSP<I, D>& rhs){ 
	return (lhs->get_id() == rhs->get_id());
}

template <typename I, typename D>
inline bool operator!=(const NodeSP<I, D>& lhs, const NodeSP<I, D>& rhs){ 
	return !(lhs == rhs);
}

/* OPERATORS EDGE SPs */
template <typename I, typename W, typename D>
inline bool operator==(const EdgeSP<I, W, D> lhs,
	const EdgeSP<I, W, D> rhs){
	return (lhs->get_weight() == rhs->get_weight())
		&& (lhs->get_src() == rhs->get_src())
		&& (lhs->get_dst() == rhs->get_dst());
}

template <typename I, typename W, typename D>
inline bool operator!=(const EdgeSP<I, W, D> lhs,
	const EdgeSP<I, W, D> rhs){
	return !(lhs == rhs);
}








#endif