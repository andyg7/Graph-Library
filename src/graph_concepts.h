#ifndef GRAPH_CONCEPTS_H
#define GRAPH_CONCEPTS_H

#include <string>
/*
   The included files from here...
 */
#include <stl2/detail/concepts/object.hpp>
#include <stl2/detail/fwd.hpp>
#include <stl2/detail/meta.hpp>
#include <stl2/detail/concepts/core.hpp>
#include <stl2/detail/concepts/object/assignable.hpp>
#include <stl2/detail/concepts/object/regular.hpp>
#include <stl2/iterator.hpp>
/*
   ... to here are from https://github.com/CaseyCarter/cmcstl2
 */

using namespace std;

/*
   Dummy types used for member type concept overloading
 */
struct Graph {};
struct DAG : Graph {};
struct DG : Graph {};
struct DT : DG {};

template<typename X> 
using Value_type = typename X::value_type;
using Value = std::pair<string, int>;


template<typename T>
concept bool Comparable =
requires (T t1, T t2) {
	{ t1 == t2 } -> bool;
	{ t1 != t2 } -> bool;
	{ t1 < t2 } -> bool;
	{ t1 > t2 } -> bool;
	{ t1 <= t2 } -> bool;
	{ t1 >= t2 } -> bool;
};

template<typename T>
concept bool Numeric =
requires (T t1, T t2) {
	{ t1 + t2 } -> T;
	{ t1 - t2 } -> T;
	{ t1 * t2 } -> T;
	{ t1 / t2 } -> T;
	{ t1 % t2 } -> T;

	t1 = 0;
};

template<typename A, typename B>
concept bool Same_type = 
requires (A a, B b) {
	{ a } -> B;
	{ b } -> A;
};

template<typename T>
concept bool Sequence =
requires(T t) {
	typename T::value_type;
	typename T::iterator;
	{ begin(t) } -> typename T::iterator;
	{ end(t) } -> typename T::iterator;
	requires std::experimental::ranges::Iterator<typename T::iterator>();
};

/*
   Vertex concept
   Just needs to be comparable
 */
template<typename V>
concept bool Vertex =
requires (V v1, V v2) {
	{ v1 == v2 } -> bool;
	requires std::experimental::ranges::Assignable<V&, V>();
	requires std::experimental::ranges::Constructible<V>();
	requires std::experimental::ranges::Copyable<V>();
	requires std::experimental::ranges::Movable<V>();
};

/*
   Like a Vertex, but has an int for a key
   that can be retrieved via get_key()
 */
template<typename V>
concept bool Vertex_numeric_id =
requires (V v1, V v2) {
	requires Vertex<V>;
	{ v1.get_key() } -> int;
};

template<typename G, typename T>
concept bool Vertex_wrapper = 
requires (G g, T t) {
	t->vertex_data;
	{ t->vertex_data } -> typename G::vertex_type;
	{ t->value } -> Value;
	requires Vertex<typename G::vertex_type>;
};

/*
   Edge concept
   Must consist of two fields v1 v2, each of which are vertices
 */
template<typename E>
concept bool Edge =
requires (E e1, E e2) {
	e1.v1;
	e2.v2;
	typename E::vertex_type;	
	{ e1.v1 } -> typename E::vertex_type;
	{ e1.v2 } -> typename E::vertex_type;
	requires Vertex<typename E::vertex_type>;	
	requires std::experimental::ranges::Assignable<E&, E>();
	requires std::experimental::ranges::Constructible<E>();
	requires std::experimental::ranges::Copyable<E>();
	requires std::experimental::ranges::Movable<E>();
};

template<typename E>
concept bool Edge_cost = 
requires (E e1, E e2) { 
	e1.cost;
	typename E::cost_type;
	{ e1.cost } -> typename E::cost_type;
	requires Comparable<typename E::cost_type>;
	requires Numeric<typename E::cost_type>;
};

template<typename G, typename E>
concept bool Edge_wrapper = 
requires (G g, E e) {
	e->value;
	e->edge;
	{ e->value } -> Value;
	{ e->edge } -> typename G::edge_type;
	requires Vertex_wrapper<G, typename G::vertex_header_type::vertex_wrapper_type>;
};

template<typename E, typename V>
concept bool matching_vertices_edges =
requires (E e, V v) {
	requires Vertex<V>;
	{ e.v1 } -> V;
	{ e.v2 } -> V;
};

