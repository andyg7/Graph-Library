#include "GraphAL.hpp"
#include <string>
#include <iostream>

int main(){

	GraphAL<string, int> g1;
	g1.add_vertex("A");
	g1.add_vertex("B");
	g1.print_graph();
	cout << "Hello world!\n";

	cout << "Add C through a variable\n";
	string c = "C";
	g1.add_vertex("C");
	g1.print_graph();
 
	cout << "Removing vertex A and C\n";
	g1.remove_vertex("A");
	g1.remove_vertex("C");
	g1.print_graph();

	cout << "Add them in inverse order, represenation shoud be\n";
	cout << "the same since stack of unique ids\n";
	g1.add_vertex("C");
	g1.add_vertex("A");

	g1.print_graph();

	cout << "Add vertex A again, should catch an exception\n";
	
	try{
		g1.add_vertex("A");
		g1.print_graph();
	}catch(...){
		cout << "exception caught\n";
	}

	cout << "Add an edge from A to B\n";
	g1.add_edge("A", 1, "B");
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