//
// Created by mkremer on 5/12/21.
//

#include <cstdio>
#include <cstring>

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
