#include <iostream>
#include <cassert>
#include <vector>
#include "user_structs.h"
#include "../src/graph_lib.h"

using namespace std;
template<typename V, typename E>
int test_dg();
template<typename V, typename E>
int test_dag();
template<typename V, typename E>
int test_dt();

string failed_test_string = "FAILED TEST";

template<typename V, typename E>
int test_matrix();

int main(int argc, char *argv[])
{
	assert(__cpp_concepts >= 201500);
	assert(__cplusplus >= 201500);

	using namespace graph_std_lib;
	cout << "********Testing DG********\n";
	int dg_passed = test_dg<user_vertex_1, user_edge_1>();
	if (dg_passed == true) {
		cout << "Passed all DG tests!\n";
	} else {
		cout << "Failed some DG test!\n";
	}
	cout << "********Testing DAG********\n";
	int dag_passed = test_dag<user_vertex_1, user_edge_1>();
	if (dag_passed == true) {
		cout << "Passed all DAG tests!\n";
	} else {
		cout << "Failed some DAG test!\n";
	}
	cout << "********Testing DT********\n";
	int dt_passed = test_dt<user_vertex_2, user_edge_2>();
	if (dt_passed == true) {
		cout << "Passed all DT tests!\n";
	} else {
		cout << "Failed some DT test!\n";
	}
	cout << "********Testing Matrix********\n";
	int matrix_passed = test_matrix<vertex, edge>();
	if (matrix_passed == true) {
		cout << "Passed all Matrix tests!\n";
	} else {
		cout << "Failed some Matrix test!\n";
	}
	return 0;
}


template<typename V, typename E>
int test_dg()
{
	using namespace graph_std_lib;
	shared_ptr<dg_graph<V, E>> my_graph = make_shared<dg_graph<V, E>>();

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

	bool path_e = path_exists(my_graph, v1, v0);
	bool cycle_ex = cycle_exists(my_graph);
	if (cycle_ex == false) {
		cout << failed_test_string << '\n';
		return 0;
	}
	int num_v = num_vertices(my_graph);
	if (num_v != 11) {
		cout << failed_test_string << '\n';
		return 0;
	}
	int num_e = num_edges(my_graph);
	if (num_e != 13) {
		cout << failed_test_string << '\n';
		return 0;
	}
	bool all_r = all_reachable_from_top(my_graph);
	if (all_r != 0) {
		cout << failed_test_string << '\n';
		return 0;
	}
	return 1;
}

template<typename V, typename E>
int test_dag()
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

	bool path_e = path_exists(my_graph, v1, v0);
	bool cycle_ex = cycle_exists(my_graph);
	if (cycle_ex == true) {
		cout << failed_test_string << '\n';
		return 0;
	}

	int num_v = num_vertices(my_graph);
	if (num_v != 11) {
		cout << failed_test_string << '\n';
		return 0;
	}
	int num_e = num_edges(my_graph);
	if (num_e != 10) {
		cout << failed_test_string << '\n';
		return 0;
	}
	bool all_r = all_reachable_from_top(my_graph);
	if (all_r != 0) {
		cout << failed_test_string << '\n';
		return 0;
	}
	return 1;
}

template<typename V, typename E>
int test_dt()
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

	bool path_e = path_exists(my_graph, v1, v0);
	bool cycle_ex = cycle_exists(my_graph);
	if (cycle_ex == true) {
		cout << failed_test_string << '\n';
		return 0;
	}
	shared_ptr<path_data<V, int>> path_info = find_path_dfs(my_graph, v0, v3);
	vector<V> path = path_info->path_v;
	if (path.size() == 0) {
		cout << failed_test_string << '\n';
		return 0;
	}
	string s = path_info->to_string();
	int c = path_info->cost;
	if (c != 3) {
		cout << failed_test_string << '\n';
		return 0;
	}
	path_info = find_path_bfs(my_graph, v0, v3);
	path = path_info->path_v;
	s = path_info->to_string();
	c = path_info->cost;
	if (c != 3) {
		cout << failed_test_string << '\n';
		return 0;
	}
	path_info = find_path_ucs(my_graph, v0, v3);
	path = path_info->path_v;
	c = path_info->cost;
	if (c != 3) {
		cout << failed_test_string << '\n';
		return 0;
	}
	return 1;
}

template<typename V, typename E>
int test_matrix()
{
	using namespace graph_std_lib;
	/* 
	   Create a DG graph
	 */
	shared_ptr<matrix_graph<V, E>> my_graph = make_shared<matrix_graph<V, E>>(20);

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
	auto v11 = create_vertex(my_graph);
	add(my_graph, v11);
	auto v12 = create_vertex(my_graph);
	add(my_graph, v12);
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

	remove(my_graph, v11);
	remove(my_graph, v12);
	int new_num =  num_vertices(my_graph); 
	if (new_num != 11) {
		cout << failed_test_string << '\n';
		return 0;
	}

	bool path_e = path_exists(my_graph, v1, v0);
	if (path_e != 1) {
		cout << failed_test_string << '\n';
		return 0;
	}
	bool cycle_ex = cycle_exists(my_graph);
	if (cycle_ex == 0) {
		cout << failed_test_string << '\n';
		return 0;
	}
	if (adjacent(my_graph, v0, v1) != 1) {
		cout << failed_test_string << '\n';
		return 0;
	}
	if (adjacent(my_graph, v0, v3) != 0) {
		cout << failed_test_string << '\n';
		return 0;
	}
	shared_ptr<path_data<V, int>> path_info = find_path_dfs(my_graph, v0, v3);
	vector<V> path = path_info->path_v;
	if (path.size() != 4) {
		cout << failed_test_string << '\n';
		return 0;
	}
	int c = path_info->cost;
	if (c != 3) {
		cout << failed_test_string << '\n';
		return 0;
	}
	path_info = find_path_bfs(my_graph, v0, v3);
	path = path_info->path_v;
	c = path_info->cost;
	if (c != 3) {
		cout << failed_test_string << '\n';
		return 0;
	}
	path_info = find_path_ucs(my_graph, v0, v3);
	path = path_info->path_v;
	c = path_info->cost;if (c != 3) {
		cout << failed_test_string << '\n';
		return 0;
	}
}
