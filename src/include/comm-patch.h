#ifndef __PATCH_H__
#define __PATCH_H__

#include <string>
#include <sstream>

namespace patch{
    template <typename T> std::string to_string(const T& n){
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#endif//__PATCH_H__