//
// Created by Michel on 27.07.2020.
//

#include "acacia_report.h"

#include <sstream>
#include <util/json_serialization.h>

void acacia::generateAcaciaReport(acacia::Report &report, std::ofstream &file) {
    file << R"({"version":1,"tests":{)";
    bool firstTestfile = true;
    for (auto it = report.results_begin() ; it != report.results_end() ; it++) {
        if (firstTestfile) {
            firstTestfile = false;
        } else {
            file << ",";
        }
        auto &testFile = *it;

        file << "\"" << testFile.first << "\":[";

        bool firstTestResult = true;
        for (const auto & result : testFile.second) {
            if (firstTestResult) {
                firstTestResult = false;
            } else {
                file << ",";
            }
            file << R"({"name":")" << util::escapeJsonString(result.getTestName()) << R"(","skipped":false,)";
            if (result.getErrorLine() > 0) {
                file << R"("error":{"assertion":")" << util::escapeJsonString(result.getAssertion()) << R"(","line":)" << result.getErrorLine() << "},";
            }
            file << R"("stdout":")" << util::escapeJsonString(result.getOutput())
                 << R"(","stderr":")" << util::escapeJsonString(result.getErrorOutput()) << "\"}";
        }

        file << "]";
    }

    file << "}}";
};