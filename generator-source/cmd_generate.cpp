//
// Created by mkremer on 6/11/21.
//

#include "cmd_generate.h"

#include <fstream>
#include <vector>
#include <string>

#include "utils.h"
#include "logging.h"

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

    std::vector<std::string> suites;
    for (int i = 1 ; i < argc ; i++) {
        std::string metaFile = argv[i];

        std::ifstream ifstream(metaFile);
        if (!ifstream) {
            fprintf(stderr, "Cannot read input meta file at %s\n", argv[i]);
            return 1;
        }
        std::string content((std::istreambuf_iterator<char>(ifstream)),
                            std::istreambuf_iterator<char>());
        ifstream.close();

        size_t start = 0;
        while (true) {
            size_t pos = content.find(';', start);
            if (pos == std::string::npos) {
                if (start == 0 && !content.empty()) {
                    suites.emplace_back(content);
                }
                break;
            }
            std::string token = content.substr(start, pos - start);
            if (!token.empty()) {
                suites.emplace_back(token);
            }
            start = pos + 1;
            if (start >= content.size()) {
                break;
            }
        }
    }

    for (const auto &suiteName : suites) {
        suitesHeaderOut << "namespace __Acacia__TestSuite_" << suiteName << R"( {
    acacia::Report runSuite();
}
)";
        suitesSourceOut << "\tsuites[\"" << suiteName << "\"] = __Acacia__TestSuite_" << suiteName << "::runSuite;\n";
    }

    suitesHeaderOut << "#endif\n";
    suitesSourceOut << "}\n";

    return 0;
}