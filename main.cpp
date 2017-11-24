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

else

    our_math_lab.open_command();


	return 0;


}
