#include <iostream>
#include <string>

using namespace std;

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
            cout << value[i].first << " " << value[i].second << endl;
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


int main()
{
    vars X;
    X.add("A",2);
    X.add("B",3);
    X.add("C",5);
    X.add("D",63);
    X.add("E",23);
    X.add("F",14);
    X.add("G",600.22);
    X.print();
    cout << *X.search("D") << endl;
    *X.search("A") = 300;
    *X.search("B") = 123;
    *X.search("C") = 23;
    *X.search("D") = 12312;
    *X.search("E") = 32.23;
    X.print();

    return 0;
}
