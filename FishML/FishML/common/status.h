/*******************************************************
* Copyright (C) 2020 All rights reserved.
* 
* File:    status.h
* Author:  xiaoran (xiaoranone@gmail.com)
* Date:    2020/09/10 15:58:56
*
******************************************************/

#ifndef FISHML_COMMON_STATUS_H
#define FISHML_COMMON_STATUS_H 

namespace fishml {

enum Status {
    kOk = 0, // success
    kError = 1, // Error
    kIOError = 2 //IO Error 
};

} // fishml

#endif // FISHML_COMMON_STATUS_H
