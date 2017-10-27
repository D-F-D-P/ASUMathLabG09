#ifndef MATRIX_H
#define MATRIX_H
#include<string>


class matrix
{
	double** elements;
    int rows,columns;
    std::string name;

	/*attach any further variables here*/

public:

	/*attach your header function here*/

	matrix(); //default constructor does not create a matrix
    matrix(int rows, int columns); //constructor create a matrix (rows*columns) leave it with it's rubbish data
    void destroy_matrix();//like destructor but we are using dynamic allocation

    //gets
    int get_rows();
    int get_columns();
    std::string get_name();

    //sets
    void set_rows(int rows);
    void set_columns(int columns);
    void set_name(std::string name);

    //algorithms and functions
    void fill_matrix_cl();//fill matrix with cin to test your function add , sub ,..
    void fill_matrix(std::string inputString); //fill from a string
    void empty_matrix(); // make all the elements of the array = 0;
    matrix operator = (matrix &p); // copy operator ( A = B )
    void print_matrix();

    //static matrix create_matrix(int rows, int columns);


};

#endif // MATRIX_H
