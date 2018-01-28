#include <iostream>
    #include "dynamic_array_matrix.h"
    #include <string>
using namespace std;

/*private members are
matrix* matrix_array;
	 int size;
*/
//----------------------------------------------------------//constructor
 dynamic_array_matrix::dynamic_array_matrix()
 {
	fake_size=10;
	size=0;
	pp_matrix = new matrix*[fake_size];

 }

 //------------------------------- ------------------------//distructor
  dynamic_array_matrix::~dynamic_array_matrix()
	 {
	  for (int i = 0; i < fake_size; i++)
	  {
		  delete pp_matrix[i];
	  }
	  delete[]pp_matrix;
	     size=0;
         fake_size=0;
	 }

  //------------------------------------------------------//get_size
  int dynamic_array_matrix::get_size()
  {
	  return size;
  }
  //-----------------------------------------------------//get_array_pointer->this return the pointer of the pointers array
  matrix** dynamic_array_matrix:: get_array_pointer()
   {
	   return pp_matrix;
   }
  //-----------------------------------------------------//set_fake_size ->  the new size must be bigger the the old one 


   void dynamic_array_matrix::set_fake_size(int new_size)
	{

		   matrix **new_array = new matrix*[new_size];
		   for (int i = 0; i < size; i++)
		   {
			   new_array[i] = pp_matrix[i];
		   }

		   delete[]pp_matrix;
		   pp_matrix = new_array;

		   size = new_size;
	}
   //---------------------------------------------------//add_element ->to add one matrix to the array
   void dynamic_array_matrix::add_element()
   {
	   if (size == fake_size)
	   {
		   set_fake_size(size + 10);
	   }
	   pp_matrix[size] = new matrix;
	   size++;
	   return;
   }
   //--------------------------------------------------//print ->to print the array
   void dynamic_array_matrix::print()
   {
	   for(int i=0;i<size;i++)
	   {
		   cout << "Matrix #" << i+1 << " =" << endl;
		   pp_matrix[i]->print_matrix();
		   cout<<endl;
	   }
   }
//------------------------------------------------------------//find_matrix and create one if it was not created

matrix* dynamic_array_matrix::find_matrix(string name1)
{
    for(int i=0;i<size;i++)
    {
        if(pp_matrix[i]->get_name()==name1)
        {
            return pp_matrix[i];
        }
    }
	add_element(); // add new matrix with "new" and "size" is updated with size+1 so after this line the last element index is size-1

	pp_matrix[size-1]->set_name(name1);

    return pp_matrix[size-1];//return the pointer of the created matrix
}








