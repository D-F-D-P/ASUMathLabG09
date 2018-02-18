#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include <string>
#include "AVL.cpp"

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

#define PI 3.14159265


string trimx(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void sighandler(int signum)
{
    //printf("Process %d got signal %d\n", getpid(), signum);
    throw "----------------- INVALID NUMBER OF OPERATORS -------------------";
}

class vars
{
    pair <string ,float> *value;
    int size;
	public:
    vars(){
        value = NULL;
        size = 0;
    }
    void print(){
        for (int i = 0 ; i < size ; i++)
            cout << value[i].first << " = " << value[i].second << endl;
    }
    void add(string name, float f){
	    pair <string ,float> *temp = value;
	    size++;
	    value = new pair <string,float>[size];
	    if (temp)
	    {

	        for (int i = 0 ; i < size-1 ; i++)
	            value [i] = temp [i];
	            delete[]temp;
	    }
	    value[size-1].first = name;
	    value[size-1].second= f;
    }
    float* search(string name)
    {
        for (int i = 0 ; i < size ; i++)
        {
            if (value[i].first == name)
                return &value[i].second;
        }
        return NULL;
    }

};



AVL matrixTree;
vars varasTree;

class Node
{
	public:
	Node *child;
	virtual int type() = 0;
};

class CharNode : public Node
{
	public:
	char value;
	int type()
	{
		return 0;
	}
	CharNode(char value)
	{
		this->value = value;
	}
};

class FloatNode : public Node
{
	public:
	float value;
	string name;
	int type()
	{
		return 1;
	}
	FloatNode(float value)
	{
		this->value = value;
	}
	FloatNode(float value, string name)
	{
		this->value = value;
		this->name = name;
	}

};

class MatrixNode : public Node
{
	public:
	matrix* value;
	bool important;
	int type()
	{
		return 2;
	}
	MatrixNode(matrix *value)
	{
		this->value = value;
		this->important = false;
	}
	MatrixNode(matrix *value, bool important)
	{
		this->value = value;
		this->important = important;
	}
	~MatrixNode()
	{
		if(!important)delete value;
	}
};

class TempMatrixNode : public Node
{
	public:
	matrix* value;
	bool important;
	int type()
	{
		return 3;
	}
	TempMatrixNode(matrix *value)
	{
		this->value = value;
		this->important = false;
	}
	TempMatrixNode(matrix *value, bool important)
	{
		this->value = value;
		this->important = important;
	}
	~TempMatrixNode()
	{
		if(!important)delete value;
	}
};

Node* do_operation(string str);

int get_operator_order(char cur)
{
	if(cur == '=')return 1;
	if(cur == '+' || cur == '-')return 2;
	// " for ./
	if(cur == '*' || cur == '/' || cur == '"')return 3;
	//minus operator
	if(cur == '%')return 4;
  //transpose operator
  if(cur == '|')return 5;
	//power operators .^
	if(cur == '^' || cur == '#')return 6;
	//sin operator
	//cos operator
	//tan operator
	//log operator
	//ln operator
	if(cur == '<' || cur == '!' || cur == '_' || cur == '~'|| cur == '\\')return 7;
	// rand(4,4)
  //eye()
	// zeros(2, 3)
	// ones(3, 6)
	// sqrt()
	if(cur == '@' || cur == '&' || cur == '?' || cur == ':' || cur == '`')return 8;
	//print operator
	if(cur == '>')return 9;
	if(cur == '(')return 0;
	if(cur == ')')return 0;
};

bool is_higher_order_than(char cur, CharNode* node)
{
	if(node->value == '(' && cur == ')')return true;
	//minus operator
	if(node->value == '%' && cur == '%')return true;
	if(get_operator_order(cur) > get_operator_order(node->value))
	{
		return true;
	}
	return false;
};

template <class T>
class Stack
{
	public:
	T *top;
	Stack()
	{
		this->top = NULL;
	}
	void add(T *node)
	{
		node->child = this->top;
		this->top = node;
	}
	T* pop()
	{
		T * temp = this->top;
		this->top = this->top->child;
		return temp;
	}
	void print()
	{
		T *current = this->top;
		while(current != NULL)
		{
			switch(current->type())
			{
				case 2:
					//((MatrixNode*)(current))->value->print_matrix();
					break;
				case 1:
					cout<<((FloatNode*)(current))->value<<endl;
					break;
				case 0:
					cout<<((CharNode*)(current))->value<<endl;
					break;
			}
			if(current->type() == 2)
			{
				cout<<((FloatNode*)(current))->value<<endl;
			}else {
				cout<<((CharNode*)(current))->value<<endl;
			}
			current = current->child;
		}
	}
};

char* infix_to_reverse_polish(char *infix)
{
	int countAll = 0, countVirtual = 0;
	for (int i = 0; infix[i] != '\0'; ++i)
	{
		if(infix[i] == '[')
		{
			while(infix[i] != ']')
			{
				countAll++;
				i++;
			}
			countVirtual+=2;
			countAll++;
		}
		else if(infix[i] != ' ')
		{
			countAll++;
			if(infix[i] == '.' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^' || infix[i] == '+' || infix[i] == '-' || infix[i] == '(' || infix[i] == ')' || infix[i] == ']' || infix[i] == '[' || infix[i] == '=')
			{
				countVirtual++;
			}
		}
	}
	char *temp = new char[countAll + countVirtual + 1];
	Stack<Node>* temp_stack = new Stack<Node>();
	int j = 0;
	bool flag = true, flagNegative = false;
	for (int i = 0; infix[i] != '\0'; ++i)
	{
		if(infix[i] != ' ')
		{
			//./ operation
			if(infix[i] == '.' && infix[i+1] == '/'){
				i += 1;
				flag = false;
				CharNode *x = new CharNode('"');
				temp_stack->add(x);
				flagNegative = true;
			}
			// .^ operation
			else if(infix[i] == '.' && infix[i+1] == '^'){
				i += 1;
				flag = false;
				CharNode *x = new CharNode('#');
				temp_stack->add(x);
				flagNegative = true;
			}
			else if(infix[i] == '.' && infix[i+1] == '+'){
				flag = false;
			}
      //transpose operator
      else if(infix[i] == '\''){
				flag = false;
				CharNode *x = new CharNode('|');
				temp_stack->add(x);
				flagNegative = true;
      }
			//sin operation
			else if(infix[i] == 's' && infix[i+1] == 'i' && infix[i+2] == 'n' && infix[i+3] == '('){
				i += 2;
				flag = false;
				CharNode *x = new CharNode('<');
				temp_stack->add(x);
			}
			//cos operation
			else if(infix[i] == 'c' && infix[i+1] == 'o' && infix[i+2] == 's' && infix[i+3] == '('){
				i += 2;
				flag = false;
				CharNode *x = new CharNode('!');
				temp_stack->add(x);
			}
			//tan operation
			else if(infix[i] == 't' && infix[i+1] == 'a' && infix[i+2] == 'n' && infix[i+3] == '('){
				i += 2;
				flag = false;
				CharNode *x = new CharNode('_');
				temp_stack->add(x);
			}
			//log operation
			else if(infix[i] == 'l' && infix[i+1] == 'o' && infix[i+2] == 'g' && infix[i+3] == '('){
				i += 2;
				flag = false;
				CharNode *x = new CharNode('~');
				temp_stack->add(x);
			}
			//ln operation
			else if(infix[i] == 'l' && infix[i+1] == 'n' && infix[i+2] == '('){
				i += 1;
				flag = false;
				CharNode *x = new CharNode('\\');
				temp_stack->add(x);
			}
			//sqrt operation
			else if(infix[i] == 's' && infix[i+1] == 'q' && infix[i+2] == 'r' && infix[i+3] == 't' && infix[i+4] == '('){
				i += 3;
				flag = false;
				CharNode *x = new CharNode('`');
				temp_stack->add(x);
			}
			//rand operation
			else if(infix[i] == 'r' && infix[i+1] == 'a' && infix[i+2] == 'n' && infix[i+3] == 'd' && infix[i+4] == '('){
				i += 5;
				flag = false;
				temp[j] = '@';
				j++;
				int bracketCount = 1;
				while(true)
				{
					if(infix[i] == '(')bracketCount++;
					if(infix[i] == ')')bracketCount--;
					if(bracketCount == 0)break;
					temp[j] = infix[i];
					i++;
					j++;
				}
				temp[j] = '@';
				j++;
				flagNegative = true;
			}
      //eye operation
			else if(infix[i] == 'e' && infix[i+1] == 'y' && infix[i+2] == 'e' && infix[i+3] == '('){
				i += 4;
				flag = false;
				temp[j] = '&';
				j++;
				int bracketCount = 1;
				while(true)
				{
					if(infix[i] == '(')bracketCount++;
					if(infix[i] == ')')bracketCount--;
					if(bracketCount == 0)break;
					temp[j] = infix[i];
					i++;
					j++;
				}
				temp[j] = '&';
				j++;
				flagNegative = true;
			}
			//zeros operation
			else if(infix[i] == 'z' && infix[i+1] == 'e' && infix[i+2] == 'r' && infix[i+3] == 'o' && infix[i+4] == 's' && infix[i+5] == '('){
				i += 6;
				flag = false;
				temp[j] = '?';
				j++;
				int bracketCount = 1;
				while(true)
				{
					if(infix[i] == '(')bracketCount++;
					if(infix[i] == ')')bracketCount--;
					if(bracketCount == 0)break;
					temp[j] = infix[i];
					i++;
					j++;
				}
				temp[j] = '?';
				j++;
				flagNegative = true;
			}
			//ones operation
			else if(infix[i] == 'o' && infix[i+1] == 'n' && infix[i+2] == 'e' && infix[i+3] == 's' && infix[i+4] == '('){
				i += 5;
				flag = false;
				temp[j] = ':';
				j++;
				int bracketCount = 1;
				while(true)
				{
					if(infix[i] == '(')bracketCount++;
					if(infix[i] == ')')bracketCount--;
					if(bracketCount == 0)break;
					temp[j] = infix[i];
					i++;
					j++;
				}
				temp[j] = ':';
				j++;
				flagNegative = true;
			}
      else if(infix[i] == '[')
      {
        int countxx = 0;
        while (true) {
          if(infix[i] == '[')countxx++;
          if(infix[i] == ']')countxx--;
          if(countxx == 0){
            temp[j] = infix[i];
  					i++;
  					j++;
            break;
          }else{
            temp[j] = infix[i];
            i++;
            j++;
          }
        }
        i--;
				flagNegative = true;
			}
			else if(infix[i] == ';'){
				bool equal_flag = false;
				while(temp_stack->top != NULL)
				{
					if(((CharNode*)(temp_stack->top))->value == '='){
						equal_flag = true;
						temp[j] = '>';
						j++;
					}
					CharNode *x = (CharNode*)temp_stack->pop();
					temp[j] = x->value;
					j++;
					delete x;
				}
				flag = false;
				//print
				if(!equal_flag){
					temp[j] = '>';
					j++;
				}
				flagNegative = false;
			}
			else if( infix[i] == '*' || infix[i] == '/' || infix[i] == '^' || infix[i] == '+' || infix[i] == '-' || infix[i] == '(' || infix[i] == ')' || infix[i] == '%' || infix[i] == '=')
			{
				if(infix[i] == '-' && !flagNegative)infix[i]= '%';
				if(temp_stack->top != NULL)
				{
					//flagNegative = false;
					if((infix[i] == '(' || is_higher_order_than(infix[i], (CharNode*)temp_stack->top))&& infix[i] != ')'){
						flag = false;
						CharNode *x = new CharNode(infix[i]);
						flagNegative = false;
						temp_stack->add(x);
					}else{
						flag = false;
						if(infix[i] == ')')flagNegative = true;
						CharNode *x = (CharNode*)temp_stack->pop();
						if(x->value != '(')
						{
							temp[j] = x->value;
							j++;
							i--;
						}
						delete x;
					}
				}else{
					flag = false;
					CharNode *x = new CharNode(infix[i]);
					flagNegative = false;
					temp_stack->add(x);
				}
			}else{
				if(!flag)
				{
					temp[j] = ';';
					j++;
				}
				temp[j] = infix[i];
				j++;
				flag = true;
				flagNegative = true;
			}
		}
	}
	while(temp_stack->top != NULL){
		CharNode *x = (CharNode*)temp_stack->pop();
		temp[j] = x->value;
		j++;
	}

	temp[j] = '\0';

	return temp;
}

Node* reverse_polish_to_float(char *reverse_polish)
{
	Stack<Node>* temp_stack = new Stack<Node>();
	bool echo_flag = true;
	for (int i = 0; reverse_polish[i] != '\0'; ++i)
	{
		if(reverse_polish[i] == ';');
		else if(reverse_polish[i] == '='){
			Node *right = temp_stack->pop();
			Node *left = temp_stack->pop();
			if(right->type() == 3){
				throw "--------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)right)->value)->name + "\" AFTER \"" + "=" + "\" ----------------";
			}
			if(right->type() == 1){
				if(left->type() == 2){
					throw "-- CAN NOT CONVERT FLOAT VALUE TO A MATRIX TYPE VARIABLE \"" + (((MatrixNode*)left)->value)->get_name() + "\" ---";
				}else if(left->type() == 3){
					varasTree.add((((MatrixNode*)left)->value)->get_name(), (((FloatNode*)right)->value));
					if(echo_flag){
						cout<<(((FloatNode*)right)->value)<<endl;
					}
					((MatrixNode*)left)->important = false;
				}else{
					float*x = varasTree.search((((FloatNode*)left)->name));
					*x = (((FloatNode*)right)->value);
					if(echo_flag){
						cout<<(((FloatNode*)right)->value)<<endl;
					}
				}
			}else{
				if(left->type() == 1){
					throw "---- CAN NOT CONVERT MATRIX TO A FLOAT TYPE VARIABLE \"" + (((FloatNode*)left)->name) + "\" --------";
				}
				*(((MatrixNode*)left)->value) = *(((MatrixNode*)right)->value);
				if(echo_flag){
					(((MatrixNode*)left)->value)->print_matrix();
					cout<<endl;
				}
				if(left->type() == 3){
          matrixTree.insert((((MatrixNode*)left)->value));
          ((MatrixNode*)left)->important = false;
        }
			}
			echo_flag = true;
			delete left;
			delete right;
		}
    else if(reverse_polish[i] == '[')
		{
      string temp_string = "";
      int countx = 0;
      while (true) {
        if(reverse_polish[i] == '[')countx++;
        if(reverse_polish[i] == ']')countx--;
        temp_string += reverse_polish[i];
        if(countx == 0)break;
        i++;
      }
			matrix *tempMatrix = new matrix;
			Node *tempNode = new MatrixNode(tempMatrix->new_fill_matrix(temp_string));
			/*temp value*/
			temp_stack->add(tempNode);
		}
    else if(reverse_polish[i] == '|'){
      Node *left = temp_stack->pop();
      Node *tempNode;
      if(left->type() == 3){
        throw "---------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" BEFORE \"" + '\'' + "\" ---------------";
      }
      if(left->type() == 1)
      {
        throw "---- EXPECT THE OPERAND OF ' TO BE MATRIX BUT FLOAT WAS GIVEN ----";
      }else{
        matrix *tempMatrix = new matrix;
        *tempMatrix = *(((MatrixNode*)left)->value);
        tempMatrix->flip_matrix();
        tempNode = new MatrixNode(tempMatrix);
      }
      /*temp value*/
      temp_stack->add(tempNode);
      delete left;
    }
    //rand operation
		else if(reverse_polish[i] == '@')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				if(reverse_polish[k] == '@'){
					throw "---- THE FUNCTION RAND TAKES TWO PARAMETERS BUT ONE WAS FIVEN ----";
				}
				count++;
			}
			char *temp_string = new char[count + 2];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      i--;
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *left = do_operation(temp_string);
			if(left->type() == 2)
			{
				throw "---- EXPECT 1ST ARG. OF RAND TO BE FLOAT BUT MATRIX WAS FOUND ----";
			}
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != '@'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 2];
			j = 0;
			i++;
			while(reverse_polish[i] != '@')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *right = do_operation(temp_string);
			if(right->type() == 2)
			{
				throw "---- EXPECT 2ND ARG. OF RAND TO BE FLOAT BUT MATRIX WAS FOUND ----";
			}
			//calculations part
			Node *tempNode;
			matrix* y = new matrix;
			{
				matrix x;
				*y = x.random((int)(((FloatNode*)left)->value), (int)(((FloatNode*)right)->value));
			}
			tempNode = new MatrixNode(y);
			temp_stack->add(tempNode);
			delete left;
			delete right;
		}
    //eye operation
		else if(reverse_polish[i] == '&')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				if(reverse_polish[k] == '&'){
					throw "---- THE FUNCTION EYE TAKES TWO PARAMETERS BUT ONE WAS FIVEN ----";
				}
				count++;
			}
			char *temp_string = new char[count + 2];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      i--;
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *left = do_operation(temp_string);
			if(left->type() == 2)
			{
				throw "---- EXPECT 1ST ARG. OF EYE TO BE FLOAT BUT MATRIX WAS FOUND ----";
			}
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != '&'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 2];
			j = 0;
			i++;
			while(reverse_polish[i] != '&')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *right = do_operation(temp_string);
			if(right->type() == 2)
			{
				throw "---- EXPECT 2ND ARG. OF EYE TO BE FLOAT BUT MATRIX WAS FOUND ----";
			}
			//calculations part
			Node *tempNode;
			matrix* y = new matrix;
			{
				matrix x;
				*y = x.eye((int)(((FloatNode*)left)->value), (int)(((FloatNode*)right)->value));
			}
			tempNode = new MatrixNode(y);
			temp_stack->add(tempNode);
			delete left;
			delete right;
		}
		//zeros operation
		else if(reverse_polish[i] == '?')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				if(reverse_polish[k] == '?'){
					throw "---- THE FUNCTION ZEROS TAKES TWO PARAMETERS BUT ONE WAS FIVEN ---";
				}
				count++;
			}
			char *temp_string = new char[count + 2];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      i--;
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *left = do_operation(temp_string);
			if(left->type() == 2)
			{
				throw "--- EXPECT 1ST ARG. OF ZEROS TO BE FLOAT BUT MATRIX WAS FOUND ---";
			}
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != '?'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 2];
			j = 0;
			i++;
			while(reverse_polish[i] != '?')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *right = do_operation(temp_string);
			if(right->type() == 2)
			{
				throw "--- EXPECT 2ND ARG. OF ZEROS TO BE FLOAT BUT MATRIX WAS FOUND ---";
			}
			//calculations part
			Node *tempNode;
			matrix* y = new matrix;
			{
				matrix x;
				*y = x.zeros((int)(((FloatNode*)left)->value), (int)(((FloatNode*)right)->value));
			}
			tempNode = new MatrixNode(y);
			temp_stack->add(tempNode);
			delete left;
			delete right;
		}
		//ones operation
		else if(reverse_polish[i] == ':')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				if(reverse_polish[k] == ':'){
					throw "---- THE FUNCTION ones TAKES TWO PARAMETERS BUT ONE WAS FIVEN ----";
				}
				count++;
			}
			char *temp_string = new char[count + 2];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      i--;
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *left = do_operation(temp_string);
			if(left->type() == 2)
			{
				throw "---- EXPECT 1ST ARG. OF ONES TO BE FLOAT BUT MATRIX WAS FOUND ---";
			}
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != ':'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 2];
			j = 0;
			i++;
			while(reverse_polish[i] != ':')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
      temp_string[count] = ';';
			temp_string[count + 1]='\0';
			Node *right = do_operation(temp_string);
			if(right->type() == 2)
			{
				throw "---- EXPECT 2ND ARG. OF ONES TO BE FLOAT BUT MATRIX WAS FOUND ---";
			}
			//calculations part
			Node *tempNode;
			matrix* y = new matrix;
			{
				matrix x;
				*y = x.ones((int)(((FloatNode*)left)->value), (int)(((FloatNode*)right)->value));
			}
			tempNode = new MatrixNode(y);
			temp_stack->add(tempNode);
			delete left;
			delete right;
		}
		//sin operator
		else if(reverse_polish[i] == '<')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "-------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" INSIDE \"" + "sin" + "\" --------------";
			}
			if(left->type() == 1)
			{
				tempNode = new FloatNode(sin ( ((FloatNode*)(left))->value) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = sin_elements(*(((MatrixNode*)left)->value));
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//cos operator
		else if(reverse_polish[i] == '!')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "-------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" INSIDE \"" + "cos" + "\" --------------";
			}
			if(left->type() == 1)
			{
				tempNode = new FloatNode(cos ( ((FloatNode*)(left))->value ) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = cos_elements(*(((MatrixNode*)left)->value));
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//tan operator
		else if(reverse_polish[i] == '_')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "-------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" INSIDE \"" + "tan" + "\" --------------";
			}
			if(left->type() == 1)
			{
				tempNode = new FloatNode(tan ( ((FloatNode*)(left))->value) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = tan_elements(*(((MatrixNode*)left)->value));
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//log operator
		else if(reverse_polish[i] == '~')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "-------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" INSIDE \"" + "log" + "\" --------------";
			}
			if(left->type() == 1)
			{
				tempNode = new FloatNode(log10 ( ((FloatNode*)(left))->value) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = log_elements(*(((MatrixNode*)left)->value));
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//ln operator
		else if(reverse_polish[i] == '\\')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "-------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" INSIDE \"" + "ln" + "\" ---------------";
			}
			if(left->type() == 1)
			{
				tempNode = new FloatNode(log ( ((FloatNode*)(left))->value) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = ln_elements(*(((MatrixNode*)left)->value));
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//sqrt operator
		else if(reverse_polish[i] == '`')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "-------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" INSIDE \"" + "sqrt" + "\" -------------";
			}
			if(left->type() == 1)
			{
			    if(( ((FloatNode*)(left))->value )  < 0)throw(19);
				tempNode = new FloatNode(sqrt ( ((FloatNode*)(left))->value ) );
			}else{
				matrix* y = mysquareroot((((MatrixNode*)left)->value));
				tempNode = new MatrixNode(y);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//print operator
		else if(reverse_polish[i] == '>')
		{
				echo_flag = false;
		}
		//mius operator
		else if(reverse_polish[i] == '%')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
			if(left->type() == 3){
				throw "---------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" AFTER \"" + '-' + "\" ---------------";
			}
			if(left->type() == 1)
			{
				tempNode = new FloatNode(((FloatNode*)(left))->value * -1);
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = ( *(((MatrixNode*)left)->value) * -1);
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		else if(reverse_polish[i] == '*' || reverse_polish[i] == '/' || reverse_polish[i] == '^' || reverse_polish[i] == '+' || reverse_polish[i] == '-' || reverse_polish[i] == '"' || reverse_polish[i] == '#')
		{
			Node *right = temp_stack->pop();
			Node *left = temp_stack->pop();
			if(left->type() == 3){
				throw "----------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" BEFORE " + reverse_polish[i] + " ---------------";
			}else if(right->type() == 3){
				throw "----------------- UNDEFINED VARIABLE \"" + (((TempMatrixNode*)right)->value)->name + "\" AFTER " + reverse_polish[i] + " ----------------";
			}
			Node *tempNode = NULL;
			switch(reverse_polish[i]){
				case '+':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
							tempNode = new FloatNode(( (((FloatNode*)left)->value) + (((FloatNode*)right)->value) ));
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( (((FloatNode*)left)->value) + *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) + (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) + *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}
					/*temp values*/
					break;
				case '-':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
							tempNode = new FloatNode(( (((FloatNode*)left)->value) - (((FloatNode*)right)->value) ));
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( (((FloatNode*)left)->value) - *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) - (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) - *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}
					/*temp values*/
					break;
				case '*':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
							tempNode = new FloatNode(( (((FloatNode*)left)->value) * (((FloatNode*)right)->value) ));
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( (((FloatNode*)left)->value) * *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) * (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) * *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}
					/*temp values*/
					break;
				case '/':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
						    if((((FloatNode*)right)->value) == 0)throw(25);
							tempNode = new FloatNode(( (((FloatNode*)left)->value) / (((FloatNode*)right)->value) ));
						}else{
							// matrix *tempMatrix = new matrix;
							// *tempMatrix = ( (((FloatNode*)left)->value) / *(((MatrixNode*)right)->value) );
							// tempNode = new MatrixNode(tempMatrix);
							throw "---- EXPECT 2ND OPERAND OF / TO BE FLOAT BUT MATRIX WAS FOUND ----";
						}
					}else{
						if(right->type() == 1)
						{
							// matrix *tempMatrix = new matrix;
							// *tempMatrix = ( *(((MatrixNode*)left)->value) / (((FloatNode*)right)->value) );
							// tempNode = new MatrixNode(tempMatrix);
							throw "---- EXPECT 2ND OPERAND OF / TO BE MATRIX BUT FLOAT WAS FOUND ----";
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) / *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}
					/*temp values*/
					break;
				case '"':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
							//tempNode = new FloatNode(( (((FloatNode*)left)->value) / (((FloatNode*)right)->value) ));
							throw "---- EXPECT 2ND OPERAND OF ./ TO BE MATRIX BUT FLOAT WAS FOUND ---";
						}else{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( (((FloatNode*)left)->value) / *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) / (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							matrix *tempMatrix = matrix_divide_elements( *(((MatrixNode*)left)->value), *(((MatrixNode*)right)->value) );
                            tempNode = new MatrixNode(tempMatrix);
							//throw "---- EXPECT 2ND OPERAND OF ./ TO BE FLOAT BUT MATRIX WAS FOUND ----";
						}
					}
					/*temp values*/
					break;
				case '^':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
							tempNode = new FloatNode(pow( (((FloatNode*)left)->value), (((FloatNode*)right)->value) ));
						}else{
							// matrix *tempMatrix = new matrix;
							// *tempMatrix = ( (((FloatNode*)left)->value) / *(((MatrixNode*)right)->value) );
							// tempNode = new MatrixNode(tempMatrix);
							throw "---- EXPECT 2ND OPERAND OF ^ TO BE FLOAT BUT MATRIX WAS FOUND ----";
						}
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) ^ (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							// matrix *tempMatrix = new matrix;
							// *tempMatrix = ( *(((MatrixNode*)left)->value) ^ *(((MatrixNode*)right)->value) );
							// tempNode = new MatrixNode(tempMatrix);
							throw "---- EXPECT 2ND OPERAND OF ^ TO BE FLOAT BUT MATRIX WAS FOUND ----";
						}
					}
					/*temp values*/
					break;
				case '#':
					if(left->type() == 1)
					{
						tempNode = new FloatNode(pow( (((FloatNode*)left)->value), (((FloatNode*)right)->value) ));
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
              //power_elements(*(((MatrixNode*)left)->value), (((FloatNode*)right)->value), *tempMatrix);
							*tempMatrix = ( *(((MatrixNode*)left)->value) & (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							// matrix *tempMatrix = new matrix;
							// *tempMatrix = ( *(((MatrixNode*)left)->value) / *(((MatrixNode*)right)->value) );
							// tempNode = new MatrixNode(tempMatrix);
							throw "---- EXPECT 2ND OPERAND OF .^ TO BE FLOAT BUT MATRIX WAS FOUND ----";
						}
					}
					/*temp values*/
					break;
			}
			temp_stack->add(tempNode);
			delete right;
			delete left;
		}else{
			int temp = i;
			while(true)
			{
				i++;
				if(reverse_polish[i] != '\0')
				{
					if(reverse_polish[i] == ';' || reverse_polish[i] == '|'  || reverse_polish[i] == '&' || reverse_polish[i] == '~' || reverse_polish[i] == '\\' || reverse_polish[i] == '*' || reverse_polish[i] == '/' || reverse_polish[i] == '^' || reverse_polish[i] == '+' || reverse_polish[i] == '-' || reverse_polish[i] == '(' || reverse_polish[i] == ')'  || reverse_polish[i] == '[' || reverse_polish[i] == '`' || reverse_polish[i] == '"'
						|| reverse_polish[i] == '%' || reverse_polish[i] == '=' || reverse_polish[i] == '<' || reverse_polish[i] == '!' || reverse_polish[i] == '_' || reverse_polish[i] == '@' || reverse_polish[i] == '#' || reverse_polish[i] == '?' || reverse_polish[i] == ':' || reverse_polish[i] == '>')
					{
						i--;
						break;
					}
				}else{
					i--;
					break;
				}
			}
			int j = 0;
			bool is_Matrix = false;
			char * word = new char[i-temp+1];
			for (int k = temp; k <= i; ++k)
			{
				if (reverse_polish[k] != ' ' && reverse_polish[k] != '\0')
				{
					if((48 <= ((int)reverse_polish[k]) && ((int)reverse_polish[k]) <= 57)||reverse_polish[k] == '.');
					else{
						is_Matrix = true;
					}
					word[j] = reverse_polish[k];
					j++;
				}
			}
			word[j] = '\0';
			//cout<<"size:"<<i-temp+1<<" "<<word<<endl;
			Node *tempNode;
			if(is_Matrix)
			{
				matrix*  tempMatrix = matrixTree.find(word);
				if(tempMatrix != NULL){
					tempNode = new MatrixNode(tempMatrix, true);
				}else{
					float* tempfloat = varasTree.search(string(word));
					if(tempfloat != NULL){
						tempNode = new FloatNode(*tempfloat, string(word));
					}else{
						tempMatrix = new matrix(4,4);
						tempMatrix->unity_matrix();
						tempMatrix->set_name(word);
						//matrixTree.insert(tempMatrix);
						tempNode = new TempMatrixNode(tempMatrix, true);
					}
				}
			}else{
				tempNode = new FloatNode(atof(word));
			}
			temp_stack->add(tempNode);
		}
	}
  if(temp_stack->top != NULL)
	{
    	Node *left = temp_stack->pop();
      if(left->type() == 1)
      {
        if(echo_flag && ((FloatNode*)(left))->name != "")cout<<((FloatNode*)(left))->name<<" =  "<<endl<<"     ";
        if(echo_flag)cout<<((FloatNode*)(left))->value;
    		/*the third print if the output was float*/
    	}else if(left->type() == 2){
        if(echo_flag)((MatrixNode*)(left))->value->print_matrix();
    	}else{
    		throw "------------------ UNDEFINED VARIABLE \"" + (((TempMatrixNode*)left)->value)->name + "\" ----------------------";
    	}
    	if(echo_flag)cout<<endl;
    return left;
	}else{
		return NULL;
	}
}

