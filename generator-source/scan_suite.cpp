//
// Created by Michel on 13.05.2021.
//

#include "scan_suite.h"

int acacia::generator::scanSuite(const std::string &content, size_t endPosition, const std::string &suiteName,
        const std::string &inputPath, std::vector<FileTestSuite> &suitesOut, const std::vector<std::string> &activeMacros) {
    FileTestSuite fileTestSuite;
    fileTestSuite.name = suiteName;
    fileTestSuite.prefixMacros = activeMacros;

    for (auto it = activeMacros.rbegin() ; it != activeMacros.rend() ; ++it) {
        const std::string &macro = *it;
        if (macro.rfind("#if", 0) == 0) {
            fileTestSuite.suffixMacros.emplace_back("#endif");
        }
        // No need to consider #else and #elif, they are supposed to have a parent #if in any case
    }

    suitesOut.emplace_back(std::move(fileTestSuite));

    // TODO: Parse tests
    return 0;
}