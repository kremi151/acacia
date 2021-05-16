//
// Created by mkremer on 6/11/21.
//

#include "cmd_meta.h"
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

#include "scan_file.h"
#include "typedefs.h"
#include "utils.h"

#ifdef ACACIA_HAS_FS
#include "fs.h"
#endif

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

    std::vector<FileTestSuite> suites;

    int status = acacia::generator::analyzeFile(sourceFile, suites);
    if (status != 0) {
        fprintf(stderr, "Analyzing file at %s failed\n", sourceFile.c_str());
        return status;
    }

#ifdef ACACIA_HAS_FS
    fs::path metaParentPath = fs::path(targetFile).parent_path();
    try {
        fs::create_directories(metaParentPath);
    } catch (const fs::filesystem_error &e) {
        fprintf(stderr, "Unable to create directory at %s: %s\n", metaParentPath.c_str(), e.what());
        return 1;
    }
#endif

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
            metaOut << "\n";
        }
        metaOut << generator::serializeTestSuite(suite);
    }

    return 0;
}