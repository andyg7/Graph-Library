int main(){
	
	// Lets assume my nodes have id a simple string
	Node<string> n1("A");
	Node<string> n2("B");
	Node<string> n3("C");
	Node<string> n4("D");

	// These onject right now exist simply as nodes. Asking what
	// are the neghobors of n1 is nonsensical.

	Graph<string> g1(AM);
	// Lets add the nodes in
	g1.add_node(n1);
	g1.add_node(n2);
	g1.add_node(n3); 

	// Lets add the edges
	g1.add_edge(n1, 3, n2);
	// Lets add an edge differently, the reverse edge to make the edge undirected
	Edge e2(n2, 3, n1);
	g1.add_edge(e2);
	// And another one, this one is directed
	g1.add_edge(n1, 10, n3);

	// This is what we have
	// "C" <= "A" <=> "B"
	// Lets check adjacency
	g1.adjacent(n1, n2); // Should be true
	g1.adjacent(n3, n1); // should say false
	g1.adjacent(n4, n1); // Exception or false? Which one? ******

	// Lets build another overlapping graph on top of these nodes
	// By default this should be adjacency list
	Graph<string> g2();
	g2.add_node(n1);
	g2.add_node(n2);
	g2.add_node(n4);

	// Note, that graph without any edges is still a graph
	g2.add_edge(n1, 1, n2);
	g2.add_edge(n1, 1, n4); 

	// We have "B" <= "A" => "D" here
	/* This is the magic. Same nodes, part of completelty different
	graphs that have different implementation. Only 4 nodes worth of memory.
	What is the problem?
	Lets remove an edge. */
	g2.remove_node(n1);
	/* This is what we should have:
		g1: "C" <= "A" <=> "D"
		g2: "C", "B" 
	   and this is what we have. So all good so far. */

	// Assume n3 = "C" was on the heap, and we delete it
	n3.delete(); 
	// What should be the behaviour then?
	/* Should the graphs stay as 
		g1: "C" <= "A" <=> "D"
		g2: "C", "B" 
	OR should the library react to this and delete the node from
	all the graphs that have that node in them?
		g1: "A" <=> "D"
		g2: "B" 
	OR should we recongnize that one is trying to delete a node that
	is part of a graph and throw a runtime exception? */

	/* PUNCHLINE: removal of a node from a graph is very clear and 
	we know the expected behaviour there. But what about the deletion
	of the node? */

	/* Somya and I think we we should go with removal from all graphs
		when the destructor of the node is invoked. There are
		few way to do this, but they all require extra book keeping. 
		1) Every graph receives unique id, node remembers them
		2) Node remembers pointers to graphs
		The centralized way to do this seems to be much worse.*/

	

}