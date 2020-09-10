/*******************************************************
* Copyright (C) 2020 All rights reserved.
* 
* File:    utils.h
* Author:  xiaoran (xiaoranone@gmail.com)
* Date:    2020/09/10 17:47:54
*
******************************************************/

#ifndef FISHML_COMMON_UTILS_H
#define FISHML_COMMON_UTILS_H

#include <vector>
#include <string>
#include <algorithm>

namespace fishml {
namespace core {

// string to double in vector
void stod_vector(std::vector<double>& target, 
                std::vector<std::string>& str_vec) {
    if (target.size() == 0) {
        for (auto& str : str_vec) {
            double d = 0.0;
            try {
                d = std::stod(str);
            } 
            catch(...) {
                d = 0.0;
            }
            target.push_back(d);
        }
    }
    else if (target.size() >= str_vec.size()) {
        for (int i = 0; i < str_vec.size(); ++i) {
            double d = 0.0;
            try {
                d = std::stod(str);
            } 
            catch(...) {
                d = 0.0;
            }
            target[i] = d;
        }
    }
}

} // fishml::core
} // fishml

#endif // FISHML_COMMON_UTILS_H

