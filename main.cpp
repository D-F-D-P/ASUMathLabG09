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
  math_lab our_math_lab;


 if(argc>1)
 our_math_lab.load_file(argv[1]);

<<<<<<< HEAD
else
=======
	getchar();

	return 0;

}
 /* //Test code
   dynamic_array_matrix array_matrix;
   int index=0;
  std::ifstream infile;
	string input_string;
	string* operations;
	infile.open("D:\\projects\\nadertest\\bin\\Debug\\matrix_file.txt");
	while(!infile.eof())
	{
	getline(infile,input_string);
>>>>>>> ecddb00ec3e37d60e9a7c7871f1db1c6b09f586d

    our_math_lab.open_command();


	return 0;

}
