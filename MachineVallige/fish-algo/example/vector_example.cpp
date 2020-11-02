#include "../include/vector.h"

#include <iostream>

using namespace std;

int main() 
{
    fish::Vector vec(10, 1);
    for (int i = 0; i < vec.size(); i ++) {
        cout << vec[i] << endl;
    }
    return 0;
}