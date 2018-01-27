#include "our_string.h"
using namespace std;

//trim char
string our_string:: trim(string right_string,char c)
{
	if(right_string.find(c)==-1)
        {
           return right_string;
        }
    string left_string="";

      int i=right_string.find(c)+1;

   left_string=right_string.substr(0,i-1);

        return left_string+trim(right_string.substr(i,right_string.length()-1),c);

}

//if number return 1
bool our_string :: is_number (string c , double & number ){
    for(int i=0; i<c.length() ; i++){
        if((int(c[i])>=48 && int(c[i])<=57)|| int(c[i])==46)
            continue;
        else return 0;
        }
    number=atof(c.c_str());;
    return 1;
}

//find one char
int our_string::  find_str (string input ,char a,int& howmany,int start)
{
    howmany=0;
    int x=0;
    int index;
    for(int i=start;i<input.length();i++)
    {
        if (input[i]==a)
        {
            howmany ++;
            x++;
        }
        if(x==1)
        {
            index=i;
            x++;
        }
    }
    if (howmany==0){
        return -1;
    }

    return index;
}

//find two chars
int our_string ::  find_2str (string input,char a,char b,int start){
    for (int i=start;i<input.length();i++){
        if(input[i]==a || input[i]==b){
            return i;
        }
    }
        return -1;
}
