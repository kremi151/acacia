//
// Created by Michel on 13.05.2021.
//

#include "utils.h"

#include <sstream>
#include <vector>
#include "platform.h"

namespace acacia::generator {

    void parseCsvList(const std::string &in, std::vector<std::string> &out) {
        int start = 0;
        int pos;
        while (true) {
            pos = in.find(',', start);
            if (pos == std::string::npos) {
                if (start == 0) {
                    if (!in.empty()) {
                        out.emplace_back(in);
                    }
                } else {
                    std::string substr = in.substr(start);
                    if (!substr.empty()) {
                        out.emplace_back(substr);
                    }
                }
                break;
            }
            out.emplace_back(in.substr(start, pos - start));
            start = pos + 1;
        }
    }

}

using namespace acacia;

size_t generator::findClosingCurly(const std::string &content) {
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

void generator::ensureTrailingPathSeparator(std::string &inputPath) {
    if (inputPath.at(inputPath.size() - 1) != PATH_SEP) {
        inputPath += PATH_SEP;
    }
}

void generator::printUsage(FILE *stream) {
    fprintf(stream, "Usage:\n");
    fprintf(stream, "acacia-gen" BINARY_EXT " meta <source root dir> <meta root dir> <input file>\n");
    fprintf(stream, "acacia-gen" BINARY_EXT " generate <output dir> <meta file 1> <meta file 2> ...\n");
}

void generator::popBackToStartingIfMacro(std::vector<std::string> &macros) {
    while (!macros.empty()) {
        const std::string &macro = macros[macros.size() - 1];
        if (macro.rfind("#if", 0) == 0 || macro.rfind("#ifdef", 0) == 0 || macro.rfind("#ifndef", 0) == 0) {
            macros.pop_back();
            return;
        }
        macros.pop_back();
    }
}

std::string generator::serializeTestSuite(const FileTestSuite &suite) {
    std::stringstream ss;
    ss << suite.name;
    ss << ";";

    bool first = true;
    for (const auto &prefix : suite.prefixMacros) {
        if (first) {
            first = false;
        } else {
            ss << ",";
        }
        ss << prefix;
    }
    ss << ";";

    first = true;
    for (const auto &suffix : suite.suffixMacros) {
        if (first) {
            first = false;
        } else {
            ss << ",";
        }
        ss << suffix;
    }

    return ss.str();
}

void generator::deserializeTestSuite(const std::string &in, FileTestSuite &out) {
    int start = in.find(';');
    if (start == std::string::npos) {
        throw std::out_of_range("Invalid test suite token, could not read suite name");
    }
    out.name = in.substr(0, start++);

    int pos = in.find(';', start);
    if (pos == std::string::npos) {
        throw std::out_of_range("Invalid test suite token, could not read prefix macros");
    }
    std::string subtoken = in.substr(start, pos - start);
    out.prefixMacros.clear();
    parseCsvList(subtoken, out.prefixMacros);
    start = pos + 1;

    subtoken = in.substr(start);
    out.suffixMacros.clear();
    parseCsvList(subtoken, out.suffixMacros);
}
