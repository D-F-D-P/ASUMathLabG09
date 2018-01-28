#include <limits>
#include "math_lab.h"
#include <cstdlib>
#include <algorithm>
#include "shuffleYard.cpp"
#include <math.h>

using namespace std;

 string replace(string right_string)
{
      if(right_string.find('\n')==-1)//recursion base case
        {
           return right_string;
        }

    string left_string="";

      int i=right_string.find('\n')+1;

   left_string=right_string.substr(0,i-1);

        return left_string+";"+trim_spaces(right_string.substr(i,right_string.length()-1));

}

bool braces_num(string s ) {
    bool valid = 0, valid1 = 0, valid2 = 0, valid3 = 0;
    int left1 = 0, right1 = 0, left2 = 0, right2 = 0, left3 = 0, right3 = 0, type1 = 0, type2 = 0, type3 = 0;

        for (int i = 0; i <= s.length(); i++)
            {
                if (s[i]=='(') left1++;
                else if(s[i]==')') right1++;
                else if(s[i]=='[') left2++;
                else if(s[i]==']') right2++;
                else if(s[i]=='{') left3++;
                else if(s[i]=='}') right3++;
            }
        if( right1 == left1) valid1 = 1;
        if( right2 == left2) valid2 = 1;
        if( right3 == left3) valid3 = 1;
        if(valid1 == valid2 == valid3) valid = 1;

    return valid;
}



//-----------------------------------------------------------------------------------------------//load_file
void math_lab:: load_file(string file_path)
  {
        
        
    string operation_string="";
    std:: ifstream infile(file_path.c_str());   
    while(!infile.eof())
        {
        getline(infile,operation_string);
        operation_string.erase(std::remove(operation_string.begin(),operation_string.end(), '\r'), operation_string.end());
         
        if(operation_string.find('[') != -1)
        {
            while(!(braces_num(operation_string))
            {
                string temp;
                getline(infile,temp);
                operation_string+=temp;

            } 
        operation_string=replace(operation_string);			
       }
       operation_string.erase(std::remove(operation_string.begin(),operation_string.end(), '\n'), operation_string.end());
       do_operation(operation_string);
 
    } 
    infile.close();
    return;
  }
//----------------------------------------------------------------------------------------------------//open_commands
void math_lab::open_command()
{
    open_cli();
    return;
}


