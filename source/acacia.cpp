//
// Created by Michel on 03.06.2020.
//

#include "acacia.h"
#include <memory>

std::unique_ptr<acacia::Registry> acaciaRuntime;

acacia::Registry &acacia::runtime() {
    if (!acaciaRuntime) {
        acaciaRuntime = std::make_unique<Registry>();
    }
    return *acaciaRuntime;
}
