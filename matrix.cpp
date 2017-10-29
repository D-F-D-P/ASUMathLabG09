#include "matrix.h"
<<<<<<< HEAD
=======
#include <iostream>
#include <cstdlib>
>>>>>>> ff0add0c8d0899f854a7e39fdf857a885fa02626

using namespace std;
/*attach your libraries here*/

/*
	attach your function here and make sure
 	you use the inputs from the class variables
 	in case you needed to attach a new variable
 	inside the class feel free to add it in "matrix.h"
*/

//example function
//<<<<<<< HEAD
//void matrix::doNull();
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
//=======
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


<<<<<<< HEAD
//sets
void matrix::set_rows(int rows)//there is abug
{
    this -> rows = rows;
}

void matrix::set_columns(int columns)//there is abug
{
    this -> columns = columns;
}

=======
>>>>>>> ff0add0c8d0899f854a7e39fdf857a885fa02626
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
   destroy_matrix();
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

string newString = space_trimer(inputString); // remove beginning spaces

// getting the name of the matrix
string name = newString.substr(0,1);

// to remove brackets
int bracketFinder = newString.find("[",0);
string newString2 = newString.substr(bracketFinder+1, newString.length()-bracketFinder-3);


int rows;
int columns;
rows = number_of(newString2.length(),newString2, ";") + 1;

// substring the string into row
int beginRow = 0 ; // position of a row starting
int endRow; // position of a row ending
string row ;
for(int i = 0 ; i < rows ; i ++)
{
    endRow = newString2.find(";",beginRow);
    row = newString2.substr(beginRow , endRow - beginRow);
    string newRow = space_trimer(row); // to remove beginning spaces
    beginRow = endRow+1; // update the begin of next find

    // now to get the number of columns
    if(i == 0)// to create the matrix once since i now can get number of columns
    {
    columns = number_of(newRow.length(),newRow," ") + 1;
    this -> reset_matrix(rows,columns);
    }

    // substring the row into elements
    int beginElement = 0;
    int endElement;
    string elementString;
    float elementFloat;
    for(int j = 0 ; j < columns ; j++)
    {
       endElement = newRow.find(" " ,beginElement);
       elementString = newRow.substr(beginElement, endElement - beginElement);
       beginElement = endElement +1;
       elementFloat = strtof((elementString).c_str(),0); // string to float
       // save the element to the matrix
       this -> elements[i][j] = elementFloat;
    }

}

   this -> name = name;

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


void matrix::reset_matrix(int rows, int columns)
{
    this -> rows = rows;
    this -> columns = columns;
    this -> elements = new double*[rows];
    for(int i=0;i<rows;i++)
    {
        this -> elements[i] = new double[columns];
    }

}



void matrix::print_matrix()
{
    if(this->elements == nullptr) //to prevent crash
        cout << "this matrix is not created" <<endl;
    else
    cout << this->name << " = " << endl;
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


// Global Functions
int number_of(int e, string s,string c)
{
int N=0;

for (int i=0;i<=e;i++)
    {
    if(s.substr(i,1)==c)
    N++;
    }
    return N;

}


string space_trimer(string text)
{
        int spaceCounter = 0;

        while(1)
        {
        if(text.substr(spaceCounter,1) == " ")
        {
            spaceCounter ++;
        }
        else break;
        }

   return text.substr(spaceCounter,text.length() - spaceCounter);

}

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

<<<<<<< HEAD
//>>>>>>> master
=======
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
>>>>>>> master
