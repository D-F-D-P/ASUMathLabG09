<<<<<<< HEAD

=======
>>>>>>> d30dcece09b1dacf0b02def69c19411fececf368
#include <iostream>
#include <string>
#include <fstream>
#include "math_lab.h"
#include "matrix.h"
#include "dynamic_array_matrix.h"
#define MATRIX array_matrix.get_matrix()
using namespace std;
<<<<<<< HEAD




int main()
{
<<<<<<< HEAD
    math_lab our_math_lab;
    our_math_lab.load_file("D:\\projects\\nadertest\\bin\\Debug\\matrix_file.txt");


=======
   //Test code

   string testString = " A = [1.4 2.2 3.2 1;4.4 5.4 6.4 2;3.3 4.2 2 3;1 2 3 4];";
   string test2 = "B = [1.5 4.1 5.4 5;3.1 4.2 1.2 6;3.2 4.3 2.2 7;5 6 7 8];";
   matrix m;
   m.fill_matrix(testString);
  // m.print_matrix();

   matrix m2;
   m2.fill_matrix(test2);



    matrix m3;

    m2.print_matrix();

    m3 = m/m2; //A

   m3.print_matrix();
   // cout<<endl<<"determinant : "<<m3.determinant()<<endl;

   // matrix m4 = m3.inverse();//B = 1/A

   // m4 = m3 * m4; // A*B = A/A

   // m4.print_matrix();

   // matrix m5 = m3 / m3 /2;// A/A/2

   // m5.print_matrix();

   // m4 = m3.inverse();// B = 1/A

   // m4 = 2*m4;

   // m4.print_matrix();

   // m4 = 2 / m3;// B = 2/A

   // m4.print_matrix();
>>>>>>> e3387917dc0ba3e01d1c08f2d5c8e38c508fabcc

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
=======
int main(int argc, char* argv[])
{
  math_lab our_math_lab;


 if(argc>1)
 our_math_lab.load_file(argv[1]);

else

    our_math_lab.open_command();


	return 0;

}
>>>>>>> d30dcece09b1dacf0b02def69c19411fececf368
