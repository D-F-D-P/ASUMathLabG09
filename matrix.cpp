#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <math.h>

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
    elements =NULL;
    rows = 0;
    columns =0;
    name = "";
}


//constructor
matrix::matrix(int rows, int columns)
{

    this->rows = rows;
    this->columns = columns;

     if ((rows*columns) == 0) { elements = NULL; return; }

    elements = new double*[rows];
    for(int i=0;i<rows;i++)
    {
        elements[i] = new double[columns];
    }

    empty_matrix();

}

//copy constructor
matrix::matrix(const matrix& p)
{

   this -> rows = p.rows;
   this -> columns = p.columns;


 if ((rows*columns) == 0) { elements = NULL; return; }


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

void matrix::set_name(string name)
{
    this -> name = name;
}

//resize matrix
void matrix::resize_matrix(int rows, int columns)
{

     if ((rows*columns) == 0) { rows = columns = 0; elements = NULL; return; }

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

 if(elements)
 {



        for (int i = 0; i < rows; i++)
        {
            delete[] elements [i]; //deletes an inner array of integer;
        }
        delete[] elements; //delete pointer holding array of pointers;
   
    elements =NULL;
    rows = 0;
    columns =0;
    name = "";
 }
}
//fill matrix from cin
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


   //To print or not


 if( inputString[inputString.length()-1] != ';' )
    print_matrix();

}

//empty matrix
void matrix::empty_matrix()
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0 ; j < columns ; j++)
            elements[i][j]=0;
	}

}

void matrix::copy_matrix(matrix & p)
{
   destroy_matrix();


   this -> rows = p.rows;
   this -> columns = p.columns;


 if ((rows*columns) == 0) { elements = NULL; return; }


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
    destroy_matrix();

    this -> rows = rows;
    this -> columns = columns;

     if ((rows*columns) == 0) { elements = NULL; return; }

    this -> elements = new double*[rows];
    for(int i=0;i<rows;i++)
    {
        this -> elements[i] = new double[columns];
    }

    empty_matrix();

}



void matrix::print_matrix()
{
    if(this->elements == NULL) //to prevent crash
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

// generate a sub matrix, it won't crash

matrix matrix::new_sub_matrix(int row, int column)

{
  matrix *temp = new matrix((this->rows)-1,(this->columns)-1);
  for(int i=0;i<(temp->rows);i++)
  {

    int flagRows = 0;
    if(i >= row){
      flagRows = 1;
    }
    for(int k=0;k<(temp->columns);k++)
    {
      int flagColumns = 0;
      if(k >= column){
        flagColumns = 1;
      }
      temp->elements[i][k] = this->elements[i+flagRows][k+flagColumns];

    }
  }
  return *temp;
}

// measure the determinant of the matrix, it will crash if the number of rows != num of colums
double matrix::determinant()
{
  double result = 0.0;
  if(this->rows == 2)
  {
    result = ((this->elements[0][0])*(this->elements[1][1]))
            - ((this->elements[0][1])*(this->elements[1][0]));
    return result;
  }
  for(int i=0;i<(this->rows);i++)
  {
    matrix temp = this->new_sub_matrix(i,0);
    result += (temp.determinant())*pow(-1,i)*this->elements[i][0];
  }
  return result;
}

//flips the rows and columns , it won't crash
void matrix::flip_matrix()
{
  matrix temp(this->columns, this->rows);
  for(int i=0;i< temp.rows;i++)
  {
    for(int k=0;k< temp.columns;k++)
    {
      temp.elements[i][k] = this->elements[k][i];
    }   
  }
  std::string name = this->name;
  this->copy_matrix(temp);
  this->name = name;
}

// divide matrix A over B , it won't crash if the rows != columns so make sure you operate with the right data
matrix matrix::inverse()
{
  matrix *temp = new matrix;
  temp->copy_matrix(*this);
  double det = temp->determinant();
  int flag = 1;
  for (int i = 0; i < temp->columns; i++)
  {
    flag = pow(-1,i);
    for (int k = 0; k < temp->rows; k++)
    {
      temp->elements[k][i] = (this->new_sub_matrix(k,i)).determinant() * flag;
      flag *= -1;
    }
  }
  temp->flip_matrix();
  multiply_num(*temp, (1/det), *temp);
  return *temp;
}

// divide number B over matrix A , it will crash if the number of rows != num of colums
void divide_num_over_matrix(matrix &A, double B , matrix &C)
{
  matrix a = A.inverse();
  multiply_num(a, B , C);
}

// divide matrix A over B , it will crash if the number of rows != num of colums or if the 2 matrix don't match
void divide_matrix(matrix &A, matrix &B , matrix &C)
{
  matrix b = B.inverse();
  multiply_matrix(A, b , C);
}

 //sum of two matrix
  void sum_matrix(matrix &A, matrix &B , matrix &C)
 {
	 if (A.rows != B.rows ||  A.columns != B.columns)cout << "error sizing" << endl;

	 else {
            matrix result(A.rows,A.columns);
            C = result;
			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					 C.elements[i][j] = A.elements[i][j] + B.elements[i][j];
			 }
	      }

 }



