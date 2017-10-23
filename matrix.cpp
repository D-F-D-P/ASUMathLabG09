#include "matrix.h"

/*attach your libraries here*/

/*
	attach your function here and make sure
 	you use the inputs from the class variables
 	in case you needed to attach a new variable 
 	inside the class feel free to add it in "matrix.h"
*/

//example function
void matrix::doNull();
int**  matrix::create_matrix(int rows, int columns)
{
	/*
	A dynamic 2D array is basically an array of pointers to arrays.
	First, we will allocate memory for an array which contains a set of pointers.
	Next, we will allocate memory for each array which is pointed by the pointers.
	The deallocation of memory is done in the reverse order of memory allocation.
	*/
	int** matrix = new int* [rows];
	
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}

	return matrix;
}