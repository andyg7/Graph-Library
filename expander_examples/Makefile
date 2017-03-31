CC=g++
FLAGS= -fconcepts -std=c++1z -g -O2
CURR_DIR= $(shell pwd)
GRAPH_LIB_DIR=/home/ubuntu/safe_dir/Graph-Library/src
THIRD_PARTY_CODE= $(CURR_DIR)/../src/cmcstl2/include
INCLUDE=-I$(THIRD_PARTY_CODE) -I$(GRAPH_LIB_DIR)
EXE=main
DEBUG_EXE=debug
VALGRIND_TARGET=valgrind
OBJS=main.o user_structs.cpp
HEADERS=$(GRAPH_LIB_DIR)/graph_lib.h $(GRAPH_LIB_DIR)/path_algorithms.h $(GRAPH_LIB_DIR)/graph_concepts.h $(GRAPH_LIB_DIR)/graph_structs.h user_structs.h $(GRAPH_LIB_DIR)/function_objs.h $(GRAPH_LIB_DIR)/node_expander_path_algorithms.h $(GRAPH_LIB_DIR)/path_algorithms_structs.h

$(EXE): $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) $(OBJS) -o $@

$(DEBUG_EXE): $(OBJS)
	g++ -fconcepts $(INCLUDE) -O0 -std=c++1z -g3 $(OBJS) -o debug

$(VALGRIND_TARGET): $(DEBUG_EXE)
	valgrind -v --track-origins=yes --num-callers=20 --leak-check=yes --leak-resolution=high --show-reachable=yes ./debug

main.o: main.cpp $(HEADERS)
	$(CC) -c $(FLAGS) $(INCLUDE) main.cpp -o $@

user_structs.o: user_structs.cpp $(HEADERS)
	$(CC) -c $(FLAGS) $(INCLUDE) main.cpp -o $@

all: clean $(EXE)

.PHONY:clean
clean:
	-@rm -rf *.o $(EXE) $(DEBUG_EXE) 2>/dev/null || true

