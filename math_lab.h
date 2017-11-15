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
<<<<<<< HEAD
=======
 string trim_r(string right_string);
>>>>>>> d30dcece09b1dacf0b02def69c19411fececf368
#endif