Node* do_operation(string str){
    try{
    for(int i =0; i<str.length() ;i++){
        if(str[i] == '\t')str[i]=' ';
    }
	signal(SIGSEGV, sighandler);
	int length = str.size();
	char *infix = new char[length+1];
	int i = 0;
	for (; i < length; ++i)
	{
		infix[i]=str[i];
	}
	infix[i] = '\0';
	char *temp = infix_to_reverse_polish(infix);
	//cout<<temp<<endl;
	Node *result = reverse_polish_to_float(temp);
	return result;
	delete infix;

   		}catch(char const*message){
   			cout<<message<<endl;
   		}catch(string message){
   			cout<<message<<endl;
   		}catch(int error){
		  if     (error==0) cout<<"---------- error: rows or columns is a negative value -----------"<<endl;
		  else if(error==1) cout<<"-- error: matrix element is not a valid input, expected double --"<<endl;
		  else if(error==2) cout<<"----- error: fill matrix error, conflict in columns number ------"<<endl;
		  else if(error==3) cout<<"----------- error: calling matrix has 0 rows or columns----------"<<endl
		  						<<"------------------ sub matrix can't be created  -----------------"<<endl;
		  else if(error==4) cout<<"--- error: required sub matrix is larger than calling matrix ----"<<endl;
		  else if(error==5) cout<<"---- error: not square matrix, determinant can't be evaluated ---"<<endl;
		  else if(error==6) cout<<"----- error: not square matrix, inverse can't be evaluated ------"<<endl;
		  else if(error==7) cout<<"error: zero denominator, infinity output, inverse can't be evaluated."<<endl;
		  else if(error==8) cout<<"---- error: not square matrix, unity matrix can't be created ----"<<endl;
		  else if(error==9) cout<<"---- error: rows or columns=0, unity matrix can't be created ----"<<endl;
		  else if(error==10)cout<<"error: B is not a square matrix, division output can't be evaluated."<<endl;
		  else if(error==11)cout<<"error: A and B matrices mismatch, division output can't be evaluated."<<endl;
		  else if(error==12)cout<<"error: matrices mismatch, sum output can't be evaluated."<<endl;
		  else if(error==13)cout<<"error: matrices mismatch, sub output can't be evaluated."<<endl;
		  else if(error==14)cout<<"error: div_num division output infinity."<<endl;
		  else if(error==15)cout<<"error: matrices mismatch, multiplication output can't be evaluated."<<endl;
		  else if(error==16)cout<<"error: cofactor caller matrix has invalid matrix dimension."<<endl;
		  else if(error==17)cout<<"error: cofactor input error."<<endl;
		  else if(error==18)cout<<"error: not square matrix, power output can't be evaluated."<<endl;
		  else if(error==19)cout<<"error: root square of a negative number, complex output not supported."<<endl;
		  else if(error==20)cout<<"error: matrix element less than or equal zero, ln() can't be evaluated."<<endl;
		  else if(error==21)cout<<"error: matrix element less than or equal zero, log() can't be evaluated."<<endl;
		  else if(error==22)cout<<"error: matrix dimensions don't match"<<endl;
          else if(error==23)cout<<"error: file path is invalid"<<endl;
          else if(error==24)cout<<"error: domensions of matrices being concatenated are not consistent"<<endl;
          else if(error==25)cout<<"error: can't divide by zero"<<endl;
		}
}

void open_cli(){
   	string str = " ";
   	while(true)
   	{
   		cout<<"> ";
   		getline(cin, str);
   		if(str == "exit")break;
   		bool flag_load = false;
   		for(int i = 0;i<str.length();i++){
            if(str.substr(i,4) == "load"){
                math_lab our_math_lab;
                our_math_lab.load_file(trimx(str.substr(i+4)));
                flag_load = true;
                continue;
            }
   		}
   		if(flag_load)continue;
   		if(str == "all")
   		{
   			cout<<endl<<"------------------------- Matrix Tree ---------------------------"<<endl;
			matrixTree.print();
			cout<<endl<<"------------------------- Varas Tree ---------------------------"<<endl;
			varasTree.print();
			continue;
   		}
   		do_operation(str);
   	}
}

//use the following command to compile :)
//g++ shuffleYard.cpp matrix.cpp AVL.cpp -o app
/*
int main()
{
   	open_cli();
}
*/
