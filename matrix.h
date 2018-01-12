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
    void sum(matrix *A , matrix *B);
    void copy_matrix(matrix &p);
    matrix new_sub_matrix(int row, int column); // generate a sub matrix, it won't crash
    double determinant(); // measure the determinant of the matrix, it will crash if the number of rows != num of colums
    void flip_matrix(); //flips the rows and columns , it won't crash
    matrix inverse(); // divide matrix A over B , it won't crash if the rows != columns so make sure you operate on the right data
    void unity_matrix();

    //TEST WALEED ...
    double get_determinant();
    matrix get_cofactor(int r, int c);


	//Friend functions
    friend void sum_matrix(matrix &A, matrix &B , matrix &C); // to sum two matrix C = A+B
	friend void sub_matrix(matrix &A, matrix &B , matrix &C); // to sub two matrix C = A-B
	friend void multiply_matrix(matrix &A, matrix &B , matrix &C); // to multiply two matrix C =  A*B
	friend void divide_matrix(matrix &A, matrix &B , matrix &C); // divide matrix A over B , it will crash if the number of rows != num of colums or if the 2 matrix don't match
    friend void sum_num(matrix &A, double B , matrix &C); // to sum matrix and number
	friend void sub_num(matrix &A, double B , matrix &C); // to sub matrix and number
	friend void multiply_num(matrix &A, double B , matrix &C); // to multiply matrix and number
    friend void div_num(matrix &A, double B , matrix &C); // to divide matrix and number
    friend bool is_equal(matrix &A , matrix &B);

    //Operators
    matrix operator = (matrix  m); // A = B = C
    friend matrix operator - (matrix &m); // C = -A
	matrix operator + (matrix  &m);// C = A + B
	matrix operator + (double a);// C =  A + number
	friend matrix operator + (double a, matrix &m);// C = number + A
	matrix operator - (matrix  &m);// C = A - B
	matrix operator - (double a);// C = A - number
	friend matrix operator - (double a, matrix &m); // C = number - A
	matrix operator * (matrix &m); // C = A + B
	matrix operator * (double a); // C= A * number
	friend matrix operator * (double a, matrix &m); // C = number * A
    matrix operator / (matrix &m); //C= A/B it will crash if the number of rows != num of colums or if the 2 matrix don't match
    matrix operator / (double a); //C= A/number
    friend matrix operator / (double a, matrix &m); //C=number/A


//Phase two Functions
      matrix zeros(int rows, int columns);//func. to fill matrix with zeros
	 matrix random(int rows, int columns);// func.to fill matrix with random no.
	matrix ones(int rows, int columns); //Function for filling the matrix with ones

	friend void power(matrix& a,int n,matrix& result);//matrix power int
	matrix operator ^ (int n);


};

//global functions
std::string space_trimer(std::string text); // remove extra spaces from beginning of a text
int number_of(int e, std::string s,std::string c); // count the number of special char in a text
int number_digits(float input); //count number of digits


#endif // MATRIX_H
