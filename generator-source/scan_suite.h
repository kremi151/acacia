//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_SCAN_SUITE_H
#define ACACIA_GEN_SCAN_SUITE_H

#include <string>
#include <ostream>

namespace acacia::generator {

    int scanSuite(const std::string &content, size_t endPosition, const std::string &suiteName,
            const std::string &inputPath, std::ostream &suitesHeaderOut, std::ostream &suitesSourceOut);

}

#endif //ACACIA_GEN_SCAN_SUITE_H
