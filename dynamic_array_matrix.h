
#ifndef DYNAMIC_ARRAY_MATRIX_H
#define DYNAMIC_ARRAY_MATRIX_H
#include <iostream>
#include "matrix.h"
#include <string>
using namespace std;
class dynamic_array_matrix//this class is to provide a dynamic array of our matrix class
{
	//private members
	matrix** pp_matrix;//pointer to pointer to matrix
	 int size;

	 // to not create element each add_element
	 int fake_size;
	 void set_fake_size(int new_size);
public:
    
	//constructor
	  dynamic_array_matrix();

	//distructor
	  ~dynamic_array_matrix();

	//gets
	  int get_size();
	  matrix** get_array_pointer();	

	//algorithmic function
	  void add_element();
	  void print();
      matrix* find_matrix(string name1);

};
#endif
