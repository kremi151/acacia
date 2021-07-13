//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_UTILS_H
#define ACACIA_GEN_UTILS_H

#include <string>
#include <cstdio>
#include <vector>
#include "typedefs.h"

namespace acacia::generator {

    size_t findClosingCurly(const std::string &content);
    void ensureTrailingPathSeparator(std::string &inputPath);
    void printUsage(FILE *stream);
    void popBackToStartingIfMacro(std::vector<std::string> &macros);
    std::string serializeTestSuite(const FileTestSuite &suite);
    void deserializeTestSuite(const std::string &in, FileTestSuite &out);

}

#endif //ACACIA_GEN_UTILS_H
