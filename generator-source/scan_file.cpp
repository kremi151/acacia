//
// Created by Michel on 13.05.2021.
//

#include "scan_file.h"

#include <fstream>
#include <regex>
#include "scan_suite.h"
#include "utils.h"
#include "logging.h"

int acacia::generator::scanFile(const std::string &inputPath, std::vector<std::string> &suitesOut) {
    fprintf(stdout, PRINT_BLUE "Analyzing test source file %s...\n" PRINT_RESET, inputPath.c_str());

    std::ifstream ifstream(inputPath);
    if (!ifstream) {
        fprintf(stderr, "Cannot read test source file at %s\n", inputPath.c_str());
        return 2;
    }

    std::string content((std::istreambuf_iterator<char>(ifstream)),
                        std::istreambuf_iterator<char>());
    ifstream.close();

    std::regex suiteRegex(R"(TEST_SUITE\s*\(([^)]+)\)\s*\{)");
    std::smatch suiteMatch;

    int status;
    while (std::regex_search(content, suiteMatch, suiteRegex)) {
        std::string suiteName = suiteMatch.str(1);
        printf("- Found test suite " PRINT_GREEN "%s" PRINT_RESET "\n", suiteName.c_str());

        content = suiteMatch.suffix();
        size_t suiteEndPosition = findClosingCurly(content);
        if (suiteEndPosition == 0) {
            fprintf(stderr, "Syntax error in %s\n", inputPath.c_str());
            return 3;
        }

        status = scanSuite(content, suiteEndPosition, suiteName, inputPath, suitesOut);
        if (status != 0) {
            return status;
        }

        content = content.substr(suiteEndPosition + 1);
    }

    return 0;
}