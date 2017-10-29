
#ifndef DYNAMIC_ARRAY_MATRIX_H
#define DYNAMIC_ARRAY_MATRIX_H

#include "matrix.h"


class dynamic_array_matrix//this class is to provide a dynamic array of our matrix class
{
	//private members
	matrix* pointer;
	 int size;
public:
	//constructor
	  dynamic_array_matrix(int size);

	//distructor
	  ~dynamic_array_matrix(); 

	//gets
	  int get_size();
	  matrix* get_matrix();
	//sets
	  void set_size(int new_size);
	    
	//algorithmic function
	  void add_element();
	  void print();


};
#endif