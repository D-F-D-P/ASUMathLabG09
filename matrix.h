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
    ~matrix(); //destructor
    matrix(matrix &p);// copy operator ( matrix A = B )
    void destroy_matrix();


    //gets
    int get_rows();
    int get_columns();
    std::string get_name();

    //sets
    void set_rows(int rows);
    void set_columns(int columns);
    void set_name(std::string name);

    void resize_matrix(int rows, int columns);//updates num of rows and coulmns and updates the elements array

    //algorithms and functions
    void fill_matrix_cl();//fill matrix with cin to test your function add , sub ,..
    void fill_matrix(std::string inputString); //fill from a string
    void empty_matrix(); // make all the elements of the array = 0;
    void copy_matrix(matrix &p);
    void print_matrix();
    matrix operator = (matrix &p); // A = B = C
    
	
    //static matrix create_matrix(int rows, int columns);
    
//functions for calculations
matrix operator * (matrix& m); //C=A*B 



};

#endif // MATRIX_H
