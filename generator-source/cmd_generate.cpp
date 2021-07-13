//
// Created by mkremer on 6/11/21.
//

#include "cmd_generate.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "utils.h"
#include "typedefs.h"
#include "logging.h"

namespace acacia::generator {

    void printMacros(std::ostream &out, const std::vector<std::string> &macros) {
        for (const std::string &macro : macros) {
            out << macro << std::endl;
        }
    }

}

using namespace acacia;

int generator::handleGenerateCommand(int argc, char **argv) {
    if (argc < 2) {
        printUsage(stderr);
        return 1;
    }

    const char *outputDir = argv[0];

    fprintf_debug(stdout, "Output dir is %s\n", outputDir);

    std::string suitesHeaderPath = outputDir;
    acacia::generator::ensureTrailingPathSeparator(suitesHeaderPath);
    suitesHeaderPath += "suites.h";
    fprintf_debug(stdout, "Write suites.h to %s\n", suitesHeaderPath.c_str());
    std::ofstream suitesHeaderOut(suitesHeaderPath);
    suitesHeaderOut << R"(#ifndef ACACIA_GENERATED_SUITES_H
#define ACACIA_GENERATED_SUITES_H
#include <acacia.h>
)";

    std::string suitesSourcePath = suitesHeaderPath.substr(0, suitesHeaderPath.size() - sizeof("suites.h") + 1) + "test_suites.cpp";
    fprintf_debug(stdout, "Write test_suites.cpp to %s\n", suitesSourcePath.c_str());
    std::ofstream suitesSourceOut(suitesSourcePath);
    suitesSourceOut << R"(#include <acacia.h>
#include <util/test_suites.h>
#include "suites.h"

void acacia::populateSuites(std::map<std::string, SuiteRunner> &suites) {
)";

    std::vector<FileTestSuite> suites;
    for (int i = 1 ; i < argc ; i++) {
        std::string metaFile = argv[i];

        std::ifstream ifstream(metaFile);
        if (!ifstream) {
            fprintf(stderr, "Cannot read input meta file at %s\n", argv[i]);
            return 1;
        }

        std::string line;
        while (std::getline(ifstream, line)) {
            auto &suite = suites.emplace_back();
            deserializeTestSuite(line, suite);
        }
    }

    for (const auto &fileSuite : suites) {
        acacia::generator::printMacros(suitesHeaderOut, fileSuite.prefixMacros);
        suitesHeaderOut << "namespace __Acacia__TestSuite_" << fileSuite.name << R"( {
    acacia::Report runSuite();
}
)";
        acacia::generator::printMacros(suitesHeaderOut, fileSuite.suffixMacros);

        acacia::generator::printMacros(suitesSourceOut, fileSuite.prefixMacros);
        suitesSourceOut << "\tsuites[\"" << fileSuite.name << "\"] = __Acacia__TestSuite_" << fileSuite.name << "::runSuite;\n";
        acacia::generator::printMacros(suitesSourceOut, fileSuite.suffixMacros);
    }

    suitesHeaderOut << "#endif\n";
    suitesSourceOut << "}\n";

    return 0;
}