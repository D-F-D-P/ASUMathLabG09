#pragma once
#include <string>
using namespace std;
class our_string : public string
{
public:
	//our_string Trim(char a);
	//bool Is_it_num(our_string input, double &num);
	//int find_str(our_string a, int &how_many,int start);
	//int find_2str(our_string a, our_string b,int start);
	
	string trim(string right_string,char c);
	int find_str (string input ,char a,int& howmany,int start);
	int find_2str(string input,char a,char b,int start);
	bool is_number (string c , double & number );
};
