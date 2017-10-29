
//there is no need to include <iostream> or "matrix.h" we did it in "dynamic_matrix.h"
#include "dynamic_array_matrix.h"


//there is no need to include <iostream> or "matrix.h" we did it in "dynamic_matrix.h"
#include "dynamic_array_matrix.h"



// .get_matrix() returns the main pointer of the dynamic_matrix 
#define MATRIX matrix_array.get_matrix() //so this #define make it easy to access any matrix in the array
using namespace std;

int main()
{


//test code for the dynamic_matrix
	dynamic_array_matrix matrix_array(1);

	MATRIX[0].resize_matrix(3,3);//set the size 

	MATRIX[0].fill_matrix_cl();//fill the matrix from cin>>

	matrix_array.add_element();//to add matrix to the dynamic array

	cout<<matrix_array.get_size()<<endl;

	MATRIX[1].resize_matrix(3,3);

	MATRIX[1].fill_matrix_cl();
	
	matrix_array.print();


	int x;//instead of getchar
	cin>>x;
	return 0;
}


/* the old test code
//Test Code
    matrix m1(2,4); //rows = 2, columns =4
    m1.fill_matrix_cl();

    cout << "I am in the main now!" << endl;
    int columns = m1.get_columns();
    cout << "number of columns = " << columns <<endl;
    m1.print_matrix();

    matrix m2;
    m2.print_matrix();

    matrix m3;
    m3 = m1;

    m1.destroy_matrix();

    cout << "test the copy function" << endl;


    m3.print_matrix();
    m3.print_matrix();*/

