#include "../include/vector.h"

#include <iostream>

using namespace std;

int main() 
{
    fish::Vector<int> vec(10, 1);
    cout << vec.size() << endl;
    for (int i = 0; i < vec.size(); i ++) {
        cout << vec[i] << endl;
    }
    return 0;
}