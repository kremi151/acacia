//
// Created by Michel on 13.05.2021.
//

#include "utils.h"

#include "platform.h"

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
    fprintf(stream, "Usage:\nacacia-gen" BINARY_EXT " <source dir> <output dir> [<test source 1> <test source 2> ...]");
}