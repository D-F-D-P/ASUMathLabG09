#include "matrix.h"
#include <iostream>
#include <string>



using namespace std;

int main()
{
   //Test code

   string testString = " A = [  2 333 2; 7 10 5; 9 21 7];";
   string test2 = "V = [ 1 33; 4.4  10;  45 21];";

   matrix m;
   m.fill_matrix(testString);
   m.print_matrix();

   matrix m2;
   m2.fill_matrix(test2);
   m2.print_matrix();

   matrix m3;
   multiply_matrix(m,m2,m3);
   m3.print_matrix();

   m3 = m;

   m.destroy_matrix();
   m.print_matrix();
   m3.print_matrix();

//(m+m2).print_matrix(); // this line calls the destructor
//    m3 = m.sum_matrix(m2);
//   m3 = m + m2;
//     m3 += m2;
//m3 = m.sum_matrix(m);
//m.destroy_matrix();
//multiply_matrix(m,m2,m3);
return 0;
}
