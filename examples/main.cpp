#include <iostream>
#include <cassert>
#include <vector>
#include "user_structs.h"
#include "../src/graph_lib.h"

using namespace std;
template<typename V, typename E>
void generic_dg_example();
template<typename V, typename E>
void generic_dag_example();
template<typename V, typename E>
void generic_dt_example();

template<typename V, typename E>
void generic_matrix_example();

template<typename T>
void pretty_print( T& l);

int main(int argc, char *argv[])
{
	assert(__cpp_concepts >= 201500);
	assert(__cplusplus >= 201500);

	using namespace graph_std_lib;
	/*
	   Example of using a DG graph with user defined vertex and user defined edge 
	 */
	cout << "********DG********\n";
	generic_dg_example<user_vertex_1, user_edge_1>();
	/*
	   Example of using a DAG graph with user defined vertex and user defined edge 
	 */
	cout << "********DAG********\n";
	generic_dag_example<user_vertex_1, user_edge_1>();
	/*
	   Example of using a DT graph with user defined vertex and user defined edge 
	 */
	cout << "********DT********\n";
	generic_dt_example<user_vertex_2, user_edge_2>();
	/*
	   Example of using a DT graph with library provided vertex and edge
	 */
	cout << "********DT********\n";
	generic_dt_example<vertex, edge>();

	cout << "********Matrix********\n";
	generic_matrix_example<vertex, edge>();
	return 0;
}

