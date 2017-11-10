
#include "dynamic_array_matrix.h"
#include <iostream>
using namespace std;

/*private members are
matrix* pointer;
	 int size;
*/
//----------------------------------------------------------//constructor
 dynamic_array_matrix::dynamic_array_matrix(int size1)
 {
	size=size1;
	pointer = new matrix[size];
   
 }

 //------------------------------- ------------------------//distructor
  dynamic_array_matrix::~dynamic_array_matrix()
	 {
		 delete[]pointer;
	 }

  //------------------------------------------------------//get_size
  int dynamic_array_matrix::get_size()
  {
	  return size;
  }
  //-----------------------------------------------------//get_matrix->this return the pointer to access the matrices easily from the main function
  matrix* dynamic_array_matrix:: get_matrix()
   {
	   return pointer;
   }
  //-----------------------------------------------------//set_size -> the new size must be bigger the the old one 
   void dynamic_array_matrix::set_size(int new_size)
	{
		matrix *new_pointer = new matrix[new_size];
		for(int counter=0;counter<size;counter++)
		{
			new_pointer[counter]=pointer[counter];
		}
		
		delete[]pointer;
		pointer = new_pointer;
		size=new_size;
	}
   //---------------------------------------------------//add_element ->to add one matrix to the array
   void dynamic_array_matrix::add_element()
   {
	   set_size(size+1);
   }
   //--------------------------------------------------//print ->to print the array
   void dynamic_array_matrix::print()
   {
	   for(int counter=0;counter<size;counter++)
	   {
		   cout << "Matrix #" << counter+1 << " =" << endl;
		   pointer[counter].print_matrix();
		   cout<<endl;
	   }
   }