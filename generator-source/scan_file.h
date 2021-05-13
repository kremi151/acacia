//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_SCAN_FILE_H
#define ACACIA_GEN_SCAN_FILE_H

#include <string>
#include <ostream>

namespace acacia::generator {

    int scanFile(const std::string &inputPath, std::ostream &suitesHeaderOut, std::ostream &suitesSourceOut);

}

#endif //ACACIA_GEN_SCAN_FILE_H
