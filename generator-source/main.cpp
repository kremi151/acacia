//
// Created by mkremer on 5/12/21.
//

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "scan_file.h"
#include "logging.h"
#include "utils.h"
#include "typedefs.h"

namespace acacia::generator {

    void writeLines(std::ostream &out, const std::vector<std::string> &lines) {
        for (const std::string &line : lines) {
            out << line << std::endl;
        }
    }

}

int main(int argc, char **argv) {
    if (argc < 3) {
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

)";

    std::vector<acacia::generator::FileTestSuite> fileSuites;
    std::vector<std::string> customIncludes;

    int status;
    for (int i = 3 ; i < argc ; i++) {
        std::string inputPath = sourceDir;
        acacia::generator::ensureTrailingPathSeparator(inputPath);
        inputPath += argv[i];
        status = acacia::generator::analyzeFile(inputPath, fileSuites, customIncludes);
        if (status != 0) {
            return status;
        }
    }

    acacia::generator::writeLines(suitesHeaderOut, customIncludes);

    acacia::generator::writeLines(suitesSourceOut, customIncludes);
    suitesSourceOut << R"(
void acacia::populateSuites(std::map<std::string, SuiteRunner> &suites) {
)";

    for (const auto &fileSuite : fileSuites) {
        acacia::generator::writeLines(suitesHeaderOut, fileSuite.prefixMacros);
        suitesHeaderOut << "namespace __Acacia__TestSuite_" << fileSuite.name << R"( {
    acacia::Report runSuite();
}
)";
        acacia::generator::writeLines(suitesHeaderOut, fileSuite.suffixMacros);

        acacia::generator::writeLines(suitesSourceOut, fileSuite.prefixMacros);
        suitesSourceOut << "\tsuites[\"" << fileSuite.name << "\"] = __Acacia__TestSuite_" << fileSuite.name << "::runSuite;\n";
        acacia::generator::writeLines(suitesSourceOut, fileSuite.suffixMacros);
    }

    suitesHeaderOut << "#endif\n";
    suitesSourceOut << "}\n";
}
