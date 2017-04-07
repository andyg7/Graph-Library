#include "GraphAL.hpp"
#include "Graph.hpp"
#include <string>
#include <iostream>

#include "graph_concepts.h"


// class PrivateMF{
// private:
// 	int priv;
// public:
// 	PrivateMF(int a){ priv = a;}

// };

int main(){

	// auto x = PrivateMF(3);
	// x.priv = 17;


	//Create the vertices
	auto n1 = create_node<string, int>("A", nullptr);
	auto n2 = create_node<string, int>("B", nullptr);
	auto n3 = create_node<string, int>("C", nullptr);
	auto n4 = create_node<string, int>("D", nullptr);

	GraphAL<string, int, int> g1;
	g1.add_node(n1);
	g1.add_node(n2);
	g1.add_node(n3);
	g1.add_node(n4);
	g1.print_graph();

	cout << "add edges A-B and A-C\n";
	g1.add_edge(n1, 1, n2);
	g1.add_edge(n1, 1, n3);
	g1.print_graph();

	cout << "Remove C from the graph, should also remove the edge\n";
	g1.remove_node(n3);
	g1.print_graph();

	cout << "Remove all vertices, and add them back\n";
	g1.remove_node(n1);
	g1.remove_node(n4);
	g1.remove_node(n2);
	g1.print_graph();
	cout << "And add back...\n";
	g1.add_node(n1);
	g1.add_node(n2);
	g1.add_node(n3);
	g1.add_node(n4);
	g1.print_graph();

	cout << "Add few edges\n";
	g1.add_edge(n1, 1, n2);
	g1.add_edge(n1, 1, n3);
	g1.add_edge(n4, 1, n3);
	g1.add_edge(n3, 1, n4);
	g1.print_graph();

	cout << "Remove few edges\n";
	g1.remove_edge(n1, n2);
	g1.remove_edge(n4, n3);
	g1.print_graph();

	cout << "Add an Edge if you know what i mean\n";
	auto e1 = create_edge<string, int, int>(n2, 7, n3);
	g1.add_edge(e1);
	g1.print_graph();

	cout << "Is B adjacent to C?\n";
	cout << g1.adjacent(n2, n3) << endl;
	cout << "Is C adjacent to B?\n";
	cout << g1.adjacent(n3, n2) << endl;

	cout << "Add more edges and see the neighbours\n";
	g1.add_edge(n2, 1, n1);
	g1.add_edge(n2, 1, n4);
	g1.print_graph();

	auto v = g1.neighbours(n2);
	print_nodes<string, int>(v);

	return 0;
}