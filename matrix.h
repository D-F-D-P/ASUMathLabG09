#ifndef MATRIX_H
#define MATRIX_H
#include<string>
#include <iostream>

class matrix
{
	double** elements;
    int rows,columns;
    std::string name;

	/*attach any further variables here*/

public:

	/*attach your header function here*/

//<<<<<<< HEAD
	//example function
	void doNull();
	int** create_matrix(int rows, int columns);
//=======
	matrix(); //default constructor does not create a matrix
    matrix(int rows, int columns); //constructor create a matrix (rows*columns) leave it with it's rubbish data
    ~matrix(); //destructor
    matrix(matrix &p);// copy operator ( matrix A = B )
    void destroy_matrix();


    //gets
    int get_rows();
    int get_columns();
    std::string get_name();


    void set_name(std::string name);

    void resize_matrix(int rows, int columns);//updates num of rows and coulmns and updates the elements array

    //algorithms and functions
    void fill_matrix_cl();//fill matrix with cin to test your function add , sub ,..
    void fill_matrix(std::string inputString); //fill from a string
    void empty_matrix(); // make all the elements of the array = 0;
    void copy_matrix(matrix &p);
    void print_matrix();
    void reset_matrix(int rows, int columns);
    matrix operator = (matrix &p); // A = B = C
<<<<<<< HEAD
    
	
    //static matrix create_matrix(int rows, int columns);
    
//functions for calculations
matrix operator * (matrix& m); //C=A*B 


=======

    //functions for calculations
    matrix operator * (matrix& m); //C=A*B 
>>>>>>> ff0add0c8d0899f854a7e39fdf857a885fa02626

};
//>>>>>>> master

//global functions
std::string space_trimer(std::string text); // remove extra spaces from beginning of a text
int number_of(int e, std::string s,std::string c); // count the number of special char in a text


#endif // MATRIX_H
