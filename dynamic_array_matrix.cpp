#include <iostream>
    #include "dynamic_array_matrix.h"
    #include <string>
using namespace std;

/*private members are
matrix* pointer;
	 int size;
*/
//----------------------------------------------------------//constructor
 dynamic_array_matrix::dynamic_array_matrix()
 {
	size=5;
	valid_size=0;
	matrix_array = new matrix[size];

 }

 //------------------------------- ------------------------//distructor
  dynamic_array_matrix::~dynamic_array_matrix()
	 {
	     size=0;
         valid_size=0;
		 delete[]matrix_array;
	 }

  //------------------------------------------------------//get_size
  int dynamic_array_matrix::get_size()
  {
	  return size;
  }
  //-----------------------------------------------------//get_matrix->this return the pointer to access the matrices easily from the main function
  matrix* dynamic_array_matrix:: get_matrix()
   {
	   return matrix_array;
   }
  //-----------------------------------------------------//set_size -> the new size must be bigger the the old one
   void dynamic_array_matrix::set_size(int new_size)
	{
		matrix *new_array = new matrix[new_size];
		for(int counter=0;counter<size;counter++)
		{
			new_array[counter]=matrix_array[counter];
		}

		delete[]matrix_array;
		matrix_array = new_array;
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
		   matrix_array[counter].print_matrix();
		   cout<<endl;
	   }
   }
//------------------------------------------------------------//find_matrix

int dynamic_array_matrix::find_matrix(string name1)
{
    for(int i=0;i<this->valid_size;i++)
    {
        if(matrix_array[i].get_name()==name1)
        {
            return i;
        }
    }
    matrix_array[valid_size].set_name(name1);
    valid_size++;
    return valid_size-1;
}








