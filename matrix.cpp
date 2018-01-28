#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include "shuffleYard.cpp"
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

#define PI 3.14159265

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
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
    if(rows<0 || columns <0) throw(0);
    this->rows = rows;
    this->columns = columns;

     if ((rows*columns) == 0) {
       elements = NULL;
       cout<<"warning: rows or columns equal zero, NULL Matrix created."<<endl;
       return;
     }

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



 if ((rows*columns) == 0) {
   elements = NULL;
   cout<<"warning: input is a NULL matrix."<<endl;
   return;
  }


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
  //Expected loop on all the created objects' names to handle this input.
    this -> name = name;
}

//resize matrix
void matrix::resize_matrix(int rows, int columns)
{
    if(rows<0 || columns<0) throw(0);

     if ((rows*columns) == 0) {
       rows = columns = 0;
       elements = NULL;
       cout<<"warning: input rows or columns =0, NULL matrix created."<<endl;
       return;
      }

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
      if(cin.fail()) throw(1);
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
    else{
      int newcolumn=number_of(newRow.length(),newRow," ") + 1;
      if(newcolumn!=columns) throw(2);
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

 if ((rows*columns) == 0) {
   elements = NULL;
   cout<<"warning: input rows or columns =0, NULL matrix created."<<endl;
  return;
  }


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
    if(rows<0 || columns<0) throw(0);
    destroy_matrix();

    this -> rows = rows;
    this -> columns = columns;

     if ((rows*columns) == 0) {
       elements = NULL;
       cout<<"warning: input rows or columns =0, NULL matrix created."<<endl;
        return;
       }


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
        cout << "This matrix is not created." <<endl;
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
  if(row<0 || column<0) throw(0);
  if(rows*columns==0) throw(3);
  if(row>(rows-1) || column>(columns-1)) throw(4);

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
  if(rows!=columns) throw(5);

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


  if(rows != columns) throw(6);

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
    if(d==0) throw(7);
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
matrix* matrix_divide_elements(matrix &A, matrix &B)
{
    if((B.rows != A.rows) || (B.columns != A.columns))
        throw (22);
    matrix* result = new matrix (A.rows,A.columns);
    for (int i = 0 ; i < A.rows ;i++)
    {
        for(int j = 0 ; j < A.columns ; j++)
        {
            result->elements[i][j] = A.elements[i][j]/B.elements[i][j];
        }
    }
    return result;
}

void matrix:: unity_matrix()
{
  //  if ( rows != columns || rows ==0 || columns==0 )
    //    return;
if(rows != columns) throw(8);
if(rows==0 || columns==0) throw(9);
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
  if(B.get_columns() != B.get_rows()) throw(10);
  if(A.get_columns() != B.get_rows()) throw(11);

  matrix b = B.inverse();
  multiply_matrix(A, b , C);
}

 //sum of two matrix
  void sum_matrix(matrix &A, matrix &B , matrix &C)
 {
	 //if (A.rows != B.rows ||  A.columns != B.columns)cout << "error sizing" << endl;
   if(A.rows !=B.rows || A.columns != B.columns) throw(12);
			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					 C.elements[i][j] = A.elements[i][j] + B.elements[i][j];
			 }


 }


// sub of two matrix
void sub_matrix(matrix &A, matrix &B , matrix &C)
 {
   if(A.rows !=B.rows || A.columns != B.columns) throw(13);

			 for (int i = 0; i < A.rows; i++)
			 {
				 for (int j = 0; j < A.columns; j++)
					 C.elements[i][j] = A.elements[i][j] - B.elements[i][j];
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
		  for (int j = 0; j < A.columns; j++){
      if(A.elements[i][j]==0) throw(14);
			  C.elements[i][j] = B / A.elements[i][j];
      }
	  }
}

void multiply_matrix(matrix &A, matrix &B , matrix &C)
{

    if (A.columns!=B.rows) throw(15);

    // Multiplying and store in r
     for (int i=0;i<A.rows;i++){
        for (int j=0;j<B.columns;j++){
            for (int k=0;k<A.columns;k++){
                C.elements[i][j] += A.elements[i][k]*B.elements[k][j];
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
    matrix result(rows , m.columns);
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


    matrix result(rows , m.columns);
    if(is_equal((*this) , m))
    result.unity_matrix();


   // else if (m.get_determinant() == 0 || isnan(m.get_determinant()))
    //{
      //  cout << "Error determinant = 0" <<endl;
    //}


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
matrix* mysquareroot(matrix* a)
{
    matrix* result = new matrix (a->rows,a->columns);
    for(int i=0; i< a->rows; i++){
        for(int j=0; j< a->columns; j++){
            if(a->elements[i][j]>=0){
            result->elements[i][j]=sqrt(a->elements[i][j]);
            }
            else {
                throw(19);
      }
    }
  }
  return result;
}



matrix matrix::get_cofactor(int r,int c)
{
    if(rows<=1 || columns<=1) throw(16);
    if(r>rows || c>columns) throw(17);
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
  if(rows != columns) throw(5);
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

    delete temp; // $$$$$$
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


//phase two functions

//function for matrix power int
void power (matrix& a,int n,matrix& result){
    //this must be a square matrix
    if(a.get_rows() != a.get_columns()) throw(18);
    result=a;
    for (int i=1;i<n;i++){
        result=a*result;
    }
}

matrix matrix:: operator ^ (int n){
    matrix result (this->rows , this->columns);
    power(*this,n,result);
    return result;
}

//Function to calculate the power to each element this is for the operator ".^" and can have a fraction power

void power_elements(matrix& a, double n, matrix& result){
    for(int i=0; i<a.rows; i++){
        for(int j=0; j<a.columns; j++){
            result.elements[i][j]=pow(a.elements[i][j],n);
        }

    }
}

matrix* power_by_elements(float num, matrix* input){
  matrix *output = new matrix(input->rows, input->columns);
  for (int i = 0; i < input->rows; i++) {
    for (int j = 0; j < input->columns; j++) {
      output->elements[i][j] = pow(num, input->elements[i][j]);
    }
  }
  return output;
}

//function for to calculate every element square root
void squareroot ( matrix& a, matrix& result){
for(int i=0; i< a.rows; i++){

    for(int j=0; j< a.columns; j++){
      if(a.elements[i][j]>=0){
        result.elements[i][j]=sqrt(a.elements[i][j]);
      }
      else {
        throw(19);
      }
    }
  }
}

//Function for filling the matrix with zeros
matrix zeros(int rows, int columns){
	matrix result(rows,columns);
	for(int i=0; i<rows; i++){
		for(int j=0; j< columns; j++){
			result.elements[i][j]=0;
        }
	}
	return result;
}
//Function for filling the matrix with random no.
matrix random(int rows, int columns){
    matrix result(rows,columns);
	for(int i=0; i<rows; i++){
		for(int j=0; j< columns; j++){
			result.elements[i][j]=(rand()%50);
        }
	}
	return result;

}

//Function for filling the matrix with ones
matrix ones(int rows,int columns){
    matrix result(rows,columns);
	for(int i=0; i<rows; i++){
		for(int j=0; j< columns; j++){
			result.elements[i][j]=1;
        }
	}
    return result;
}

//Function for filling the matrix with zeros
matrix matrix:: zeros(int rows, int columns){
  matrix result(rows,columns);
  for(int i=0; i<rows; i++){
    for(int j=0; j< columns; j++){
      result.elements[i][j]=0;
        }
  }
    return result;
}
//Function for filling the matrix with random no.
matrix matrix:: random(int rows, int columns){
    matrix result(rows,columns);
  for(int i=0; i<rows; i++){
    for(int j=0; j< columns; j++){
      result.elements[i][j]=(rand()%50);
        }
  }
  return result;

}


//Function for filling the matrix with ones

matrix matrix:: ones(int rows,int columns){
    matrix result(rows,columns);
  for(int i=0; i<rows; i++){
    for(int j=0; j< columns; j++){
      result.elements[i][j]=1;
        }
  }
    return result;
}

/*
matrix matrix:: kobry (int r, int c){
return ones(r,c);
}
*/



//trigonometric (MAKE SURE THE INPUT VALUES ARE MEANT TO BE RADIAN) and logarithmic functions

	matrix sin_elements(matrix& a){
    matrix result(a.get_rows(),a.get_columns());
    for(int i=0; i< a.get_rows(); i++){
      for(int j=0; j<a.get_columns(); j++){
        result.elements[i][j]=sin(a.elements[i][j] );

      }
    }
    return result;

  }
	matrix cos_elements(matrix& a){
    matrix result(a.get_rows(),a.get_columns());
    for(int i=0; i< a.get_rows(); i++){
      for(int j=0; j<a.get_columns(); j++){
        result.elements[i][j]=cos(a.elements[i][j] );

      }
    }
    return result;


  }
	matrix tan_elements(matrix& a){
    matrix result(a.get_rows(),a.get_columns());
    for(int i=0; i< a.get_rows(); i++){
      for(int j=0; j<a.get_columns(); j++){
        result.elements[i][j]=tan(a.elements[i][j]);

      }
    }
    return result;


  }

	matrix ln_elements(matrix& a){
    matrix result(a.get_rows(),a.get_columns());
    for(int i=0; i< a.get_rows(); i++){
      for(int j=0; j<a.get_columns(); j++){
        if(a.elements[i][j]<=0) throw(20);
        result.elements[i][j]=log(a.elements[i][j]);

      }
    }
    return result;

  }
	matrix log_elements(matrix& a){
    matrix result(a.get_rows(),a.get_columns());
    for(int i=0; i< a.get_rows(); i++){
      for(int j=0; j<a.get_columns(); j++){
        if(a.elements[i][j]<=0) throw(21);
        result.elements[i][j]=log10(a.elements[i][j]);

      }
    }
    return result;


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
//if (input < 1000000) return 6;
else return 6;
}

void matrix::set_value(float val){
  for (int i = 0; i < this->get_rows(); i++) {
    for (int k = 0; k < this->get_columns(); k++) {
      this->elements[i][k] = val;
    }
  }
}

matrix *add_ver(matrix* input , int num)
{
  int columns = input[0].get_columns();
  int rows = 0;
  for (int i = 0; i < num; i++) {
    rows += input[i].get_rows();
  }
  int indexRow = 0;
  int indexColumn = 0;
  matrix *output = new matrix(rows, columns);
  for (int i = 0; i < num; i++) {
    if(input[i].get_columns() != columns)throw(24);
    output->setSubMatrx(indexRow, indexColumn, &input[i]);
    indexRow += input[i].get_rows();
  }
  return output;
}


matrix *add_horz(matrix* input , int num)
{
  int rows = input[0].get_rows();
  int columns = 0;
  for (int i = 0; i < num; i++) {
    columns += input[i].get_columns();
  }
  int indexRow = 0;
  int indexColumn = 0;
  matrix *output = new matrix(rows, columns);
  for (int i = 0; i < num; i++) {
    if(input[i].get_rows() != rows)throw(24);
    output->setSubMatrx(indexRow, indexColumn, &input[i]);
    indexColumn += input[i].get_columns();
  }
  return output;
}


void matrix::setSubMatrx(int indexRow, int indexColumn, matrix * input){
  for (int i = 0; i < input->get_rows(); i++) {
    for (int j = 0; j < input->get_columns(); j++) {
      this->elements[i + indexRow][j + indexColumn] = input->elements[i][j];
    }
  }
};



matrix * row_factory(string inputString){
  string* vertically_arr;
  inputString = trim(inputString);
  int count = 0;
  int vert_length = 0;
  string temp;
  for (int i = 0; i < inputString.length(); ++i)
  {
    if(inputString[i] == '[' || inputString[i] == '(')count++;
    if(inputString[i] == ']' || inputString[i] == ')')count--;
    if(( (inputString[i] == ' '  || inputString[i] == ',' ) && count == 0)){
      if(i < (inputString.length() - 1)){
        if(inputString[i + 1] == ' ' || inputString[i + 1] == ',' )continue;
      }
      vert_length += 1;
      string* temp_vertically_arr = new string[vert_length];
      for (int k = 0; k < (vert_length - 1); ++k)
      {
        temp_vertically_arr[k] = vertically_arr[k];
      }
      temp_vertically_arr[vert_length - 1] = temp;
      vertically_arr = temp_vertically_arr;
      temp = "";
    }else{
      temp += inputString[i];
    }
  }
  vert_length += 1;
  string* temp_vertically_arr = new string[vert_length];
  for (int k = 0; k < (vert_length - 1); ++k)
  {
    temp_vertically_arr[k] = vertically_arr[k];
  }
  temp_vertically_arr[vert_length - 1] = temp;
  string* tempDelete = vertically_arr;
  vertically_arr = temp_vertically_arr;
  //if (tempDelete)
  //delete[] tempDelete;
  matrix *vertically_arr_matrix = new matrix[vert_length];
  for (int i = 0; i < vert_length; ++i)
  {
    Node* x = do_operation(vertically_arr[i] + ";");
    if(x->type() == 1){
      matrix y(1,1);
      y.set_value( (((FloatNode*)x)->value) );
      vertically_arr_matrix[i] = y;
    }else{
      vertically_arr_matrix[i] = *(((MatrixNode*)x)->value);
      delete x;
    }
  }
  matrix* x =  add_horz(vertically_arr_matrix, vert_length);
  //matrix *x = new matrix();
  for (int i = 0; i < vert_length; i++) {
    //delete &vertically_arr_matrix[i];
  }
  return x;
}

// advanced fill matrix
matrix * matrix:: new_fill_matrix(string inputString)
{
  string* vertically_arr;
  int count = 0;
  int vert_length = 0;
  string temp;
  for (int i = 1; i < inputString.length() - 1; ++i)
  {
    if(inputString[i] == '[')count++;
    if(inputString[i] == ']')count--;
    if((inputString[i] == ';' && count == 0)){
      vert_length += 1;
      string* temp_vertically_arr = new string[vert_length];
      for (int k = 0; k < (vert_length - 1); ++k)
      {
        temp_vertically_arr[k] = vertically_arr[k];
        //delete &vertically_arr[k];
      }
      temp_vertically_arr[vert_length - 1] = temp;
      vertically_arr = temp_vertically_arr;
      temp = "";
    }else{
      temp += inputString[i];
    }
  }
  vert_length += 1;
  string* temp_vertically_arr = new string[vert_length];
  for (int k = 0; k < (vert_length - 1); ++k)
  {
    temp_vertically_arr[k] = vertically_arr[k];
    //delete &vertically_arr[k];
  }
  temp_vertically_arr[vert_length - 1] = temp;
  vertically_arr = temp_vertically_arr;
  matrix *vertically_arr_matrix = new matrix[vert_length];
  for (int i = 0; i < vert_length; ++i)
  {
    vertically_arr_matrix[i] = *row_factory(vertically_arr[i]);
  }
  matrix* x =  add_ver(vertically_arr_matrix, vert_length);
  for (int i = 0; i < vert_length; i++) {
    //delete &vertically_arr_matrix[i];
  }
  return x;
}

matrix matrix::eye(int rows, int columns){
  matrix x(rows, columns);
  if(rows != columns)throw(22);
  for (int i = 0; i < rows; i++) {
    for (int k = 0; k < columns; k++) {
      if(i == k) x.elements[i][k] = 1;
      else x.elements[i][k] = 0;
    }
  }
  return x;
}


 string replace(string right_string)
{
      if(right_string.find('\n')==-1)//recursion base case
        {
           return right_string;
        }

    string left_string="";

      int i=right_string.find('\n')+1;

   left_string=right_string.substr(0,i-1);

        return left_string+";"+replace(right_string.substr(i,right_string.length() - 1));

}

bool braces_num(string s ) {
    bool valid = 0, valid1 = 0, valid2 = 0, valid3 = 0;
    int left1 = 0, right1 = 0, left2 = 0, right2 = 0, left3 = 0, right3 = 0, type1 = 0, type2 = 0, type3 = 0;

        for (int i = 0; i <= s.length(); i++)
            {
                if (s[i]=='(') left1++;
                else if(s[i]==')') right1++;
                else if(s[i]=='[') left2++;
                else if(s[i]==']') right2++;
                else if(s[i]=='{') left3++;
                else if(s[i]=='}') right3++;
            }
        if( right1 == left1) valid1 = 1;
        if( right2 == left2) valid2 = 1;
        if( right3 == left3) valid3 = 1;
        if(valid1 == valid2 == valid3) valid = 1;

    return valid;
}



//-----------------------------------------------------------------------------------------------//load_file
void math_lab:: load_file(string file_path)
  {


    string operation_string="";
    std:: ifstream infile(file_path.c_str());
    if(infile.good() == 0){
        cout << "error : Invalid file directory"<<endl;
        return;
    }
    while(!infile.eof())
        {
        getline(infile,operation_string);
        operation_string.erase(std::remove(operation_string.begin(),operation_string.end(), '\r'), operation_string.end());

        if(operation_string.find('[') != -1)
        {
            while(!(braces_num(operation_string)))
            {
                string temp;
                operation_string+=';';
                getline(infile,temp);
                operation_string+=temp;
            }
            int count = 0;
            bool flag = false;
            string result;
            for (int i = 0; i < operation_string.length(); ++i)
            {
              if(operation_string[i] == '['){
                count++;
                flag = true;
              }else if(operation_string[i] == ']')count--;
              result += operation_string[i];
              if(count == 0 && flag)break;
            }
            operation_string = result;
       }
       operation_string.erase(std::remove(operation_string.begin(),operation_string.end(), '\n'), operation_string.end());
       do_operation(operation_string);
    }
    infile.close();
    return;
  }
//----------------------------------------------------------------------------------------------------//open_commands
void math_lab::open_command()
{
    open_cli();
    return;
}
