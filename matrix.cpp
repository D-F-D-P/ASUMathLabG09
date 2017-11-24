#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <string>
#include <algorithm>

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

    //empty_matrix();

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


string newString = space_trimer(inputString); // remove spaces


// getting the name of the matrix
string name = newString.substr(0,1);

// to remove brackets
int bracketFinder = newString.find("[",0);
string newString2;
if( newString[newString.length()-1] != ';' )
newString2 = newString.substr(bracketFinder+1, newString.length()-bracketFinder-2);
else
newString2 = newString.substr(bracketFinder+1, newString.length()-bracketFinder-3);


int rows;
int columns;
rows = number_of(newString2.length(),newString2, ";") + 1;

// new Edit ...
if( newString[newString.length()-3] == ';' )
    rows --;



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
 if( newString[newString.length()-1] != ';' )
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
    string name = this->name;
   destroy_matrix();


   this -> rows = p.rows;
   this -> columns = p.columns;
    this -> name = name;

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

  //  empty_matrix();

}



void matrix::print_matrix()
{
    if(this->elements == NULL) //to prevent crash
        cout << "this matrix is not created" <<endl;
    else
    cout << this->name << " = " << endl;
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){

            switch(number_digits(elements[i][j]))
           {

            case 1:
			std::cout <<"    \t" << std::fixed << std::setprecision(4) << elements[i][j] ; //4 digits like matlab :D
			break;

            case 2:
		    std::cout <<"   \t" << std::fixed << std::setprecision(4) << elements[i][j] ;//4 digits like matlab :D
			break;

			case 3:
		    std::cout <<"  \t" << std::fixed << std::setprecision(4) << elements[i][j]; //4 digits like matlab :D
			break;

			case 4:
		    std::cout <<" \t" << std::fixed << std::setprecision(4) << elements[i][j]; //4 digits like matlab :D
			break;

			default:
            std::cout <<"\t" << std::fixed << std::setprecision(4) << elements[i][j]; //4 digits like matlab :D
           }

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
    matrix* temp = new matrix;
    *temp = *this;
    matrix u(rows,columns);
    u.unity_matrix();
    int n = rows;
    int i,j,k;
    float d;
    for(i=n-1;i>0;i--)
    {
        //if(a[i-1][1]<=a[i][1])
        if (temp -> elements[i-1][i-1]==0)
        for(j=0;j<n;j++)
        {
            d=temp -> elements[i][j];
            temp -> elements[i][j]=temp -> elements[i-1][j];
            temp -> elements[i-1][j]=d;
            d=u.elements[i][j];
            u.elements[i][j]=u.elements[i-1][j];
            u.elements[i-1][j]=d;
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        if(j!=i)
        {
            d=temp -> elements[j][i]/temp -> elements[i][i];
            for(k=0;k<n;k++)
            {
                temp -> elements[j][k]-=temp -> elements[i][k]*d;
                u.elements[j][k]-=u.elements[i][k]*d;
            }
        }
    }
    for(i=0;i<n;i++)
    {
    d=temp -> elements[i][i];
        for(j=0;j<n;j++)
        {
            temp -> elements[i][j]=temp -> elements[i][j]/d;
            u.elements[i][j]=u.elements[i][j]/d;
        }
    }
    return u;



  /*matrix *temp = new matrix;
  temp->copy_matrix(*this);
  double det = temp->get_determinant();
  //determinant();
  int flag = 1;
  for (int i = 0; i < temp->columns; i++)
  {
      flag = pow(-1,i);
    for (int k = 0; k < temp->rows; k++)
    {
      temp->elements[k][i] = (this->new_sub_matrix(k,i)).get_determinant() * flag;
      flag *= -1;
    }
  }
  temp->flip_matrix();
  multiply_num(*temp, (1/det), *temp);
  return *temp;*/
}

void matrix:: unity_matrix()
{
    if ( rows != columns || rows ==0 || columns==0 )
        return;

for(int i = 0 ; i < rows ; i++)
        for(int j=0 ; j < columns ; j++)
            if(i == j)
            elements[i][j] = 1;
        else
            elements[i][j] = 0;
}

bool is_equal(matrix &A , matrix &B)
{

    if (A.rows != B.rows || A.columns!= B.columns)
        return false;

    for(int i = 0 ; i < A.rows ; i++ )
        for(int j = 0 ; j < A.columns ; j++)
        if(A.elements[i][j]!=B.elements[i][j])
      return false;

    return true;

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
	 if ( (A.rows != B.rows  ||  A.columns != B.columns ) )
        cout << "error sizing" << endl;

	 else {

			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					 C.elements[i][j] = A.elements[i][j] - B.elements[i][j];
			 }
	      }
 }







  //sum of matrix and number
  void sum_num(matrix &A, double B, matrix &C)
  {


	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  C.elements[i][j] = A.elements[i][j] + B;
	  }


  }



  //multiply of matrix and number
  void multiply_num(matrix &A, double B, matrix &C)
{

	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  C.elements[i][j] = A.elements[i][j] * B;
	  }


}


  //sub of matrix and number
  void sub_num(matrix &A, double B, matrix &C)
  {


	  for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  C.elements[i][j] = A.elements[i][j] - B;
	  }

  }


void div_num(matrix &A, double B , matrix &C) // to divide matrix and number

{
    for (int i = 0; i < A.rows; i++)
	  {
		  for (int j = 0; j < A.columns; j++)
			  C.elements[i][j] = B / A.elements[i][j];
	  }
}

