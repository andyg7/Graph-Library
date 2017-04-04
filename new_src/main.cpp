#include "GraphAL.hpp"
#include <string>
#include <iostream>

int main(){

	GraphAL<string> g1;
	g1.add_vertex("A");
	g1.add_vertex("B");
	g1.print_graph();
	cout << "Hello world!\n";
 
	cout << "Removing vertex A\n";
	g1.remove_vertex("A");
	g1.print_graph();

	cout << "Add vertex A back\n";
	g1.add_vertex("A");
	g1.print_graph();

	cout << "Add an edge from A to B\n";
	g1.add_edge("A", "B");
	g1.print_graph();

	cout << "Is A adjacent to B?\n";
	cout << g1.adjacent("A", "B") << endl;

	cout << "Remove an edge from A to B\n";
	g1.remove_edge("A", "B");
	g1.print_graph();

	cout << "Is A still adjacent to B?\n";
	cout << g1.adjacent("A", "B") << endl;



	// //BUG
	// int a = 10;
	// int b = 20;
	// GraphAL<int> g2;
	// g2.add_vertex(10);
	// g2.add_vertex(20);
	// g2.print_graph();
	// cout << "Hello world!\n";


	return 0;
}