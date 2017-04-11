#include <string>
#include <iostream>

#include "GraphAL.hpp"
#include "Graph.hpp"
#include "algo.h"
#include "utility.hpp"


int main(){

	// Create few nodes. nullptr is the data pointer
	auto n1 = create_node<string, int>("A", nullptr);
	auto n2 = create_node<string, int>("B", nullptr);
	auto n3 = create_node<string, int>("C", nullptr);
	auto n4 = create_node<string, int>("D", nullptr);

	// Create a graph
	auto g1 = create_graph<string, int, int, GraphAL>();
	
	// Add nodes to the graph 
	g1->add_node(n1);
	g1->add_node(n2);
	g1->add_node(n3);
	g1->add_node(n4);
	g1->print_graph();

	// Add edges
	cout << "add edges A-B and A-C\n";
	g1->add_edge(n1, 1, n2);
	g1->add_edge(n1, 1, n3);
	g1->print_graph();

	// Remove a node
	cout << "Remove C from the graph, should also remove the edge\n";
	g1->remove_node(n3);
	g1->print_graph();

	cout << "Remove all vertices, and add them back\n";
	g1->remove_node(n1);
	g1->remove_node(n4);
	g1->remove_node(n2);
	g1->print_graph();
	cout << "And add back...\n";
	g1->add_node(n1);
	g1->add_node(n2);
	g1->add_node(n3);
	g1->add_node(n4);
	g1->print_graph();

	// Add a edges
	cout << "Add few edges\n";
	g1->add_edge(n1, 1, n2);
	g1->add_edge(n1, 1, n3);
	g1->add_edge(n4, 1, n3);
	g1->add_edge(n3, 1, n4);
	g1->print_graph();

	// Remove edges
	cout << "Remove few edges\n";
	g1->remove_edge(n1, n2);
	g1->remove_edge(n4, n3);
	g1->print_graph();

	// Create an Edge, pass that object in instead
	cout << "Add an Edge if you know what i mean\n";
	auto e1 = create_edge<string, int, int>(n2, 7, n3);
	g1->add_edge(e1);
	g1->print_graph();

	cout << "Is B adjacent to C?\n";
	cout << g1->adjacent(n2, n3) << endl;
	cout << "Is C adjacent to B?\n";
	cout << g1->adjacent(n3, n2) << endl;

	cout << "Add more edges and see the neighbours\n";
	g1->add_edge(n2, 1, n1);
	g1->add_edge(n2, 1, n4);
	g1->print_graph();

	// Get neighbours
	cout << "Who are the neighbours of B?\n";
	auto v = g1->neighbours(n2);
	print_nodes<string, int>(v);

	// Lets see which nodes participate in g1
	cout << "Who are the participants of g1?\n";
	auto pariticipants = g1->get_nodes();
	print_nodes(pariticipants);

	// Lets get the edge list
	cout << "What are the edges os g1?\n";
	auto edges = g1->get_edges();
	print_edges(edges);

	// Set the data pointer of a node, access data, get id
	int a = 30;
	n1->set_data(&a);
	a = 15;
	assert(a == *n1->get_data());
	cout << "Data assosciated with A?\n";
	cout << n1->get_id() << ", data " << *n1->get_data() << endl;

	// Given an edge or a node, lets check if it is in the graph
	cout << "Is D in the graph?\n";
	cout << g1->has_node(n4) << endl;
	cout << "Remove it. Is D in graph now?\n";
	g1->remove_node(n4);
	cout << g1->has_node(n4) << endl;
	cout << "Lets check if there is an edge (A, 1, C)?\n";
	auto e2 = create_edge<string, int, int>(n1, 1, n3);
	cout << g1->has_edge(e2) << endl;
	cout << "Maybe (C, 1, D)? Remember we removed D\n";
	auto e3 = create_edge<string, int, int>(n3, 1, n4);
	cout << g1->has_edge(e3) << endl;
	g1->print_graph();

	// Lets get edges of B and its edges back
	cout << "Edges of B are?\n";
	auto edges_of = g1->edges_of_node(n2);
	print_edges(edges_of);

	// Run DFS
	cout << "Print DFS rooted at A\n";
	auto dfsn1 = dfs(g1, n1);
	dfsn1->print_graph();

	cout << "Print DFS rooted at B\n";
	auto dfsn2 = dfs(g1, n2);
	dfsn2->print_graph();

	cout << "Print DFS rooted at C\n";
	auto dfsn3 = dfs(g1, n3);
	dfsn2->print_graph();

	// Build a graph from multiple edges and nodes (make sure to add nodes first`)
	cout << "Lets build a graph from edges and nodes of g1\n";
	auto node_v = g1->get_nodes();
	auto edges_v = g1->get_edges();
	auto g2 = create_graph<string, int, int, GraphAL>();
	add_nodes(node_v, g2);
	add_edges(edges_v, g2);
	g2->print_graph();

	// Lets test the undirectification
	cout << "Lets get the undirected version of a directed graph g2\n";
	auto ug2 = make_undirected_from<string, int, int, GraphAL>(g2, average_combine<string, int, int>);
	ug2->print_graph();

	cout << "Lets try a more complicated graph. Here is one:\n";
	auto g3 = create_graph<string, int, int, GraphAL>();
	g3->add_node(n1);
	g3->add_node(n2);
	g3->add_node(n3);
	g3->add_node(n4);

	g3->add_edge(n1, 1, n2);
	g3->add_edge(n2, 8, n1);
	g3->add_edge(n2, 5, n3);
	g3->print_graph();

	cout << "Now lets see how it can be made undirected by adding edges according to some rule\n";
	auto ug3 = make_undirected_from<string, int, int, GraphAL>(g3, average_combine<string, int, int>);
	ug3->print_graph();






	return 0;
}