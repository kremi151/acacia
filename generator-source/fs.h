//
// Created by mkremer on 16.06.2021.
//

#ifndef ACACIA_GEN_FS_H
#define ACACIA_GEN_FS_H

#ifdef ACACIA_HAS_FS

#if STD_FS_IS_EXPERIMENTAL

#include <experimental/filesystem>

namespace acacia::generator {
    namespace fs = std::experimental::filesystem;
}

#else

#include <filesystem>

namespace acacia::generator {
    namespace fs = std::filesystem;
}

#endif

#endif // ACACIA_HAS_FS

#endif //ACACIA_GEN_FS_H