//
// Created by mkremer on 6/11/21.
//

#include "cmd_meta.h"
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

#include "scan_file.h"
#include "utils.h"

using namespace acacia;

int generator::handleMetaCommand(int argc, char **argv) {
    if (argc < 3) {
        printUsage(stderr);
        return 1;
    }
    std::string sourceFile = argv[0];
    acacia::generator::ensureTrailingPathSeparator(sourceFile);
    sourceFile += argv[2];

    std::string targetFile = argv[1];
    acacia::generator::ensureTrailingPathSeparator(targetFile);
    targetFile += argv[2];
    targetFile += ".meta";

    std::vector<std::string> suites;

    int status = acacia::generator::scanFile(sourceFile, suites);
    if (status != 0) {
        fprintf(stderr, "Analyzing file at %s failed\n", sourceFile.c_str());
        return status;
    }

    std::ofstream metaOut(targetFile);
    if (!metaOut) {
        fprintf(stderr, "Target meta file %s cannot be written\n", targetFile.c_str());
        return 1;
    }

    bool first = true;
    for (const auto &suite : suites) {
        if (first) {
            first = false;
        } else {
            metaOut << ";";
        }
        metaOut << suite;
    }

    return 0;
}