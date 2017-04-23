#include <string>
#include <iostream>

#include "GraphAL.hpp"
#include "Graph.hpp"
#include "algo.h"
#include "utility.hpp"
#include "path_algorithms.h"

#include "GraphAM.hpp"


int main(){

	/* Create few nodes. nullptr is the data pointer */
	auto n1 = create_node<string, int>("A", nullptr);
	auto n2 = create_node<string, int>("B", nullptr);
	auto n3 = create_node<string, int>("C", nullptr);
	auto n4 = create_node<string, int>("D", nullptr);
	auto extra = create_node<string, int>("Z", nullptr);

	cout << "Testing the matrix implementation\n";
	cout << "Add 4 nodes and few edges\n";
	auto gAM1 = create_graph<string, int, int, GraphAM>();
	add_node(gAM1, n1);
	add_node(gAM1, n2);
	add_node(gAM1, n3);
	add_node(gAM1, n4);

	add_edge(gAM1, n1, 2, n2);
	add_edge(gAM1, n2, 10, n1);
	add_edge(gAM1, n3, 1, n1);

	gAM1->print_graph();
	cout << endl;

	cout << "Add another node, and notice how the underlying matrix expands\n";
	add_node(gAM1, extra);
	gAM1->print_graph();
	cout << endl;

	cout << "Remove an edge\n";
	remove_edge(gAM1, n2, n1);
	gAM1->print_graph();
	cout << endl;

	cout << "Lets add bunch of edges and then delete a node\n";
	add_edge(gAM1, n1, 5, n3);
	add_edge(gAM1, n2, 5, n3);
	add_edge(gAM1, n4, 5, n3);

	add_edge(gAM1, n3, 7, n2);
	add_edge(gAM1, n3, 7, n4);
	gAM1->print_graph();
	cout << endl;

	cout << "Now delete the node 3\n";
	remove_node(gAM1, n3);
	gAM1->print_graph();
	cout << endl;

	// cout << "Testing the adjacency list implementation\n";
	// // Create a graph
	// auto g1 = create_graph<string, int, int, GraphAL>();
	
	// // Add nodes to the graph 
	// add_node(g1, n1);
	// add_node(g1, n2);
	// add_node(g1, n3);
	// add_node(g1, n4);
	// g1->print_graph();

	// // Add edges
	// cout << "add edges A-B and B-C\n";
	// add_edge(g1, n1, 10, n4);
	// add_edge(g1, n1, 1, n2);
	// add_edge(g1, n2, 1, n3);
	// add_edge(g1, n3, 1, n4);
	// find_path_dfs(g1, n1, n4);
	// find_path_bfs(g1, n1, n4);
	// find_path_ucs(g1, n1, n4);

	// g1->print_graph();

	// // Remove a node
	// cout << "Remove C from the graph, should also remove the edge\n";
	// remove_node(g1, n3);
	// g1->print_graph();

	// cout << "Remove all vertices, and add them back\n";
	// remove_node(g1, n1);
	// remove_node(g1, n4);
	// remove_node(g1, n2);
	// g1->print_graph();
	// cout << "And add back...\n";
	// add_node(g1, n1);
	// add_node(g1, n2);
	// add_node(g1, n3);
	// add_node(g1, n4);
	// g1->print_graph();

	// // Add a edges
	// cout << "Add few edges\n";
	// add_edge(g1, n1, 1, n2);
	// add_edge(g1, n1, 1, n3);
	// add_edge(g1, n4, 1, n3);
	// add_edge(g1, n3, 1, n4);
	// g1->print_graph();

	// // Remove edges
	// cout << "Remove few edges\n";
	// remove_edge(g1, n1, n2);
	// remove_edge(g1, n4, n3);
	// g1->print_graph();

	// // Create an Edge, pass that object in instead
	// cout << "Add an Edge if you know what i mean\n";
	// auto e1 = create_edge<string, int, int>(n2, 7, n3);
	// add_edge(g1, e1);
	// g1->print_graph();

	// cout << "Is B adjacent to C?\n";
	// cout << adjacent(g1, n2, n3) << endl;
	// cout << "Is C adjacent to B?\n";
	// cout << adjacent(g1, n3, n2) << endl;

	// cout << "Add more edges and see the neighbours\n";
	// add_edge(g1, n2, 1, n1);
	// add_edge(g1, n2, 1, n4);
	// g1->print_graph();

	// // Get neighbours
	// cout << "Who are the neighbours of B?\n";
	// auto v = neighbours(g1, n2);
	// print_nodes(v);

	// // Lets see which nodes participate in g1
	// cout << "Who are the participants of g1?\n";
	// auto pariticipants = get_nodes(g1);
	// print_nodes(pariticipants);

	// // Lets get the edge list
	// cout << "What are the edges os g1?\n";
	// auto edges = get_edges(g1);
	// print_edges(edges);

	// // Set the data pointer of a node, access data, get id
	// int a = 30;
	// n1->set_data(&a);
	// a = 15;
	// assert(a == *n1->get_data());
	// cout << "Data assosciated with A?\n";
	// cout << n1->get_id() << ", data " << *n1->get_data() << endl;

	// // Given an edge or a node, lets check if it is in the graph
	// cout << "Is D in the graph?\n";
	// cout << has_node(g1, n4) << endl;
	// cout << "Remove it. Is D in graph now?\n";
	// remove_node(g1, n4);
	// cout << has_node(g1, n4) << endl;
	// cout << "Lets check if there is an edge (A, 1, C)?\n";
	// auto e2 = create_edge<string, int, int>(n1, 1, n3);
	// cout << has_edge(g1, e2) << endl;
	// cout << "Maybe (C, 1, D)? Remember we removed D\n";
	// auto e3 = create_edge<string, int, int>(n3, 1, n4);
	// cout << has_edge(g1, e3) << endl;
	// g1->print_graph();

	// // Lets get edges of B and its edges back
	// cout << "Edges of B are?\n";
	// auto edges_of = edges_of_node(g1, n2);
	// print_edges(edges_of);

	// // Run DFS
	// cout << "Print DFS rooted at A\n";
	// auto dfsn1 = dfs(g1, n1);
	// dfsn1->print_graph();

	// cout << "Print DFS rooted at B\n";
	// auto dfsn2 = dfs(g1, n2);
	// dfsn2->print_graph();

	// cout << "Print DFS rooted at C\n";
	// auto dfsn3 = dfs(g1, n3);
	// dfsn2->print_graph();

	// // Build a graph from multiple edges and nodes (make sure to add nodes first`)
	// cout << "Lets build a graph from edges and nodes of g1\n";
	// auto node_v = get_nodes(g1);
	// auto edges_v = get_edges(g1);
	// auto g2 = create_graph<string, int, int, GraphAL>();
	// add_nodes(g2, node_v);
	// add_edges(g2, edges_v);
	// g2->print_graph();

	// // Lets test the undirectification
	// cout << "Lets get the undirected version of a directed graph g2\n";
	// auto ug2 = make_undirected_from<string, int, int, GraphAL>(g2, average_combine<string, int, int>);
	// ug2->print_graph();

	// cout << "Lets try a more complicated graph. Here is one:\n";
	// auto g3 = create_graph<string, int, int, GraphAL>();
	// add_node(g3, n1);
	// add_node(g3, n2);
	// add_node(g3, n3);
	// add_node(g3, n4);

	// add_edge(g3, n1, 1, n2);
	// add_edge(g3, n2, 8, n1);
	// add_edge(g3, n2, 5, n3);
	// g3->print_graph();

	// cout << "Now lets see how it can be made undirected by adding edges according to some rule\n";
	// auto ug3 = make_undirected_from<string, int, int, GraphAL>(g3, average_combine<string, int, int>);
	// ug3->print_graph();

	// auto n5 = create_node<string, int>("D", nullptr);
	// cout << (n5 == n4) << endl;
	// cout << (n5 == n3) << endl;

	// cout << (n5 != n4) << endl;
	// cout << (n5 != n3) << endl;

	// cout << "Now on edges\n";
	// auto e5 = create_edge<string, int, int>(n2, 5, n4);
	// auto e6 = create_edge<string, int, int>(n2, 5, n5);
	// auto e7 = create_edge<string, int, int>(n2, 2, n5);
	// auto e8 = create_edge<string, int, int>(n1, 2, n5);

	// cout << (e5 == e6) << endl;
	// cout << (e5 == e7) << endl;
	// cout << (e5 == e8) << endl;
	// cout << (e5 != e8) << endl;



	return 0;
}