void multiply_matrix(matrix &A, matrix &B , matrix &C)
{

    if (A.columns!=B.rows)
        cout << "error columns of first is not equal rows of the second" << endl;
        //Or whatever the doctor says

     else
     {

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
//Copy cant be reference
 matrix matrix :: operator = (matrix m)
 {
     copy_matrix(m);
     return *this; // this line calls the copy constructor
 }


// sum_matrix
  matrix matrix:: operator + (matrix &m) //C = A + B
  {
     matrix result(this->rows,this -> columns);
     sum_matrix((*this),m , result);
	 return result;
  }


 matrix matrix:: operator - (matrix &m) // A - B = C
  {
     matrix result(this->rows,this -> columns);
     sub_matrix((*this),m , result);
	 return result;
  }

matrix matrix :: operator + (double a)// C = m + a
{
     matrix result(this->rows,this -> columns);
     sum_num((*this),a , result);
	 return result;

}



matrix matrix :: operator - (double a)// C = m -a
{
     matrix result(this->rows,this -> columns);
     sub_num((*this), a , result);
	 return result;
}



matrix operator + (double a, matrix &m) //a+m
{

     matrix result(m.rows, m.columns);
     sum_num(m,a , result);
	 return result;


}


matrix operator - (double a, matrix &m) // a-m
{

     matrix result(m.rows, m.columns);
     m=-m;
     sum_num(m,a , result);
	 return result;

}

matrix operator - (matrix &p) // A = -A
{
    matrix result(p.rows,p.columns);

    multiply_num(p,-1,result);
    return result;
}


matrix matrix :: operator * (matrix &m) //C=A*B
{
    matrix result(m.rows , m.columns);
    multiply_matrix((*this),m, result);
    return result;

}

matrix matrix :: operator * (double a) //C=m*a
{
    matrix result(this->rows , this-> columns);
    multiply_num(*this,a,result);
    return result;
}



matrix operator * (double a, matrix &m) // C = a * m
{
    matrix result(m.rows , m.columns);
    multiply_num(m,a,result);
    return result;
}


matrix matrix :: operator / (matrix &m)
{


    matrix result(m.rows , m.columns);
    if(is_equal((*this) , m))
    result.unity_matrix();

    else if (m.get_determinant() == 0 || isnan(m.get_determinant()))
    {
        cout << "Error determinant = 0" <<endl;
    }

    else
    divide_matrix((*this), m , result);

    return result;

}

matrix matrix :: operator / (double a) //C = m/a
{
    matrix result(this->rows , this-> columns);
    multiply_num(*this,(1/a),result);
    return result;
}

matrix operator / (double a, matrix &m) // C = a / m
{
    matrix result(m.rows,m.columns);
    div_num(m,a,result);
    return result;
}

//WALEED ...
matrix matrix::get_cofactor(int r,int c)
{
    if(rows<=1 && columns<=1);//throw("Invalid matrix dimension");
    matrix m(rows-1, columns-1);
    for(int iR=0;iR<m.rows;iR++)
        for(int iC=0;iC<m.columns;iC++)
          {
            int sR = (iR<r)?iR:iR+1;
            int sC = (iC<c)?iC:iC+1;
            m.elements[iR][iC] = elements[sR][sC];
          }
    return m;

}
double matrix::get_determinant()
{
    matrix *temp = new matrix;
    *temp = *this;

    double result = 1;
    int n = rows;
    int i,j,k;
    float d;
    for(i=n-1;i>0;i--)
    {
        //if(a[i-1][1]<=a[i][1])
        if (temp -> elements[i-1][i-1]==0)
        for(j=0;j<n;j++)
        {
            d=temp -> elements[i][j];
            temp -> elements[i][j]=temp -> elements[i-1][j];
            temp -> elements[i-1][j]=d;
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        if(j!=i)
        {
            d=temp -> elements[j][i]/temp -> elements[i][i];
            for(k=0;k<n;k++)
            {
                temp -> elements[j][k]-=temp -> elements[i][k]*d;
            }
        }
    }
    for (i = 0 ; i < n ; i++)
    {
        result *= temp -> elements[i][i];
    }
    return result;




   /* if(rows!=columns);//throw("Invalid matrix dimension");
    if(rows==1&&columns==1)return elements[0][0];
    double value = 0, m = 1;
    for(int iR=0;iR<rows;iR++)
    {
        value+= m * elements[0][iR] * get_cofactor(0, iR).get_determinant();
        m *= -1;
    }
    return value;*/

}




// Global Functions

//count number of chars in a string
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


//to trim spaces from the begin and end of a text
string space_trimer(string text)
{

        // to trim extra start spaces
        int spaceStarter = 0;

        while(1)
        {
        if(text.substr(spaceStarter,1) == " ")
        {
            spaceStarter++;
        }
        else break;
        }

        string start_trimed = text.substr(spaceStarter,text.length() - spaceStarter);

        // to trim extra ending spaces
        spaceStarter = start_trimed.length()-1;
        int counter = 0;
        while(1)
        {
        if(start_trimed.substr(spaceStarter,1) == " ")
        {
            counter ++;
            spaceStarter--;
        }
        else break;
        }
        string all_trimed = start_trimed.substr(0, start_trimed.length() - counter);

     return all_trimed ;

}

//to find a number of digits in a float digits ( 1322.12 returns 4 ) max 6 digits
int number_digits(float input)
{
if (input < 10) return 1;
if (input < 100) return 2;
if (input < 1000) return 3;
if (input < 10000) return 4;
if (input < 100000) return 5;
if (input < 1000000) return 6;

}

