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

void sighandler(int signum)
{
    //printf("Process %d got signal %d\n", getpid(), signum);
    throw "----------------- INVALID NUMBER OF OPERATORS -------------------";
}


AVL matrixTree;

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
	int type()
	{
		return 1;
	}
	FloatNode(float value)
	{
		this->value = value;
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

Node* do_operation(string str);

int get_operator_order(char cur)
{
	if(cur == '=')return 1;
	if(cur == '+' || cur == '-')return 2;
	if(cur == '*' || cur == '/')return 3;
	//minus operator
	if(cur == '%')return 4;
	//sin operator
	//cos operator
	//tan operator
	if(cur == '<' || cur == '!' || cur == '_')return 5;
	// rand(4,4)
	// eye(4, 4)
	// zeros(2, 3)
	// ones(3, 6)
	// sqrt()
	if(cur == '@' || cur == '#' || cur == '?' || cur == ':' || cur == '`')return 6;
	if(cur == '^')return 7;
	//print operator
	if(cur == '>')return 8;
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
			//sin operation
			if(infix[i] == 's' && infix[i+1] == 'i' && infix[i+2] == 'n' && infix[i+3] == '('){
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
				temp[j] = '#';
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
				temp[j] = '#';
				j++;
				flagNegative = true;
			}
			//zeros operation
			else if(infix[i] == 'z' && infix[i+1] == 'e' && infix[i+2] == 'r' && infix[i+3] == 'o' && infix[i+4] == 's' && infix[i+5] == '('){
				i += 6;
				flag = false;
				temp[j] = '?';
				j++;
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
				flag = false;
				while(infix[i] != ']')
				{
					temp[j] = infix[i];
					i++;
					j++;
				}
				temp[j] = ']';
				j++;
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
	bool echo_flag = false;
	for (int i = 0; reverse_polish[i] != '\0'; ++i)
	{
		if(reverse_polish[i] == ';');
		else if(reverse_polish[i] == '='){
			MatrixNode *right = (MatrixNode*)temp_stack->pop();
			MatrixNode *left = (MatrixNode*)temp_stack->pop();
			*(left->value) = *(right->value);
			if(echo_flag){
				left->value->print_matrix();
				cout<<endl;
			}
			echo_flag = false;
			//right->value->print_matrix();
			delete right;
		}
		else if(reverse_polish[i] == '[')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ']'; ++k)
			{
				count++;
			}
			char *temp_string = new char[count+4];
			int j = 2;
			temp_string[0]='=';
			temp_string[1]='[';
			i++;
			while(reverse_polish[i] != ']')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count+2]=']';
			temp_string[count+3]=';';
			temp_string[count+4]='\0';
			//cout<<temp_string<<endl;
			matrix *tempMatrix = new matrix;
			tempMatrix->fill_matrix(temp_string);
			Node *tempNode = new MatrixNode(tempMatrix);
			/*temp value*/
			temp_stack->add(tempNode);
			delete temp_string;
		}
		//rand operation
		else if(reverse_polish[i] == '@')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				count++;
			}
			char *temp_string = new char[count + 1];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *left = do_operation(temp_string);
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != '@'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 1];
			j = 0;
			i++;
			while(reverse_polish[i] != '@')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *right = do_operation(temp_string);
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
		else if(reverse_polish[i] == '#')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				count++;
			}
			char *temp_string = new char[count + 1];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *left = do_operation(temp_string);
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != '#'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 1];
			j = 0;
			i++;
			while(reverse_polish[i] != '#')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *right = do_operation(temp_string);
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
		//zeros operation
		else if(reverse_polish[i] == '?')
		{
			int count = 0;
			for (int k = i+1; reverse_polish[k] != ','; ++k)
			{
				count++;
			}
			char *temp_string = new char[count + 1];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *left = do_operation(temp_string);
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != '?'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 1];
			j = 0;
			i++;
			while(reverse_polish[i] != '?')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *right = do_operation(temp_string);
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
				count++;
			}
			char *temp_string = new char[count + 1];
			int j = 0;
			i++;
			while(reverse_polish[i] != ',')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *left = do_operation(temp_string);
			i++;
			count = 0;
			for (int k = i+1; reverse_polish[k] != ':'; ++k)
			{
				count++;
			}
			temp_string = new char[count + 1];
			j = 0;
			i++;
			while(reverse_polish[i] != ':')
			{
				temp_string[j] = reverse_polish[i];
				j++;
				i++;
			}
			temp_string[count]='\0';
			Node *right = do_operation(temp_string);
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
			if(left->type() == 1)
			{
				tempNode = new FloatNode(sin ( ((FloatNode*)(left))->value * PI/180) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = ( *(((MatrixNode*)left)->value) * -1);
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
			if(left->type() == 1)
			{
				tempNode = new FloatNode(cos ( ((FloatNode*)(left))->value * PI/180) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = ( *(((MatrixNode*)left)->value) * -1);
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
			if(left->type() == 1)
			{
				tempNode = new FloatNode(tan ( ((FloatNode*)(left))->value * PI/180) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = ( *(((MatrixNode*)left)->value) * -1);
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
			if(left->type() == 1)
			{
				tempNode = new FloatNode(sqrt ( ((FloatNode*)(left))->value ) );
			}else{
				matrix *tempMatrix = new matrix;
				*tempMatrix = ( *(((MatrixNode*)left)->value) * -1);
				tempNode = new MatrixNode(tempMatrix);
			}
			/*temp value*/
			temp_stack->add(tempNode);
			delete left;
		}
		//print operator
		else if(reverse_polish[i] == '>')
		{
			if(reverse_polish[i+1] != '='){
				Node *left = temp_stack->pop();
				if(left->type() == 1)
				{
					cout<<((FloatNode*)(left))->value;
					/*the third print if the output was float*/
				}else{
					((MatrixNode*)(left))->value->print_matrix();
				}
				cout<<endl;
			}else{
				echo_flag = true;
			}
		}
		//mius operator
		else if(reverse_polish[i] == '%')
		{
			Node *left = temp_stack->pop();
			Node *tempNode;
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
		else if(reverse_polish[i] == '*' || reverse_polish[i] == '/' || reverse_polish[i] == '^' || reverse_polish[i] == '+' || reverse_polish[i] == '-')
		{
			Node *right = temp_stack->pop();
			Node *left = temp_stack->pop();
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
							tempNode = new FloatNode(( (((FloatNode*)left)->value) / (((FloatNode*)right)->value) ));
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
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) / *(((MatrixNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}
					}
					/*temp values*/
					break;
				case '^':
					if(left->type() == 1)
					{
						if(right->type() == 1)
						{
							tempNode = new FloatNode( pow( (((FloatNode*)left)->value), (((FloatNode*)right)->value) ) );
						}else{
							//throw error
						}
					}else{
						if(right->type() == 1)
						{
							matrix *tempMatrix = new matrix;
							*tempMatrix = ( *(((MatrixNode*)left)->value) ^ (((FloatNode*)right)->value) );
							tempNode = new MatrixNode(tempMatrix);
						}else{
							//throw error
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
					if(reverse_polish[i] == ';' || reverse_polish[i] == '*' || reverse_polish[i] == '/' || reverse_polish[i] == '^' || reverse_polish[i] == '+' || reverse_polish[i] == '-' || reverse_polish[i] == '(' || reverse_polish[i] == ')'  || reverse_polish[i] == '[' || reverse_polish[i] == '`'
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
					matrix* tempMatrix = new matrix(4,4);
					tempMatrix->unity_matrix();
					tempMatrix->set_name(word);
					matrixTree.insert(tempMatrix);
					tempNode = new MatrixNode(tempMatrix, true);
				}
			}else{
				tempNode = new FloatNode(atof(word));
			}
			temp_stack->add(tempNode);
		}
	}
	if(temp_stack->top != NULL)
	{
		return temp_stack->pop();
	}else{
		return NULL;
	}
}

Node* do_operation(string str){
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
}

void open_cli(){
   	string str = " ";
   	while(true)
   	{
   		cout<<"> ";
   		getline(cin, str);
   		if(str == "exit")break;
   		if(str == "all")
   		{
   			cout<<endl<<"------------------------- Matrix Tree ---------------------------"<<endl;
			matrixTree.print();
			continue;
   		}
   		try{
   			do_operation(str);
   		}catch(char const*message){
   			cout<<message<<endl;
   		}
   	}
}

//use the following command to compile :)
//g++ shuffleYard.cpp matrix.cpp AVL.cpp -o app

int main()
{
   	open_cli();
}