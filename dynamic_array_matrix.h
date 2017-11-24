
#ifndef DYNAMIC_ARRAY_MATRIX_H
#define DYNAMIC_ARRAY_MATRIX_H
#include <iostream>
#include "matrix.h"
#include <string>
using namespace std;
class dynamic_array_matrix//this class is to provide a dynamic array of our matrix class
{
	//private members
	matrix* matrix_array;
	 int size;

public:
    int valid_size;
	//constructor
	  dynamic_array_matrix();

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
      int find_matrix(string name1);

};
#endif
