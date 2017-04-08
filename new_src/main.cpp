#include "GraphAL.hpp"
#include "Graph.hpp"
#include <string>
#include <iostream>

#include "graph_concepts.h"


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


	// Deletions
	delete_graph(g1);

	delete_node(n1);
	delete_node(n2);
	delete_node(n3);
	delete_node(n4);


	cout << "All good!\n";

	return 0;
}