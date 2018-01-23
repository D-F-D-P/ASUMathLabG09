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

  if(error==0) cout<<"error: rows or columns is a negative value."<<endl;
  else if(error==1) cout<<"error: matrix element is not a valid input, expected double."<<endl;
  else if(error==2) cout<<"error: fill matrix error, conflict in columns number."<<endl;
  else if(error==3) cout<<"error: calling matrix has 0 rows or columns, sub matrix can't be created."<<endl;
  else if(error==4) cout<<"error: required sub matrix is larger than calling matrix."<<endl;
  else if(error==5) cout<<"error: not square matrix, determinant can't be evaluated."<<endl;
  else if(error==6) cout<<"error: not square matrix, inverse can't be evaluated."<<endl;
  else if(error==7) cout<<"error: zero denominator, infinity output, inverse can't be evaluated."<<endl;
  else if(error==8) cout<<"error: not square matrix, unity matrix can't be created."<<endl;
  else if(error==9) cout<<"error: rows or columns=0, unity matrix can't be created."<<endl;
  else if(error==10)cout<<"error: B is not a square matrix, division output can't be evaluated."<<endl;
  else if(error==11)cout<<"error: A and B matrices mismatch, division output can't be evaluated."<<endl;
  else if(error==12)cout<<"error: matrices mismatch, sum output can't be evaluated."<<endl;
  else if(error==13)cout<<"error: matrices mismatch, sub output can't be evaluated."<<endl;
  else if(error==14)cout<<"error: div_num division output infinity."<<endl;
  else if(error==15)cout<<"error: matrices mismatch, multiplication output can't be evaluated."<<endl;
  else if(error==16)cout<<"error: cofactor caller matrix has invalid matrix dimension."<<endl;
  else if(error==17)cout<<"error: cofactor input error."<<endl;
  else if(error==18)cout<<"error: not square matrix, power output can't be evaluated."<<endl;
  else if(error==19)cout<<"error: root square of a negative number, complex output not supported."<<endl;
  else if(error==20)cout<<"error: matrix element less than or equal zero, ln() can't be evaluated."<<endl;
  else if(error==21)cout<<"error: matrix element less than or equal zero, log() can't be evaluated."<<endl;
}

	return 0;

}
