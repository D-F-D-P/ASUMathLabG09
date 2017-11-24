
#include "math_lab.h"
#define MATRIX array_matrix.get_matrix()
using namespace std;

//---------------------------------------------------------------------------------------------//trim spaces & \r
string trim_r(string right_string)
{
      if(right_string.find('\r')==-1)//recursion base case
        {
           return right_string;
        }

    string left_string="";

      int i=right_string.find('\r')+1;

   left_string=right_string.substr(0,i-1);

        return left_string+trim_spaces(right_string.substr(i,right_string.length()-1));

}
// --------------------------------------------------------------------------------------------------------------------------------- //
string trim_n(string right_string)
{
      if(right_string.find('\n')==-1)//recursion base case
        {
           return right_string;
        }

    string left_string="";

      int i=right_string.find('\n')+1;

   left_string=right_string.substr(0,i-1);

        return left_string+trim_spaces(right_string.substr(i,right_string.length()-1));

}
//----------------------------------------------------------------------------------------------//trim spaces fun->public fun
string trim_spaces(string right_string)
{
      if(right_string.find(' ')==-1)//recursion base case
        {
           return right_string;
        }

    string left_string="";

      int i=right_string.find(' ')+1;

   left_string=right_string.substr(0,i-1);

        return left_string+trim_spaces(right_string.substr(i,right_string.length()-1));

}
//-----------------------------------------------------------------------------------------------// decode
void math_lab::decode(string operation)
{
   bool print_=0;
    if(operation[operation.length()-1]==';')
    {
        print_=1;
    }

    string first_operand,second_operand,third_operand;
    int st,nd,th;
    int operator1;
    int x=0;
    for(int i=0;i<operation.length();i++)
    {char a=operation[i];
        if(operation[i]=='=')
        {
            first_operand=operation.substr(0,i);
            x=i+1;
        }
        if(operation[i]=='+'||operation[i]=='-'||operation[i]=='*'||operation[i]=='/'||operation[i]=='\'')
        {
            operator1=i;
            second_operand=operation.substr(x,i-x);

            if(print_==1)
            {
                third_operand=operation.substr(i+1,operation.length()-(i+2));
            }
            else
            {
                third_operand=operation.substr(i+1,operation.length()-(i+1));
            }
            break;
        }
    }
    st= array_matrix.find_matrix(first_operand);
       nd=array_matrix.find_matrix(second_operand);
       th=array_matrix.find_matrix(third_operand);
  // cout<<endl<<second_operand<<third_operand<<first_operand;
    if(operation[operator1]=='+')
    {
       MATRIX[st]=MATRIX[nd]+MATRIX[th];
        if(!print_)
        {
          MATRIX[st].print_matrix();
        }
    }
   else if(operation[operator1]=='-')
    {
        MATRIX[st]=MATRIX[nd]-MATRIX[th];
          if(!print_)
        {
            MATRIX[st].print_matrix();
        }
    }
    else if(operation[operator1]=='*')
    {
        MATRIX[st]=MATRIX[nd]*MATRIX[th];
          if(!print_)
        {
            MATRIX[st].print_matrix();
        }
    }
     else if( operation[operator1]=='/'  && operation[operator1-1]!='.')
    {
            MATRIX[st]=MATRIX[nd]/MATRIX[th];
          if(!print_)
        {
            MATRIX[st].print_matrix();
        }
    }
     else if(operation[operator1]=='\'')
    {
            MATRIX[st]=MATRIX[nd];
            MATRIX[st].flip_matrix();
          if(!print_)
        {
            MATRIX[st].print_matrix();
        }
    }


    else if(operation[operator1-1]=='.')
	{   float number = strtof((second_operand).c_str(),0);
		MATRIX[st] = number / MATRIX[th];
		if(!print_)
        {
            MATRIX[st].print_matrix();
        }
	}

    else
	{
		cout<<"invalid operator"<<endl;
		  return;
	}

    return;
}
//-----------------------------------------------------------------------------------------------//load_file
void math_lab:: load_file(string file_path)
  {
        array_matrix.set_size(10);

       // std::ifstream infile;
        string data_string;
        string operation_string;
        //infile.open(file_path);
	std:: ifstream infile(file_path.c_str());
        while(!infile.eof())
	//while(getline(infile,data_string))
        {
        getline(infile,data_string);


        if(data_string.find('[') != -1)
        {

           MATRIX[array_matrix.valid_size].fill_matrix(data_string);
            array_matrix.valid_size++;
            if (array_matrix.valid_size==array_matrix.get_size())
            {
                array_matrix.set_size(array_matrix.valid_size+5);
            }
        }
        else
        {
                        operation_string=trim_spaces(data_string);
			operation_string=trim_r(operation_string);
if(operation_string=="")
continue;

	    //operation_string=trim_n(operation_string);
            //cout<<operation_string;
            decode(operation_string);


        }

        }
        infile.close();
    return;
  }
//----------------------------------------------------------------------------------------------------//open_commands
void math_lab::open_command()
{
    string data_string;
    string operation_string;

    while(1)
    {
        getline(cin,data_string);
        if(data_string.find('[') != -1)
        {
            MATRIX[array_matrix.valid_size].fill_matrix(data_string);
            array_matrix.valid_size++;
             if (array_matrix.valid_size==array_matrix.get_size())
            {
                array_matrix.set_size(array_matrix.valid_size+5);
            }
        }
        else
        {
            operation_string=trim_spaces(data_string);
            operation_string=trim_r(operation_string);
if(operation_string=="")
continue;
            decode(operation_string);

        }
    }
    return;
}