template<typename V, typename E>
void generic_dg_example()
{
	using namespace graph_std_lib;
	/* 
	   Create a DG graph
	 */
	shared_ptr<dg_graph<V, E>> my_graph = make_shared<dg_graph<V, E>>();

	/*
	   Create and add a bunch of vertices to graph
	 */
	auto v0 = create_vertex(my_graph);
	add(my_graph, v0);
	auto v1 = create_vertex(my_graph);
	add(my_graph, v1);
	auto v2 = create_vertex(my_graph);
	add(my_graph, v2);
	auto v3 = create_vertex(my_graph);
	add(my_graph, v3);
	auto v4 = create_vertex(my_graph);
	add(my_graph, v4);
	auto v5 = create_vertex(my_graph);
	add(my_graph, v5);
	auto v6 = create_vertex(my_graph);
	add(my_graph, v6);
	auto v7 = create_vertex(my_graph);
	add(my_graph, v7);
	auto v8 = create_vertex(my_graph);
	add(my_graph, v8);
	auto v9 = create_vertex(my_graph);
	add(my_graph, v9);
	auto v10 = create_vertex(my_graph);
	add(my_graph, v10);

	/*
	   Set vertices value 
	 */
	set_value(my_graph, v0, Value {"A", 1990});
	set_value(my_graph, v1, Value {"B", 38490});
	set_value(my_graph, v2, Value {"C", 77});
	set_value(my_graph, v3, Value {"D", 9999});
	set_value(my_graph, v4, Value {"E", 33});
	set_value(my_graph, v5, Value {"F", 11});
	set_value(my_graph, v6, Value {"G", 68});
	set_value(my_graph, v7, Value {"H", 89});
	set_value(my_graph, v8, Value {"I", 444});
	set_value(my_graph, v9, Value {"J", 1033});
	set_value(my_graph, v10, Value {"K", 99});

	/*
	   Create and add a bunch of edges
	   Then set their values
	 */
	auto e1 = create_edge(my_graph, v0, v1);
	add_edge(my_graph, e1);
	set_value(my_graph, e1, Value {"j", 0});

	auto e2 = create_edge(my_graph, v1, v2);
	add_edge(my_graph, e2);
	set_value(my_graph, e2, Value {"g", 1});

	auto e3 = create_edge(my_graph, v1, v4);
	add_edge(my_graph, e3);
	set_value(my_graph, e3, Value {"I", 10});

	auto e4 = create_edge(my_graph, v3, v4);
	add_edge(my_graph, e4);
	set_value(my_graph, e4, Value {"I", 13});

	auto e5 = create_edge(my_graph, v2, v3);
	add_edge(my_graph, e5);
	set_value(my_graph, e5, Value {"I", 99});

	auto e6 = create_edge(my_graph, v2, v5);;
	add_edge(my_graph, e6);
	set_value(my_graph, e6, Value {"I", 1000});

	auto e7 = create_edge(my_graph, v5, v6);
	add_edge(my_graph, e7);
	set_value(my_graph, e7, Value {"I", 41});

	auto e8 = create_edge(my_graph, v6, v2);
	add_edge(my_graph, e8);
	set_value(my_graph, e8, Value {"I", 37});

	auto e9 = create_edge(my_graph, v6, v7);
	add_edge(my_graph, e9);
	set_value(my_graph, e9, Value {"I", 5});

	auto e10 = create_edge(my_graph, v7, v8);
	add_edge(my_graph, e10);
	set_value(my_graph, e10, Value {"I", 65});

	auto e11 = create_edge(my_graph, v8, v6);
	add_edge(my_graph, e11);
	set_value(my_graph, e11, Value {"I", 65});

	auto e12 = create_edge(my_graph, v2, v0);
	add_edge(my_graph, e12);
	set_value(my_graph, e12, Value {"I", 65});

	auto e13 = create_edge(my_graph, v8, v9);
	add_edge(my_graph, e13);
	set_value(my_graph, e13, Value {"J", 564});

	/*
	   Pretty print the graph
	 */
	pretty_print(my_graph);
	/*
	   Run some of the functions required
	 */
	bool path_e = path_exists(my_graph, v1, v0);
	bool cycle_ex = cycle_exists(my_graph);
	cout << "cycle exists: " << cycle_ex << '\n';
	auto some_v = top(my_graph);
	cout << "top: " << value(my_graph, some_v).first << '\n';
	int num_v = num_vertices(my_graph);
	cout << "Num vertices: " << num_v << '\n';
	int num_e = num_edges(my_graph);
	cout << "Num edges: " << num_e << '\n';
	bool all_r = all_reachable_from_top(my_graph);
	cout << "all reachable: " << all_r << '\n';
	vector<V> vertices_by_value = get_vertices_by_value(my_graph);
	cout << "vertices by value: " << '\n';
	for (auto v : vertices_by_value) {
		shared_ptr<V> t_p = make_shared<V>(v);
		Value val = value(my_graph, t_p);
		cout << val.first << " " << val.second << ", ";
	}	
	cout << '\n';
	vector<E> edges_by_value = get_edges_by_value(my_graph);
	cout << "edges by value: " << '\n';
	for (auto e : edges_by_value) {
		shared_ptr<E> t_p { new E };
		*t_p = e;
		Value val = value(my_graph, t_p);
		cout << val.first << " " << val.second << ", ";
	}
	cout << '\n';
}

