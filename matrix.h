#ifndef MATRIX_H
#define MATRIX_H
#include<string>


class matrix
{
	double** elements;
    int rows,columns;
    std::string name;
    //  bool valid; to be added..

	/*attach any further variables here*/

public:

	/*attach your header function here*/

	matrix(); //default constructor does not create a matrix
	matrix(const matrix &p);//( matrix A = B )
    matrix(int rows, int columns); //constructor create a matrix (rows*columns) and initialize them with zeros
    ~matrix(); //destructor



    //gets
    int get_rows();
    int get_columns();
    std::string get_name();

    //sets
    void set_name(std::string name);
    void resize_matrix(int rows, int columns);//updates num of rows and columns and updates the elements array

    //algorithms and functions
    void fill_matrix_cl();//fill matrix with cin
    void fill_matrix(std::string inputString); //fill from a string
    void empty_matrix(); // make all the elements of the array = 0;
    void destroy_matrix();
    void print_matrix();
    void reset_matrix(int rows, int columns); //reset dimentions
    void copy_matrix(matrix &p);

	//Friend functions
    friend void sum_matrix(matrix &A, matrix &B , matrix &C); // to sum two matrix C = A+B
	friend void sub_matrix(matrix &A, matrix &B , matrix &C); // to sub two matrix C = A-B
	friend void multiply_matrix(matrix &A, matrix &B , matrix &C); // to multiply two matrix C =  A*B
	friend void sum_num(matrix &A, int B , matrix &C); // to sum matrix and number
	friend void sub_num(matrix &A, int B , matrix &C); // to sub matrix and number
	friend void multiply_num(matrix &A, int B , matrix &C); // to sub matrix and number

    //Operators
    matrix operator = (matrix  p); // A = B = C
	matrix operator + (matrix  p);// A + B = C
	matrix operator - (matrix  p);// A - B = C
	matrix operator + (int p);// A + number = C
	friend matrix operator + (int a, matrix p);// number + A = C
	matrix operator - (int p);// A - number = C
	friend matrix operator - (int a, matrix p);// number + A = C
	matrix operator * (matrix p);
	matrix operator * (int p); // C= A * number
	friend matrix operator * (int a, matrix p); // A = number * A
	friend matrix operator - (matrix p); // A = -A



};

//global functions
std::string space_trimer(std::string text); // remove extra spaces from beginning of a text
int number_of(int e, std::string s,std::string c); // count the number of special char in a text


#endif // MATRIX_H
