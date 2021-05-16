//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_SCAN_FILE_H
#define ACACIA_GEN_SCAN_FILE_H

#include <string>
#include <ostream>
#include <vector>
#include <string>
#include "typedefs.h"

namespace acacia::generator {

    int analyzeFile(const std::string &inputPath, std::vector<FileTestSuite> &suitesOut);

}

#endif //ACACIA_GEN_SCAN_FILE_H
