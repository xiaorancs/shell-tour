/*******************************************************
* Copyright (C) 2020 All rights reserved.
* 
* File:    dataframe.cpp
* Author:  xiaoran (xiaoranone@gmail.com)
* Date:    2020/09/10 16:20:03
*
******************************************************/

#include "dataframe.h"
#include "fishml/comon/utils.h"

#include <iostream>
#include <ifstream>
#include <ofstream>
#include <boost/algorithm/string.hpp>

namespace fishml {
namespace data {

// default DataFrame
DataFrame::DataFrame() {}

// default ~DataFrame
DataFrame::~DataFrame() {}

// Eigen::MatrixXd for init
DataFrame::DataFrame(Eigen::MatrixXd& mat) {
    data = mat;
}

// vector for init
template<typename T>
DataFrame::DataFrame(vector<vector<T>>& mat) {
    construct_from_vector(data);
}

// construct data from vector
Status DataFrame::construct_from_vector(vector<vector<T>>& mat) {
    if (mat.empty() || mat[0].empty()) {
        return Status::kError;
    }
    int rows = mat.size();
    int cols = mat[0].size();
    data = Eigen::Map<Eigen::Matrix<T, rows, cols> >(mat); 
    return Status::kOk;
}

// read csv 
Status DataFrame::read_csv(const std::string file_name, const std::string sep=",", bool header=false) {
    std::ifstream fin(file_name);
    if (!fin) { // failed to open file 
        return Status::kIOError;
    }
    std::string temp_s;
    std::vector<std::vector<double>> vec_mat;
    while (std::getline(fin, temp_s)) {
        std::vector<std::string> temp_vec;
        boost::algorithm::split(temp_vec, temp_s, boost::algorithm::is_any_of(sep));
        std::vector<double> temp_d;
        fishml::core::stod_vector(temp_d, temp_vec);
        vec_mat.emplace_back(temp_d);
    }
    if (Status::kOk != construct_from_vector(vec_mat)) {
        return Status::kError;
    }
    return Status::kOk;
}

// write csv 
Status DataFrame::write_csv(const std::string file_name, const std::string sep=",", bool header=false) {
    
    
    return Status::kOk;
}


} // fishml::data
} // fishml