template<typename V, typename E>
void generic_dag_example()
{
	using namespace graph_std_lib;
	shared_ptr<dag_graph<V, E>> my_graph = make_shared<dag_graph<V, E>>();

	auto v0 = create_vertex(my_graph);
	add(my_graph, v0);
	auto v1 = create_vertex(my_graph);
	add(my_graph, v1);
	auto v2 = create_vertex(my_graph);
	add(my_graph, v2);
	auto v3 = create_vertex(my_graph);
	add(my_graph, v3);
	auto v4 = create_vertex(my_graph);
	add(my_graph, v4);
	auto v5 = create_vertex(my_graph);
	add(my_graph, v5);
	auto v6 = create_vertex(my_graph);
	add(my_graph, v6);
	auto v7 = create_vertex(my_graph);
	add(my_graph, v7);
	auto v8 = create_vertex(my_graph);
	add(my_graph, v8);
	auto v9 = create_vertex(my_graph);
	add(my_graph, v9);
	auto v10 = create_vertex(my_graph);
	add(my_graph, v10);
	auto v11 = create_vertex(my_graph);
	add(my_graph, v11);
	auto v12 = create_vertex(my_graph);
	add(my_graph, v12);

	set_value(my_graph, v0, Value {"A", 1990});
	set_value(my_graph, v1, Value {"B", 38490});
	set_value(my_graph, v2, Value {"C", 77});
	set_value(my_graph, v3, Value {"D", 9999});
	set_value(my_graph, v4, Value {"E", 33});
	set_value(my_graph, v5, Value {"F", 11});
	set_value(my_graph, v6, Value {"G", 68});
	set_value(my_graph, v7, Value {"H", 89});
	set_value(my_graph, v8, Value {"I", 444});
	set_value(my_graph, v9, Value {"J", 1033});
	set_value(my_graph, v10, Value {"K", 99});
	set_value(my_graph, v11, Value {"L", 99});
	set_value(my_graph, v12, Value {"L", 99});

	remove(my_graph, v11);
	remove(my_graph, v12);

	auto e1 = create_edge(my_graph, v0, v1);
	add_edge(my_graph, e1);
	set_value(my_graph, e1, Value {"j", 0});

	auto e2 = create_edge(my_graph, v1, v2);
	add_edge(my_graph, e2);
	set_value(my_graph, e2, Value {"g", 1});

	auto e3 = create_edge(my_graph, v1, v4);
	add_edge(my_graph, e3);
	set_value(my_graph, e3, Value {"I", 10});

	auto e4 = create_edge(my_graph, v3, v4);
	add_edge(my_graph, e4);
	set_value(my_graph, e4, Value {"I", 13});

	auto e5 = create_edge(my_graph, v2, v3);
	add_edge(my_graph, e5);
	set_value(my_graph, e5, Value {"I", 99});

	auto e6 = create_edge(my_graph, v2, v5);;
	add_edge(my_graph, e6);
	set_value(my_graph, e6, Value {"I", 1000});

	auto e7 = create_edge(my_graph, v5, v6);
	add_edge(my_graph, e7);
	set_value(my_graph, e7, Value {"I", 41});

	auto e8 = create_edge(my_graph, v6, v2);
	add_edge(my_graph, e8);
	set_value(my_graph, e8, Value {"I", 37});

	auto e9 = create_edge(my_graph, v6, v7);
	add_edge(my_graph, e9);
	set_value(my_graph, e9, Value {"I", 5});

	auto e10 = create_edge(my_graph, v7, v8);
	add_edge(my_graph, e10);
	set_value(my_graph, e10, Value {"I", 65});

	auto e11 = create_edge(my_graph, v8, v6);
	add_edge(my_graph, e11);
	set_value(my_graph, e11, Value {"I", 65});

	auto e12 = create_edge(my_graph, v2, v0);
	add_edge(my_graph, e12);
	set_value(my_graph, e12, Value {"I", 65});

	auto e13 = create_edge(my_graph, v8, v9);
	add_edge(my_graph, e13);
	set_value(my_graph, e13, Value {"J", 564});

	pretty_print(my_graph);
	bool path_e = path_exists(my_graph, v1, v0);
	bool cycle_ex = cycle_exists(my_graph);
	cout << "cycle exists: " << cycle_ex << '\n';
	auto some_v = top(my_graph);
	cout << "top: " << value(my_graph, some_v).first << '\n';
	int num_v = num_vertices(my_graph);
	cout << "Num vertices: " << num_v << '\n';
	int num_e = num_edges(my_graph);
	cout << "Num edges: " << num_e << '\n';
	bool all_r = all_reachable_from_top(my_graph);
	cout << "all reachable: " << all_r << '\n';
	vector<V> vertices_by_value = get_vertices_by_value(my_graph);
	cout << "vertices by value: " << '\n';
	for (auto v : vertices_by_value) {
		shared_ptr<V> t_p { new V };
		*t_p = v;
		Value val = value(my_graph, t_p);
		cout << val.first << " " << val.second << ", ";
	}	
	cout << '\n';
	vector<E> edges_by_value = get_edges_by_value(my_graph);
	cout << "edges by value: " << '\n';
	for (auto e : edges_by_value) {
		shared_ptr<E> t_p { new E };
		*t_p = e;
		Value val = value(my_graph, t_p);
		cout << val.first << " " << val.second << ", ";
	}
	cout << '\n';
}

