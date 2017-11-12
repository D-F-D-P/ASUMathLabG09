
#include <iostream>
#include <string>
#include <fstream>
#include "math_lab.h"
#include "matrix.h"
#include "dynamic_array_matrix.h"
#define MATRIX array_matrix.get_matrix()
using namespace std;




int main()
{
    math_lab our_math_lab;
    our_math_lab.load_file("D:\\projects\\nadertest\\bin\\Debug\\matrix_file.txt");



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


    if(input_string.find('[') != -1)
    {
       MATRIX[index].fill_matrix(input_string);
        index++;
    }

    else
        {
         //   operations = decode(input_string);

        }
	}
	MATRIX[2]=MATRIX[0]+MATRIX[1];
	 array_matrix.print();*/
