//
// Created by mkremer on 5/12/21.
//

#include <cstdio>
#include <fstream>
#include <string>
#include <regex>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

int scanFile(const char *outputDir, const std::string &inputPath, std::ofstream &suitesHeaderOut, std::ofstream &suitesSourceOut);
int scanSuite(const std::string &content, size_t endPosition, const std::string &suiteName, const std::string &inputPath, std::ofstream &suitesHeaderOut, std::ofstream &suitesSourceOut);
size_t findClosingCurly(const std::string &content);

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Missing arguments\n");
        return 1;
    }
    std::string sourceDir = argv[1];
    const char *outputDir = argv[2];

    fprintf(stdout, "Source dir is %s\n", sourceDir.c_str());
    fprintf(stdout, "Output dir is %s\n", outputDir);

    std::string suitesHeaderPath = outputDir;
    if (suitesHeaderPath.at(suitesHeaderPath.size() - 1) != PATH_SEP) {
        suitesHeaderPath += PATH_SEP;
    }
    suitesHeaderPath += "suites.h";
    fprintf(stdout, "Write suites.h to %s\n", suitesHeaderPath.c_str());
    std::ofstream suitesHeaderOut(suitesHeaderPath);
    suitesHeaderOut << R"(#ifndef ACACIA_GENERATED_SUITES_H
#define ACACIA_GENERATED_SUITES_H
#include <acacia.h>
)";

    std::string suitesSourcePath = suitesHeaderPath.substr(0, suitesHeaderPath.size() - sizeof("suites.h") + 1) + "test_suites.cpp";
    fprintf(stdout, "Write test_suites.cpp to %s\n", suitesSourcePath.c_str());
    std::ofstream suitesSourceOut(suitesSourcePath);
    suitesSourceOut << R"(#include <acacia.h>
#include <util/test_suites.h>
#include "suites.h"

void acacia::populateSuites(std::map<std::string, SuiteRunner> &suites) {
)";

    int status;
    for (int i = 3 ; i < argc ; i++) {
        std::string inputPath = sourceDir;
        if (inputPath.at(inputPath.size() - 1) != PATH_SEP) {
            inputPath += PATH_SEP;
        }
        inputPath += argv[i];
        status = scanFile(outputDir, inputPath, suitesHeaderOut, suitesSourceOut);
        if (status != 0) {
            return status;
        }
    }

    suitesHeaderOut << "#endif\n";
    suitesSourceOut << "}\n";
}

int scanFile(const char *outputDir, const std::string &inputPath, std::ofstream &suitesHeaderOut, std::ofstream &suitesSourceOut) {
    fprintf(stdout, "Analyzing test source file %s...\n", inputPath.c_str());

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
        printf("Found test suite %s\n", suiteName.c_str());

        content = suiteMatch.suffix();
        size_t suiteEndPosition = findClosingCurly(content);
        if (suiteEndPosition == 0) {
            fprintf(stderr, "Syntax error in %s\n", inputPath.c_str());
            return 3;
        }

        status = scanSuite(content, suiteEndPosition, suiteName, inputPath, suitesHeaderOut, suitesSourceOut);
        if (status != 0) {
            return status;
        }

        content = content.substr(suiteEndPosition + 1);
    }

    return 0;
}

int scanSuite(const std::string &content, size_t endPosition, const std::string &suiteName, const std::string &inputPath, std::ofstream &suitesHeaderOut, std::ofstream &suitesSourceOut) {
    suitesHeaderOut << "namespace __Acacia__TestSuite_" << suiteName << R"( {
    acacia::Report runSuite();
}
)";
    suitesSourceOut << "\tsuites[\"" << suiteName << "\"] = __Acacia__TestSuite_" << suiteName << "::runSuite;\n";
    // TODO: Parse tests
    return 0;
}

size_t findClosingCurly(const std::string &content) {
    int curlies = 0;
    for (size_t i = 0 ; i < content.size() ; i++) {
        switch (content.at(i)) {
            case '{':
                curlies++;
                break;
            case '}':
                if (--curlies < 0) {
                    return i;
                }
                break;
        }
    }
    return 0;
}