template<typename V, typename E>
void generic_dt_example()
{
	using namespace graph_std_lib;
	shared_ptr<dt_graph<V, E>> my_graph = make_shared<dt_graph<V, E>>();

	auto v0 = create_vertex(my_graph);
	add(my_graph, v0);
	auto v1 = create_vertex(my_graph);
	add(my_graph, v1);
	auto v2 = create_vertex(my_graph);
	add(my_graph, v2);
	auto v3 = create_vertex(my_graph);
	add(my_graph, v3);
	auto v4 = create_vertex(my_graph);
	add(my_graph, v4);
	auto v5 = create_vertex(my_graph);
	add(my_graph, v5);
	auto v6 = create_vertex(my_graph);
	add(my_graph, v6);
	auto v7 = create_vertex(my_graph);
	add(my_graph, v7);
	auto v8 = create_vertex(my_graph);
	add(my_graph, v8);
	auto v9 = create_vertex(my_graph);
	add(my_graph, v9);

	set_value(my_graph, v0, Value {"A", 1990});
	set_value(my_graph, v1, Value {"B", 38490});
	set_value(my_graph, v2, Value {"C", 77});
	set_value(my_graph, v3, Value {"D", 9999});
	set_value(my_graph, v4, Value {"E", 33});
	set_value(my_graph, v5, Value {"F", 11});
	set_value(my_graph, v6, Value {"G", 68});
	set_value(my_graph, v7, Value {"H", 89});
	set_value(my_graph, v8, Value {"I", 444});
	set_value(my_graph, v9, Value {"J", 1033});

	auto e1 = create_edge(my_graph, v0, v1);
	add_edge(my_graph, e1);
	set_value(my_graph, e1, Value {"j", 0});

	auto e2 = create_edge(my_graph, v1, v2);
	add_edge(my_graph, e2);
	set_value(my_graph, e2, Value {"g", 1});

	auto e3 = create_edge(my_graph, v1, v4);
	add_edge(my_graph, e3);
	set_value(my_graph, e3, Value {"I", 10});

	auto e4 = create_edge(my_graph, v3, v4);
	add_edge(my_graph, e4);
	set_value(my_graph, e4, Value {"I", 1033});

	auto e5 = create_edge(my_graph, v2, v3);
	add_edge(my_graph, e5);
	set_value(my_graph, e5, Value {"I", 99});

	auto e6 = create_edge(my_graph, v2, v5);;
	add_edge(my_graph, e6);
	set_value(my_graph, e6, Value {"I", 1000});

	auto e7 = create_edge(my_graph, v5, v6);
	add_edge(my_graph, e7);
	set_value(my_graph, e7, Value {"I", 41});

	auto e8 = create_edge(my_graph, v6, v2);
	add_edge(my_graph, e8);
	set_value(my_graph, e8, Value {"I", 37});

	auto e9 = create_edge(my_graph, v6, v7);
	add_edge(my_graph, e9);
	set_value(my_graph, e9, Value {"I", 5});

	auto e10 = create_edge(my_graph, v7, v8);
	add_edge(my_graph, e10);
	set_value(my_graph, e10, Value {"I", 65});

	auto e11 = create_edge(my_graph, v8, v6);
	add_edge(my_graph, e11);
	set_value(my_graph, e11, Value {"I", 65});

	auto e12 = create_edge(my_graph, v2, v0);
	add_edge(my_graph, e12);
	set_value(my_graph, e12, Value {"I", 65});

	auto e13 = create_edge(my_graph, v8, v9);
	add_edge(my_graph, e13);
	set_value(my_graph, e13, Value {"J", 564});

	pretty_print(my_graph);
	bool path_e = path_exists(my_graph, v1, v0);
	bool cycle_ex = cycle_exists(my_graph);
	cout << "cycle exists: " << cycle_ex << '\n';
	cout << "neighbors for 2: ";
	auto neighbors_1 = neighbors(my_graph, v2);
	for (auto n : neighbors_1) {
		shared_ptr<V> t_p { new V };
		*t_p = n;
		Value v = value(my_graph, t_p);
		cout << v.first << ", ";
	};
	cout << '\n';
	auto some_v = top(my_graph);
	cout << "top: " << value(my_graph, some_v).first << '\n';
	int num_v = num_vertices(my_graph);
	cout << "Num vertices: " << num_v << '\n';
	int num_e = num_edges(my_graph);
	cout << "Num edges: " << num_e << '\n';
	bool all_r = all_reachable_from_top(my_graph);
	cout << "all reachable: " << all_r << '\n';

	vector<V> vertices_by_value = get_vertices_by_value(my_graph);
	cout << "vertices by value: " << '\n';
	for (auto v : vertices_by_value) {
		shared_ptr<V> t_p { new V };
		*t_p = v;
		Value val = value(my_graph, t_p);
		cout << val.first << " " << val.second << ", ";
	}	
	cout << '\n';
	vector<E> edges_by_value = get_edges_by_value(my_graph);
	cout << "edges by value: " << '\n';
	for (auto e : edges_by_value) {
		shared_ptr<E> t_p { new E };
		*t_p = e;
		Value val = value(my_graph, t_p);
		cout << val.first << " " << val.second << ", ";
	}
	cout << '\n';
	cout << "path dfs\n";
	shared_ptr<path_data<V, int>> path_info = find_path_dfs(my_graph, v0, v3);
	vector<V> path = path_info->path_v;
	string s = path_info->to_string();
	int c = path_info->cost;
	cout << s << '\n';
	cout << "cost\n";
	cout << c << '\n';
	cout << "path bfs\n";
	path_info = find_path_bfs(my_graph, v0, v3);
	path = path_info->path_v;
	s = path_info->to_string();
	c = path_info->cost;
	cout << s << '\n';
	cout << "cost\n";
	cout << c << '\n';
	cout << "path ucs\n";
	path_info = find_path_ucs(my_graph, v0, v3);
	path = path_info->path_v;
	s = path_info->to_string();
	c = path_info->cost;
	cout << s << '\n';
	cout << "cost\n";
	cout << c << '\n';
}

template<typename V, typename E>
void generic_matrix_example()
{
	using namespace graph_std_lib;
	shared_ptr<matrix_graph<V, E>> my_graph = make_shared<matrix_graph<V, E>>();

	auto v0 = create_vertex(my_graph);
}

template<typename T>
void pretty_print(T& l)
{
	cout << "Printing graph:" << "\n";
	auto it = l->underlying_data.begin();
	auto it_end = l->underlying_data.end();

	int counter = 0;
	for (; it != it_end; it++) {
		auto neighbors = (*it).neighbors;
		auto edges = (*it).edges;
		cout << "Node " << (*it).vertex_wrapper_data->vertex_data.get_key();
		cout << ",  " << (*it).vertex_wrapper_data->value.first;
		cout << ", " << (*it).vertex_wrapper_data->value.second;
		cout << ": ";
		for (auto n : neighbors) {
			cout << n->value.first;
			cout << "(edge value " << n->value.second << ")";
			cout << ", ";
		}

		cout << "\n";
		counter++;
	}
}
