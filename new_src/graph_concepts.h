#ifndef GRAPH_CONCEPTS_H
#define GRAPH_CONCEPTS_H

#include <string>
/*
   The included files from here...
 */
//#include <stl2/detail/concepts/object.hpp> *compiles
//#include <stl2/detail/fwd.hpp> does not
//#include <stl2/detail/meta.hpp> does not
//#include <stl2/detail/concepts/core.hpp> does not
//#include <stl2/detail/concepts/object/assignable.hpp> compiles
//#include <stl2/detail/concepts/object/regular.hpp> *compiles
//#include <stl2/iterator.hpp> *compiles 
/*
   ... to here are from https://github.com/CaseyCarter/cmcstl2
 */
#include <vector>

using namespace std;

/*
   Dummy types used for member type concept overloading
 */
struct Graph {};
struct DAG : Graph {};
struct DG : Graph {};
struct DT : DG {};
struct Matrix_graph {};

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

template<typename G>
concept bool is_matrix = 
requires (G g) {
	{ g } -> Matrix_graph;
};

template<typename P>
concept bool Ptr = 
requires (P p) {
	*p;
};

template<typename P>
concept bool Shared_ptr = 
requires (P p) {
	typename P::element_type;
	*p;
};

template<typename N>
concept bool Node_ptr = 
requires (N n) {
	requires Shared_ptr<N>;
	typename N::element_type::id_type;
	typename N::element_type::data_type;
};

template<typename G>
concept bool Graph_ptr = 
requires (G g) {
	requires Shared_ptr<G>;
	typename G::element_type::id_type;
	typename G::element_type::weight_type;
};

template<typename S>
concept bool Expandable_state = 
requires (S s) {
	requires Shared_ptr<S>;
	{ s->expand() } -> vector<S>;
};

#endif
