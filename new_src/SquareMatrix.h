#ifndef MATRIX_H
#define MATRIX_H

#define GROW_FACTOR 1.5
#define FIRST_ALLOC 4

#include <stdexcept>
#include <iostream>
#include <string.h>

template <typename EntryType>
class SquareMatrix{

public:
	EntryType * entry;
	int used;
	int alloced;

	SquareMatrix(){
		used = 0;
		alloced = FIRST_ALLOC;
		entry = new EntryType[alloced * alloced];
		memset(entry, 0, sizeof(EntryType) * alloced * alloced);
	}

	~SquareMatrix(){
		delete[] entry;
	}

	void resize(){

		/* Determine the square size of new matrix */
		int new_alloced = alloced * GROW_FACTOR;

		/* Get an empty array of bigger size */
		auto new_entry = new EntryType[new_alloced * new_alloced];
		memset(new_entry, 0, sizeof(EntryType) * new_alloced * new_alloced);

		/* Copy the contents of old matrix */
		for(int i = 0; i < used; i++){
			for(int j = 0; j < used; j++){
				*(new_entry + i*new_alloced + j) = (*(entry + i*alloced + j));
			}
		}

		/* Delete the old matrix */
		delete[] entry;

		/* Assign the new matrix to entry */
		entry = new_entry;
		alloced = new_alloced;
	}

	inline EntryType get_entry(int row_index, int column_index){
		return *(entry + row_index*alloced + column_index);
	}

	inline void set_entry(int row_index, int column_index, EntryType value){
		(*(entry + row_index*alloced + column_index)) = value;
	}

	inline void zero_entry(int row_index, int column_index){
		memset(entry + row_index*alloced + column_index, 0, sizeof(EntryType));
	}

	inline void inc_used(){
		used++;
		if (used > alloced){
			throw std::invalid_argument("horror");
		}
	}

	inline bool full(){
		return (used == alloced);
	}

	void print_matrix(){
		for(int i = 0; i < alloced; i++){
			for(int j = 0; j < alloced; j++){
				cout << get_entry(i, j) << "\t";
			}
			cout << endl;
		}

	}
	
};
#endif