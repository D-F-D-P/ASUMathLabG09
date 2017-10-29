#include "matrix.h"
#include <iostream>
#include <string>



using namespace std;

int main()
{
   //Test code
   string testString = "    A = [  1.4 2 333 2; 4.4 7 10 5; 9 45 21 7];";
   matrix m;
   m.fill_matrix(testString);
   m.print_matrix();
	 return 0;
}
