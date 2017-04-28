/// \file
/// \brief Helper functions to be included in the main header file are declared

#ifndef GRAPH_LIB_HEADER_HELPER
#define GRAPH_LIB_HEADER_HELPER

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<typename G::element_type::vertex_wrapper_type> get_vertex_wrapper(G g, V v);

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
shared_ptr<typename G::element_type::vertex_wrapper_type> get_vertex_wrapper(G g, V v);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
vector<typename G::element_type::edge_type> get_edges_for_vertex(G g, V v);

template<typename G, typename V>
requires Matrix_Graph<G> && Vertex_ptr<V>
vector<typename G::element_type::edge_type> get_edges_for_vertex(G g, V v);

template<typename G>
requires Graph<G>
vector<typename G::element_type::vertex_type> get_vertices(G g);

template<typename G>
requires Matrix_Graph<G>
vector<typename G::element_type::vertex_type> get_vertices(G g);

template<typename G>
requires Graph<G>
vector<int> get_vertices_ids(G g);

template<typename G>
requires Matrix_Graph<G>
vector<int> get_vertices_ids(G g);

template<typename G>
requires Graph<G>
vector<int> get_vertex_wrapper_ids(G g);

template<typename G>
requires Matrix_Graph<G>
vector<int> get_vertex_wrapper_ids(G g);

template<typename G>
requires Graph<G>
int num_vertices(G g);

template<typename G>
requires Matrix_Graph<G>
int num_vertices(G g);

template<typename G, typename E>
requires Graph<G> && Edge_ptr<E>
Value value(G g, E e);

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V> 
Value value(G g, V x);

#endif
