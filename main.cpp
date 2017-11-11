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

    m3 = m*m2; //A

   m3.print_matrix();
   cout<<endl<<"determinant : "<<m3.determinant()<<endl;

   matrix m4 = m3.inverse();//B = 1/A

   m4 = m3 * m4; // A*B = A/A

   m4.print_matrix();

   matrix m5 = m3 / m3 /2;// A/A/2

   m5.print_matrix();

   m4 = m3.inverse();// B = 1/A

   m4 = 2*m4;

   m4.print_matrix();

   m4 = 2 / m3;// B = 2/A

   m4.print_matrix();

   // m3.inverse().print_matrix();

   
   // m3.new_sub_matrix(0).print_matrix();
   // cout<<m3.new_sub_matrix(0).determinant()<<endl;
   // m3.new_sub_matrix(1).print_matrix();
   // cout<<m3.new_sub_matrix(1).determinant()<<endl;
   // m3.new_sub_matrix(2).print_matrix();
   // cout<<m3.new_sub_matrix(2).determinant()<<endl;
return 0;
}
