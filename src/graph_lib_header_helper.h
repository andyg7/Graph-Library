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

#endif
