//
// Created by Michel on 16.05.2021.
//

#ifndef ACACIA_GEN_TYPEDEFS_H
#define ACACIA_GEN_TYPEDEFS_H

#include <string>
#include <vector>

namespace acacia::generator {

    typedef struct {
        std::string name;
        std::vector<std::string> prefixMacros;
        std::vector<std::string> suffixMacros;
    } FileTestSuite;

}

#endif //ACACIA_GEN_TYPEDEFS_H
