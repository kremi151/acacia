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
    fprintf(stream, "Usage:\n");
    fprintf(stream, "acacia-gen" BINARY_EXT " meta <source root dir> <meta root dir> <input file>\n");
    fprintf(stream, "acacia-gen" BINARY_EXT " generate <output dir> <meta file 1> <meta file 2> ...\n");
}