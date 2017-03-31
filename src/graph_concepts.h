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
	v1.vertex_id;
	{ v1 == v2 } -> bool;
	requires std::experimental::ranges::Assignable<V&, V>();
	requires std::experimental::ranges::Constructible<V>();
	requires std::experimental::ranges::Copyable<V>();
	requires std::experimental::ranges::Movable<V>();
};

template<typename V>
concept bool Vertex_ptr =
requires (V v) {
	typename V::element_type;
	requires Vertex<typename V::element_type>;
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
	{ v1.set_key(0) } -> void;
};

/*
   Edge concept
   Must consist of two fields v1 v2, each of which are vertices
 */
template<typename E>
concept bool Edge =
requires (E e1, E e2) {
	e1.v1;
	e1.v2;
	e1.cost;
	typename E::vertex_type;	
	typename E::cost_type;	
	{ e1.v1 } -> typename E::vertex_type;
	{ e1.v2 } -> typename E::vertex_type;
	{ e1.cost } -> typename E::cost_type;

	requires Vertex<typename E::vertex_type>;	
	requires Numeric<typename E::cost_type>;

	requires std::experimental::ranges::Assignable<E&, E>();
	requires std::experimental::ranges::Constructible<E>();
	requires std::experimental::ranges::Copyable<E>();
	requires std::experimental::ranges::Movable<E>();
};

template<typename E>
concept bool Edge_ptr =
requires (E e1, E e2) {
	typename E::element_type;
	requires Edge<typename E::element_type>;
};

template<typename E, typename V>
concept bool Matching_vertices_edges =
requires (E e, V v) {
	{ e.v1 } -> V;
	{ e.v2 } -> V;
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

/*
Graph concept
- must have certain member types
- must have an underlying data structure adjacency list
- must have a header type where nodes are stored
*/
template<typename G>
concept bool Graph = 
requires (G g) {
	typename G::graph_type;
	typename G::edge_type;
	typename G::vertex_type;
	typename G::vertex_wrapper_type;
	typename G::vertex_header_type;
	typename G::underlying_data_type;

	{ g.underlying_data } -> typename G::underlying_data_type;
	requires Sequence<typename G::underlying_data_type>
	requires Same_type<typename G::edge_type::vertex_type, typename G::vertex_type>;

	requires std::experimental::ranges::Constructible<G>();
	requires std::experimental::ranges::Assignable<G&, G>();
	requires std::experimental::ranges::Copyable<G>();
	requires std::experimental::ranges::Movable<G>();
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

template<typename G>
concept bool Heuristic_graph = 
requires (G g) {
	requires Graph<G>;
	typename G::vertex_type::heuristic_function_type;
	requires Numeric<typename G::vertex_type::heuristic_function_type>;
};

#endif