template<typename G, typename T>
concept bool Vertex_header = 
requires (G g, T t) {
	t.vertex_wrapper_data;
	{ t.vertex_wrapper_data } -> typename T::vertex_wrapper_type;
	{ t.neighbors } -> typename T::neighbors_type;
	{ t.edges } -> typename T::edges_type;
	requires Vertex_wrapper<G, typename T::vertex_wrapper_type>;
	requires Vertex_wrapper<G, typename T::neighbors_type::value_type>;
	requires Edge_wrapper<G, typename T::edges_type::value_type>;
	requires Sequence<typename T::neighbors_type>;
	requires Sequence<typename T::edges_type>;
};

template<typename G>
concept bool is_dag = 
requires (G g) {
	{ g } -> DAG;
};

template<typename G>
concept bool is_dt = 
requires (G g) {
	{ g } -> DT;
};

template<typename G>
concept bool is_dg = 
requires (G g) {
	{ g } -> DG;
};

template<typename GT, typename T>
concept bool Shared_ptr = 
requires (GT gt, T t) {
	{ t } -> shared_ptr<GT>;
};

/*
Graph concept
- must have certain member types
- must have an underlying data structure adjacency list
- must have a header type where nodes are stored
*/
template<typename G>
concept bool Graph = 
requires (G g) {
	{ g.underlying_data } -> typename G::underlying_data_type;
	requires Sequence<typename G::underlying_data_type>

	typename G::graph_type;
	typename G::edge_type;
	typename G::vertex_type;
	typename G::vertex_header_type;
	typename G::underlying_data_type;

	requires matching_vertices_edges<typename G::edge_type, typename G::vertex_type>;
	requires Same_type<typename G::vertex_type, typename G::underlying_data_type::value_type::vertex_wrapper_type::element_type::vertex_type>
	requires Same_type<typename G::vertex_header_type, typename G::underlying_data_type::value_type>

	requires Vertex_header<G, typename G::underlying_data_type::value_type>;

	requires std::experimental::ranges::Constructible<G>();
	requires std::experimental::ranges::Assignable<G&, G>();
	requires std::experimental::ranges::Copyable<G>();
	requires std::experimental::ranges::Movable<G>();
};

template<typename G>
concept bool Heuristic_graph = 
requires (G g) {
	requires Graph<G>;
	typename G::vertex_type::heuristic_function_type;
	requires Numeric<typename G::vertex_type::heuristic_function_type>;
};
/*
   Must be a Graph AND the member type 'graph_type' must be dag
 */
template<typename G>
concept bool DAG_Graph = 
requires (G g) {
	requires Graph<G>;
	requires is_dag<typename G::graph_type>;
};

/*
   Must be a Graph AND the member type 'graph_type' must be dg
 */
template<typename G>
concept bool DG_Graph = 
requires (G g) {
	requires Graph<G>;
	requires is_dg<typename G::graph_type>;
};

/*
   Must be a Graph AND the member type 'graph_type' must be dt
 */
template<typename G>
concept bool DT_Graph = 
requires (G g) {
	requires Graph<G>;
	requires is_dt<typename G::graph_type>;
};

/*
   Makes sure edge type provided is compatible with the supplied graph
   Also edge type must be a shared ptr
 */
template<typename G, typename E>
concept bool Graph_and_Edge_ptr =
requires (G g, E e) {
	requires Graph<G>;
	{ *e } -> typename G::edge_type;
	requires Edge<typename G::edge_type>;
	requires Shared_ptr<typename G::edge_type, E>;
};

/*
   Makes sure vertex type provided is compatible with the supplied graph
   Also vertex type must be a shared ptr
 */
template<typename G, typename V>
concept bool Graph_and_Vertex_ptr =
requires (G g, V v) {
	requires Graph<G>;
	{ *v } -> typename G::vertex_type;
	requires Vertex<typename G::vertex_type>;
	requires Shared_ptr<typename G::vertex_type, V>;
};

template<typename G, typename V>
concept bool Heuristic_graph_and_Vertex_ptr =
requires (G g, V v) {
	requires Heuristic_graph<G>;
	{ *v } -> typename G::vertex_type;
	requires Vertex<typename G::vertex_type>;
	requires Shared_ptr<typename G::vertex_type, V>;
};

#endif
