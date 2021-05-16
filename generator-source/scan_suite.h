//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_SCAN_SUITE_H
#define ACACIA_GEN_SCAN_SUITE_H

#include <string>
#include <vector>
#include "typedefs.h"

namespace acacia::generator {

    int scanSuite(const std::string &content, size_t endPosition, const std::string &suiteName,
                  const std::string &inputPath, std::vector<FileTestSuite> &suitesOut, const std::vector<std::string> &activeMacros);

}

#endif //ACACIA_GEN_SCAN_SUITE_H
