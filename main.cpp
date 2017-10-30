#include "matrix.h"
#include <iostream>

using namespace std;

int main()
{
    //Test Code
	matrix m1(2, 4); //rows = 2, columns =4
	m1.fill_matrix_cl();


	matrix m3 = m1 - 2;

	m3.print_matrix();

	return 0;
}
