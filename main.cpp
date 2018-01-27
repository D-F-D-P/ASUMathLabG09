#include <iostream>
#include <string>
#include <fstream>
#include "math_lab.h"
#include "matrix.h"


using namespace std;


int main(int argc, char* argv[])
{

    math_lab our_math_lab;

   if(argc>1)
    our_math_lab.load_file(argv[1]);

   else
   our_math_lab.open_command();


//the try & catch  in the shuffleYard file
	return 0;

}


