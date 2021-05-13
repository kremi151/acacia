//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_UTILS_H
#define ACACIA_GEN_UTILS_H

#include <string>
#include <cstdio>

namespace acacia::generator {

    size_t findClosingCurly(const std::string &content);
    void ensureTrailingPathSeparator(std::string &inputPath);
    void printUsage(FILE *stream);

}

#endif //ACACIA_GEN_UTILS_H
