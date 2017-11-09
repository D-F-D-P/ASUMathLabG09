#include "matrix.h"
#include <iostream>
#include <string>



using namespace std;

int main()
{
   //Test code

   string testString = " A = [2 3 1;3 7 10;4 9 5];";
   string test2 = "B = [1 7 21; 4.4 5 10; 1 5 1]";

   matrix m;
   m.fill_matrix(testString);
  // m.print_matrix();

   matrix m2;
   m2.fill_matrix(test2);


    matrix m3;

    m3 = m*m2;



   m3.print_matrix();

return 0;
}
