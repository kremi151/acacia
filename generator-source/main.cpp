//
// Created by mkremer on 5/12/21.
//

#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>

#include "logging.h"
#include "utils.h"
#include "cmd_meta.h"
#include "cmd_generate.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        acacia::generator::printUsage(stderr);
        return 1;
    }
    if (std::strcmp("help", argv[1]) == 0) {
        acacia::generator::printUsage(stdout);
        return 0;
    }
    if (std::strcmp("meta", argv[1]) == 0) {
        return acacia::generator::handleMetaCommand(argc - 2, argv + 2);
    }
    if (std::strcmp("generate", argv[1]) == 0) {
        return acacia::generator::handleGenerateCommand(argc - 2, argv + 2);
    }
    acacia::generator::printUsage(stderr);
    return 1;
}

int main_old(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Missing arguments\n");
        acacia::generator::printUsage(stderr);
        return 1;
    }
    std::string sourceDir = argv[1];
    const char *outputDir = argv[2];

    fprintf_debug(stdout, "Source dir is %s\n", sourceDir.c_str());
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

    int status;
    for (int i = 3 ; i < argc ; i++) {

        if (status != 0) {
            return status;
        }
    }

    suitesHeaderOut << "#endif\n";
    suitesSourceOut << "}\n";
}
