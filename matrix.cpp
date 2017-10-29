#include "matrix.h"
#include <iostream>
using namespace std;
/*attach your libraries here*/

/*
	attach your function here and make sure
 	you use the inputs from the class variables
 	in case you needed to attach a new variable
 	inside the class feel free to add it in "matrix.h"
*/

//example function
//void matrix::doNull();

//default constructor
matrix::matrix()
{
    elements = nullptr;
    rows = 0;
    columns =0;
    name = "";
}


//constructor
matrix::matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    elements = new double*[rows];
    for(int i=0;i<rows;i++)
    {
        elements[i] = new double[columns];
    }
}

//copy constructor
matrix::matrix(matrix& p)
{
    elements = nullptr;
    copy_matrix(p);
}


//gets
int matrix::get_rows()
{
 return rows;
}

int matrix::get_columns()
{
 return columns;
}

string matrix::get_name()
{
 return name;
}


//sets
void matrix::set_rows(int rows)
{
    this -> rows = rows;
}

void matrix::set_columns(int columns)
{
    this -> columns = columns;
}

void matrix::set_name(string name)
{
    this -> name = name;
}

//resize matrix
void matrix::resize_matrix(int rows, int columns)
{
	double** newElements = new double*[rows];
    for(int i=0;i<rows;i++){
        newElements[i] = new double[columns];
        if((i+1)<=this->rows)
        {
        	for(int k=0; k<this->columns; k++)
	        {
	        	if((k+1)<=this->columns)
        		{
        			newElements[i][k] = this->elements[i][k];
        		}
	        }
        }
    }
	this->destroy_matrix();
	this->rows = rows;
	this->columns = columns;
	this->elements = newElements;
}


//destructor
matrix::~matrix()
{
    if(elements)
        delete []elements;
}

//destroy matrix
void matrix::destroy_matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] elements [i]; //deletes an inner array of integer;
	}

	delete[] elements; //delete pointer holding array of pointers;
}

//to have a filled array quickly to test your functions algorithms
void matrix::fill_matrix_cl()
{
    cout << "Please fill the matrix with its elements" << endl;
	for (int i = 0; i < rows; i++)
	{
	    cout << "values in row: " << i+1 << endl;
		for (int j = 0; j < columns; j++)
		{
			cin >> elements[i][j];
		}
		cout << endl;
	}
}

void matrix::fill_matrix(string inputString)
{

// to be implemented..

}

//empty matrix used in result to make it initialed with zero
void matrix::empty_matrix()
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0 ; j < columns ; j++)
            elements[i][j]=0;
	}

}

void matrix::copy_matrix(matrix& p)
{
    if(elements) // if it was filled
        destroy_matrix();

   this -> rows = p.rows;
   this -> columns = p.columns;

   //create the matrix
    elements = new double*[rows];
    for(int i=0;i<rows;i++)
    {
        elements[i] = new double[columns];
    }

    //copy the values
    for (int i = 0; i < rows; i++)
	{
		for (int j = 0 ; j < columns ; j++)
           elements[i][j] = p.elements[i][j];
	}

}



void matrix::print_matrix()
{
    if(this->elements == nullptr) //to prevent crash
        cout << "this matrix is not created" <<endl;
    else
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<elements[i][j]<<"\t";
		}
		cout<<endl;
	}
}


 matrix matrix :: operator = (matrix &p)
 {
     copy_matrix(p);
     return *this;

 }

/*matrix matrix::create_matrix(int rows, int columns){
    matrix newMatrix;
    newMatrix.rows = rows;
    newMatrix.columns = columns;
    newMatrix.elements = new double*[rows];
    for(int i=0;i<rows;i++){
        newMatrix.elements[i] = new double[columns];
    }
    return newMatrix;
}*/


matrix matrix::operator * (matrix& m){
    if (this->columns!=m.rows)
      //Or whatever the doctor says
	    cout << "error columns of first is not equal rows of the second" << endl;
    matrix r(this->rows,m.columns);

    //initializing elements of matrix r=0
    for (int i=0;i<this->rows;i++){
        for (int j=0;j<m.columns;j++){
            r.elements[rows][columns]=0;
        }
    }

    // Multiplying and store in r
     for (int i=0;i<this->rows;i++){
        for (int j=0;j<m.columns;j++){
            for (int k=0;k<this->columns;k++){
                r.elements[rows][columns] += this->elements[rows][k]*m.elements[k][columns];
            }
        }
    }
    return r;
}