// sub of two matrix
void sub_matrix(matrix &A, matrix &B , matrix &C)
 {

	 if (A.rows != B.rows  ||  A.columns != B.columns)cout << "error sizing" << endl;

	 else {

             matrix result(A.rows,A.columns);
             C = result;
			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					 C.elements[i][j] = A.elements[i][j] - B.elements[i][j];
			 }
	      }

 }



 // matrix matrix:: operator - (matrix & p) // A - B = C
  //{
  //return sub_matrix(*this, p);
  //}



  //sum of matrix and number
  void sum_num(matrix &A, double B, matrix &C)
  {
	  matrix result(A.rows, A.columns);

	  C = result;

	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  C.elements[i][j] = A.elements[i][j] + B;
	  }

  }



  //multiply of matrix and number
  void multiply_num(matrix &A, double B, matrix &C)
{
	  matrix result(A.rows, A.columns);

	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  result.elements[i][j] = A.elements[i][j] * B;
	  }
    C = result;

}


  //sub of matrix and number
  void sub_num(matrix &A, double B, matrix &C)
  {
	  matrix result(A.rows, A.columns);

	  C = result;

	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  C.elements[i][j] = A.elements[i][j] - B;
	  }

  }



void multiply_matrix(matrix &A, matrix &B , matrix &C)
{

    if (A.columns!=B.rows)
        cout << "error columns of first is not equal rows of the second" << endl;
        //Or whatever the doctor says

     else
     {

     matrix result(A.rows,B.columns);
     C = result;

    // Multiplying and store in r
     for (int i=0;i<A.rows;i++){
        for (int j=0;j<B.columns;j++){
            for (int k=0;k<A.columns;k++){
                C.elements[i][j] += A.elements[i][k]*B.elements[k][j];
            }
        }
    }

     }
}




// ************************ Operators ************************* //
//Copy
 matrix matrix :: operator = (matrix  p)
 {
     copy_matrix(p);
     return *this; // this line calls the copy constructor
 }

 //sum of two matrix
 
  matrix sum_matrix(matrix &A, matrix &B)
 {
	 matrix result(A.rows, A.columns);
	 if (A.rows != B.rows  && A.columns != B.columns)cout << "error sizing" << endl;
	
	 else {
			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					 result.elements[i][j] = A.elements[i][j] + B.elements[i][j];
			 }
	      }
	 return result;
 }

  // sum_matrix operator
  matrix matrix:: operator + (matrix & p) // A + B = C
  {
	 return sum_matrix(*this,p);
  }




