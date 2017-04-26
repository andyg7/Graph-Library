# A C++ Graph Library Using Concepts

## What is this repo?

It's a graph library, built in C++, that makes it easy to create and use graphs. Currently the library supports the following
graphs: DG (directed graph), DAG (directed acyclic graph), DT (directed tree), Matrix(undirected). The idea is that users define their own vertex and edge data
types, and then the library handles everything else under the hood.

Conceptually, a graph is made up of a bunch of vertices and edges. At a minimum there must be some way to distinguish between vertices, distinguish between edges, and
define edges as made up of two vertices. Nontheless, users often want to embed extra information in these ADTs. For example, a user may want a graph representing
cities and the highways between them. The user may have a City class; cities must of course have some unique id (e.g. city name), but they may also have extra information such as population, GDP,
etc. The same goes for edges; maybe a Road class is used, and the class also has miles, age of road etc. This library makes it easy for users to provide their own
ADTs, and immediately start creating graphs, and run algoritms on them. 


## What are C++ concepts?

http://www.stroustrup.com/good_concepts.pdf

They're essentially compile time predicates. That is, they are requirements on the types that are passed into functions. If an argument doesn't satisfy the concept,
the compiler will immediately report an error. This makes debugging much easier when using templates. Without concepts, debugging can be very tricky when
using templates, as it's often late in the compilation process that the compiler realizes a type is no good. As a result error messages can be extremely
long, making dubugging tricky. In terms of this library, the idea is that user defined vertices and edges must
satisfy certain properties; concepts are used to enforce these.


## Graph Terminology

https://en.wikipedia.org/wiki/Graph_(abstract_data_type)


## Why use this repo?

- I've tried to make it so that it is really easy for users to use their own vertex/edge data structures so they can  start using graphs right away and run
  algorithms on them. 
- Concepts support overloading, so the right function is selected at compile depending on the actual argument types. Thus, there is no runtime overhead in
  terms of looking up which function to call.
- Concepts make debugging easier. Bugs are caught earlier in the compilation process (when the concept predicate is checked). Often when programming with
  templates errors are caught late in the compilation process, resulting in hard to read error messages. Concepts will make sure the compiler knows right away
  an argument's type is no good

## Using the library

- The most important thing is for the user to define his/her vertex and edge data types. The only requirements are that the vertex/edge are comparable (aka must
  implement operator==) and hashable (aka implement struct hash<vertex> ...).
- Then the user should select one of graph_dg, graph_dag, graph_dt, matrix_graph and provide the struct with two template parameters that
specify the vertex and edge types (as mentioned above the lib provides vertex and edge for this but the user can use his/her own data types)
   e.g.  dag_graph<my_vertex_1, my_edge_1> my_graph;
   e.g.  dt_graph<vertex, edge> my_graph;
   e.g.  dg_graph<my_vertex_2, my_edge_2> my_graph;
- At this point any/all of the functions can be used. Note that all functions require pointers as inputs (more specifically shared_ptrs); this is to avoid
  the cost of copying large graphs/vertices/edges
   - see examples/ directory for some examples
- Note that the same function name is used for all graph types, vertex types and edge types. This is another benefit of concepts; that is, concepts are used
  to make sure the right function is called using overloading

### Other

- The user can use the create_vertex code iff the data type provided by the user has unique id that is an int, and get be retrieved via get_key(). 
I use a concept to guarantee only graphs whose vertices are of the right type can call this code. This is a nice helper function that can be used to create
lots of user defined vertices; again though the unique id for the user defined vertex must be an int retrievable from get_key()

### Path algorithms
- Bfs, dfs, ucs and ast implementations exist for all types of graph
- The code that runs the algos is in node_expander_path_algorithms.h
- Whats nice is that there is one and only one path finding algorithm in node_expander_path_algorithms.h. The inputs are simply the goal state, the frontier
  type (e.g. stack, queue, heap), and the operations that work on the frontier. This way bfs, dfs, ucs and ast can all work with the same code
- In fact, as the code in expander_examples/ directory show, you dont even need a graph to use the path finding algorithms. As long as you send the
  algorithm an initial state, goal state and frontier (plus it's operations), that adhere to a few properties (explained below) you are good to go
   - the states must have an expand function that returns a vector of successor states
   - the state must have a cost field
   - take a look at https://en.wikipedia.org/wiki/Pathfinding for more reference

## Implementation

- Created structs for DAG, DG, DT, Matrix
   - dg_graph, dag_graph, dt_graph, matrix_graph
   - each have a member type called 'graph_type'
   - use concepts to differentiate between them based on this member type 'graph_type'
   - created dummy structs "Graph" "DAG" "DG" "DT" "Matrix_graph" so that the member type 'graph_type' can be set to one of these
- The AL structs use an vector to hold vertex and edge information
   - Created structs for vertex and edge, but user can also provide his/her own implementation as long as their data type is comparable
   - lib provided structs are just called vertex and edge
   - users can provide custom built vertices/edges for their specific needs as mentioned previously
- For the matrix implementation, i map a vertex to a unique id. This unique id is used to index the matrix. Note, the unique is hidden from the user; thus, the
  user's vertex does not need to maintain it's own index. This was a design design I made to make it super easy for the user to get going right away.
  Nonetheless, there is some overhead in storing this mapping.
- Use concept overloading to choose which function to call depending on the graph type
- Reach out to me with any implementation questions

## Location of Code
- in src/ directory
- adjacency_list_graph_lib.h contains all adjacency list code
- matrix_graph_lib.h contains all matrix code
- graph_structs.h contains the data structures the lib uses

## Environment
- Development:
   - OS: Ubuntu 16.10
   - C++ standard libary used: c++1z
   - Compiler: g++
   - Compiler options: -fconcepts 
- Third party code:
   - used a bunch of code from https://github.com/CaseyCarter/cmcstl2
   - all the concepts from this repo are in cmcstl2/

## Compiling
- Take a look at Makefile in examples/ 
   - to compile: make
   - to clean: make clean
   - to clean dir and recompile: make all
   - to debug/run with valgrind: make valgrind

## Important Notes

- There appears to be a GCC bug when it comes to compiling concepts. There are times where private member variables/functions can suddenly be accessed from
  outside a class/struct (very weird). See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78715 for this bug report


## Examples
- Take a look at main.cpp in examples/, cities_examples/ expander_examples/ directory for examples. The makefiles should be set up so you can simply run
  'make', and execute the binary (./main)

