#include "matrix.h"
#include <iostream>

using namespace std;

int main()
{
    //Test Code
    matrix m1(2,4); //rows = 2, columns =4
    m1.fill_matrix_cl();

    cout << "I am in the main now!" << endl;
    int columns = m1.get_columns();
    cout << "number of columns = " << columns <<endl;
    m1.print_matrix();
    m1.empty_matrix();
    m1.print_matrix();
    m1.destroy_matrix();

    matrix m2;
    m2.print_matrix();



	return 0;
}