// sub of two matrix
  matrix sub_matrix(matrix &A, matrix &B)
  {
	  matrix result(A.rows, A.columns);
	  if (A.rows != B.rows  && A.columns != B.columns)cout << "error sizing" << endl;
	 
	  else {
		  for (int i = 0; i < A.rows; i++)
		     {
			  for (int j = 0; j < A.columns; j++)
				  result.elements[i][j] = A.elements[i][j] - B.elements[i][j]; 
		     }
	       }
	  return result;
  }
  matrix matrix:: operator - (matrix & p) // A - B = C
  {
	  return sub_matrix(*this, p);
  }



  //sum of matrix and number

  matrix sum_num(matrix &A, int B)
  {
	  matrix result(A.rows, A.columns);

	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  result.elements[i][j] = A.elements[i][j] + B;
	  }

	  return result;
  }

  // sum_num operator
  matrix matrix:: operator + (int p) // A + B = C
  {
	  return sum_num(*this, p);
  }
 
  matrix operator + (int a , matrix &p) // A + B = C
  {
	  return sum_num(p,a);
  }

  //sub of matrix and number

  matrix sub_num(matrix &A, int B)
  {
	  matrix result(A.rows, A.columns);

	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  result.elements[i][j] = A.elements[i][j] - B;
	  }

	  return result;
  }

  // sub_num operator
  matrix matrix:: operator - (int p) // A - number = C
  {
	  return sub_num(*this, p);
  }

  matrix operator - (int a, matrix &p) // number - A = C
  {
	  return sub_num(p, a);
  }



// sum_matrix
  matrix matrix:: operator + (matrix p) // A + B = C
  {
     matrix result(this->rows,this -> columns);
     sum_matrix((*this),p , result);
	 return result;
  }


 matrix matrix:: operator - (matrix p) // A + B = C
  {
     matrix result(this->rows,this -> columns);
     sub_matrix((*this),p , result);
	 return result;
  }

matrix matrix :: operator + (double p)// A + number = C
{
     matrix result(this->rows,this -> columns);
     sum_num((*this),p , result);
	 return result;

}



matrix matrix :: operator - (double p)// A + number = C
{
     matrix result(this->rows,this -> columns);
     sub_num((*this),p , result);
	 return result;

}



matrix operator + (double a, matrix p)
{

     matrix result(p.rows, p.columns);
     sum_num(p,a , result);
	 return result;


}


matrix operator - (double a, matrix p)
{

     matrix result(p.rows, p.columns);
     p=-p;
     sum_num(p,a , result);
	 return result;

}

matrix operator - (matrix p)
{
    matrix result(p.rows,p.columns);

    multiply_num(p,-1,result);
    return result;
}


matrix matrix :: operator * (matrix p) //C=A*B
{
    matrix result(this -> rows , p.columns);
    multiply_matrix((*this),  p , result);

    return result;

}

matrix matrix :: operator * (double p) //C=A*B
{
    matrix result(this->rows , this-> columns);
    multiply_num(*this,p,result);
    return result;
}



matrix operator * (double a, matrix p) // A = double * A
{
    matrix result(p.rows , p.columns);
    multiply_num(p,a,result);
    return result;
}

//C=A/B it will crash if the number of rows != num of colums or if the 2 matrix don't match
matrix matrix :: operator / (matrix p) 
{
    matrix result(this -> rows , p.columns);
    divide_matrix((*this),  p , result);

    return result;

}

matrix matrix :: operator / (double p) //C=A/p
{
    matrix result(this->rows , this-> columns);
    multiply_num(*this,(1/p),result);
    return result;
}

//it will crash if the number of rows != num of colums
matrix operator / (double a, matrix p) // C = a / p
{
    matrix result(p.rows , p.columns);
    divide_num_over_matrix(p,a,result);
    return result;
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


/*matrix matrix :: sum_matrix(matrix &A)
{
     matrix result(this->rows , this -> columns);
	 if (A.rows != this ->rows  || A.columns != this ->columns)cout << "error sizing" << endl;

	 else {
			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					result.elements[i][j] =  this ->elements[i][j] + A.elements[i][j];
			 }
	      }
	 return result;
}
void matrix:: operator += (matrix& A)
{
 sum_matrix(A);
}



//   sub_num operator
  matrix matrix:: operator - (int p) // A - number = C
  {
	  return sub_num(*this, p);
  }

  matrix operator - (int a, matrix &p) // number - A = C
  {
	  return sub_num(p, a);
  }

// sum_num operator
  matrix matrix:: operator + (int p) // A + B = C
  {
  return sum_num(*this, p);
  }

  matrix operator + (int a , matrix &p) // A + B = C
  {
	  return sum_num(p,a);
  }

*/
