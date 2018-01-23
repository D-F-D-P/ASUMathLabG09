#include <iostream>
#include <string>
#include <fstream>
#include "math_lab.h"
#include "matrix.h"
#include "dynamic_array_matrix.h"
#define MATRIX array_matrix.get_matrix()


using namespace std;


int main(int argc, char* argv[])
{
try{
 math_lab our_math_lab;

 if(argc>1)
  our_math_lab.load_file(argv[1]);

 else
  our_math_lab.open_command();
  
}
catch(int error){

  if(error==0) cout<<"error input: rows or columns is a negative value, program terminated."<<endl;
  if(error==1) cout<<"error input: matrix element is not a valid input, expected double."<<endl;
  if(error==2) cout<<"error input: fill matrix error, conflict in columns number."<<endl;
  if(error==3) cout<<"error: calling matrix has 0 rows or 0 columns ,sub matrix can't be created."<<endl;
  if(error==4) cout<<"error input: required sub matrix is larger than calling matrix"<<endl;
  if(error==5) cout<<"error:not square matrix, determinant can't be evaluated."<<endl;
  if(error==6) cout<<"error:not square matrix ,inverse can't be evaluated."<<endl;
  if(error==7) cout<<"error:zero denominator"<<endl;
  if(error==8) cout<<"error input: not square matrix unity matrix can't be created."<<endl;
  if(error==9) cout<<"error input: rows or columns =0 unity matrix can't be created."<<endl;
}

	return 0;

}


