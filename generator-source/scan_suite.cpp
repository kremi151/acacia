//
// Created by Michel on 13.05.2021.
//

#include "scan_suite.h"

int acacia::generator::scanSuite(const std::string &content, size_t endPosition, const std::string &suiteName,
        const std::string &inputPath, std::ostream &suitesHeaderOut, std::ostream &suitesSourceOut) {
    suitesHeaderOut << "namespace __Acacia__TestSuite_" << suiteName << R"( {
    acacia::Report runSuite();
}
)";
    suitesSourceOut << "\tsuites[\"" << suiteName << "\"] = __Acacia__TestSuite_" << suiteName << "::runSuite;\n";
    // TODO: Parse tests
    return 0;
}