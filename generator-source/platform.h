//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_PLATFORM_H
#define ACACIA_GEN_PLATFORM_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define PATH_SEP '\\'
#define BINARY_EXT ".exe"
#else
#define PATH_SEP '/'
#define BINARY_EXT ""
#endif

#endif //ACACIA_GEN_PLATFORM_H
