//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_SCAN_FILE_H
#define ACACIA_GEN_SCAN_FILE_H

#include <string>
#include <vector>

namespace acacia::generator {

    int scanFile(const std::string &inputPath, std::vector<std::string> &suitesOut);

}

#endif //ACACIA_GEN_SCAN_FILE_H
