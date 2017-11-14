#ifndef MATHLAB_H
#define MATHLAB_H

#include <iostream>
#include <string>
#include <fstream>
#include "dynamic_array_matrix.h"
using namespace std;
class math_lab
{
    dynamic_array_matrix array_matrix;

    public:
    void decode(string operation);
    void load_file(string file_path);
    void open_command();

};
 string trim_spaces(string right_string);
#endif
