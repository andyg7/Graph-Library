#include "GraphAL.hpp"
#include <string>
#include <iostream>

int main(){

	Node<string, int> n1 = Node<string, int>("A", nullptr);
	Node<string, int> n2 = Node<string, int>("B", nullptr);
	Node<string, int> n3 = Node<string, int>("C", nullptr);

	Node<string, int>* n4_p = new Node<string, int>("D", nullptr);




	GraphAL<string, int, int> g1;
	g1.add_vertex(n1);
	g1.add_vertex(n2);
	g1.add_vertex(n3);
	g1.add_vertex(*n4_p);

	g1.print_graph();

	cout << "add edges A-B and A-C\n";
	g1.add_edge(n1, 1, n2);
	g1.add_edge(n1, 1, n3);
	g1.print_graph();

	cout << "Remove C from the graph, should also remove the edge\n";
	g1.remove_vertex(n3);
	g1.print_graph();

	cout << "Remove all vertices, and add them back\n";
	g1.remove_vertex(n1);
	g1.remove_vertex(*n4_p);
	g1.remove_vertex(n2);
	g1.print_graph();
	cout << "And add back...\n";
	g1.add_vertex(n1);
	g1.add_vertex(n2);
	g1.add_vertex(n3);
	g1.add_vertex(*n4_p);
	g1.print_graph();


	// string a = "A";
	// string b = "B";
	// string c = "C";

	// GraphAL<string, int> g1;
	// g1.add_vertex(a);
	// g1.add_vertex(b);
	// g1.print_graph();
	// cout << "Hello world!\n";

	// cout << "Add C through a variable\n";
	// g1.add_vertex(c);
	// g1.print_graph();
 
	// cout << "Removing vertex A and C\n";
	// g1.remove_vertex(a);
	// g1.remove_vertex(c);
	// g1.print_graph();

	// cout << "Add them in inverse order, represenation shoud be\n";
	// cout << "the same since stack of unique ids\n";
	// g1.add_vertex(c);
	// g1.add_vertex(a);

	// g1.print_graph();

	// cout << "Add vertex A again, should catch an exception\n";
	
	// try{
	// 	g1.add_vertex(a);
	// 	g1.print_graph();
	// }catch(...){
	// 	cout << "exception caught\n";
	// }

	// cout << "Add an edge from A to B\n";
	// g1.add_edge(a, 1, b);
	// g1.print_graph();

	// cout << "Is A adjacent to B?\n";
	// cout << g1.adjacent(a, b) << endl;

	// cout << "Remove an edge from A to B\n";
	// g1.remove_edge(a, b);
	// g1.print_graph();

	// cout << "Is A still adjacent to B?\n";
	// cout << g1.adjacent(a, b) << endl;

	// cout << "Add edges A-B, A-C\n";
	// g1.add_edge(a, 1, b);
	// g1.add_edge(a, 1, c);
	// g1.print_graph();

	// cout << "Lets remove B and see if edge disappears\n";
	// g1.remove_vertex(b);
	// g1.print_graph();


	// char a1 = 'A';
	// char b1 = 'B';
	// GraphAL<char, int> g2;
	// g2.add_vertex(a1);
	// g2.add_vertex(b1);
	// g2.print_graph();
	// cout << "Hello world!\n";


	// int n1 = 1;
	// int n2 = 2;
	// int n3 = 3;

	// GraphAL<int, int> g3;
	// g3.add_vertex(n1);
	// g3.add_vertex(n2);
	// g3.add_vertex(n3);

	// g3.add_edge(n1, 1, n2);
	// g3.add_edge(n1, 1, n3);
	// g3.add_edge(n2, 1, n1);

	// g3.print_graph();

	// // Uncoment the code below to expose the problem
	// cout << "graph created using constants\n";
	// GraphAL<int, int> g4;
	// g4.add_vertex(1);
	// g4.add_vertex(2);
	// g4.add_vertex(3);
	// g4.print_graph();






	return 0;
}