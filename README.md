A C++ Graph Library Using Concepts

What are concepts?

http://www.stroustrup.com/good_concepts.pdf

Graph Terminology

https://en.wikipedia.org/wiki/Graph_(abstract_data_type)

What is this repo?

It's a graph library, built in C++, that makes it easy to create and use graphs. Currently the lib supports the following
graphs: DG (directed graph), DAG (directed acyclic graph), DT (directed tree)

Why use this repo?

- I've tried to make it so that it is really easy for users to use their own vertex/edge data structures. 
- Concepts support overloading, so the right function is picked at compile depending on the actual argument types
- Concepts make debugging easier. Bugs are caught earlier in the compilation process (when the concept predicate is checked)

Architecture

- Created structs for DAG, DG, DT
   - graph_dg, graph_dag, graph_dt
   - each have a member type called 'graph_type'
   - use concepts to differentiate between them based on this member type 'graph_type'
   - i created dummy structs "Graph" "DAG" "DG" "DT" so that the member type 'graph_type' can be set to one of these
- the structs use an adjacency list to hold vertex and edge information
- Created structs for vertex and edge, but user can also provide his/her own implementation as long as their data type is comparable
   - lib provided structs are just called vertex and edge
   - users can provide custom built vertices/edges for their specific needs. e.g. one user may want a vertex to represent a city and have a string field
for city, whereas another user may want the graph to represent jobs to be done and have a field indicating the job number. The vertex data type 
just needs to be comparable, and the edge data structure must have two fields v1, v2 that are the same type as the vertex
- use concept overloading to choose which function to call depending on the graph type
- also implemented 'create_vertex' and 'create_edge' to make it easy for user to create such data structures

Implementation

- the structs for the graphs (e.g. graph_dg, graph_dag, graph_dt) hold an adjacency list of node headers
   - each node header has a vector of vertex wrappers, which hold the 'Value value' field, and points to the vertex data
   - each node header also has a vector of edge wrappers, which hold the 'Value value' field for each edge, and points to the edge data
- require the user to send vertex and edges as shared_ptr
- user can just send graph by reference

Using Lib

- overall idea is for the user to select one of graph_dg, graph_dag, graph_dt, and provide the struct with two template parameters that
specify the vertex and edge types (as mentioned above the lib provides vertex and edge for this but the user can use his/her own data types)
   e.g.  dag_graph<my_vertex_1, my_edge_1> my_graph;
   e.g.  dt_graph<vertex, edge> my_graph;
   e.g.  dg_graph<my_vertex_2, my_edge_2> my_graph;
- concepts are then used to make sure the right function is called depending on the
  graph type (e.g. DT vs DAG vs DG)

Other

- the user can use the create_vertex code iff the data type provided by the user has unique id that is an int, and get be retrieved via get_key(). 
I use a concept to guarantee only graphs whose vertices are of the right type can call this code

Where stuff is

- lib/graph_structs.h contains the library provided data types
to be used
- lib/graph_lib.h the code for the required lib functions
- lib/graph_lib_header.h the header for the code for the required lib functions
- lib/graph_concepts.h the concepts for the assignment
- examples/user_structs.h created some user defined types for the vertex and edges to show that the lib provided data types don't need to be used

Environment
- development:
   - OS: Ubuntu 16.10
   - C++ standard libary used: c++1z
   - Compiler: g++
   - Compiler options: -fconcepts 
- third party code:
   - used a bunch of code from https://github.com/CaseyCarter/cmcstl2
   - all the concepts from this repo are in cmcstl2/

Compiling
- take a look at Makefile in examples/ 
   - to compile: make
   - to clean: make clean
   - to clean dir and recompile: make all
   - to debug/run with valgrind: make valgrind

Examples
- take a look at main.cpp in examples/ or cities_examples/ directory for examples. Just compile and run ./main to see output

