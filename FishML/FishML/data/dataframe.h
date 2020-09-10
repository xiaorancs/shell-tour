/*******************************************************
* Copyright (C) 2020 All rights reserved.
* 
* File:    dataframe.h
* Author:  xiaoran (xiaoranone@gmail.com)
* Date:    2020/09/10 14:54:56
*
******************************************************/

#ifndef FISHML_DATA_DATAFRAME_H
#define FISHML_DATA_DATAFRAME_H 

#include <vector>
#include <Eigen/Dense>

#include "FishML/commom/status.h"

namespace fishml {
namespace data {

/* class dataframe, oper data */ 
class DataFrame {
public:
    // vector for init
    template<typename T>
    DataFrame(vector<vector<T>>& mat);
    
    // Eigen::MatrixXd for init 
    DataFrame(Eigen::MatrixXd& mat);
    
    // default init
    DataFrame();

    // Destructor
    ~DataFrame();
    
    // read_csv
    Status read_csv(const std::string file_name, const std::string sep=",", bool header=false);
    
    // write_csv
    Status write_csv(const std::string file_name, const std::string sep=",", bool header=false);

    // read Eigen::MatirxXd
    Status read_mat(const std::string file_name);

    // write Eigen::MatrixXd
    Status write_mat(const std::string file_name);

    // random data
    Status random_data(unsigned rows, unsigned cols);
    
    // get shape
    std::pair<unsigned, unsigned> get_shape();

    // reshape
    Status reshape(unsigned n_rows, unsigned n_cols);

    // reshape
    Status reshape(std::pair<unsigned, unsigned> n_shape);
    
    // construct data from vector
    template<typename T>
    Status construct_from_vector(vector<vector<T>>& mat);

private:
    Eigen::MatrixXd data;
    //std::vector<std::string> columns;
    std::pair<unsigned, unsigned> shape;

}; // class DataFrame


} // namespcae data
} // namesspace fishml


#endif // FISHML_DATA_DATAFRAME_H
