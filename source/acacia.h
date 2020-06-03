//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_ACACIA_H
#define ACACIA_ACACIA_H

#include <registry/registry.h>
#include <assertions/assertions.h>

#define TEST(name) \
void __Acacia__Test__##name(); \
acacia::Registration __Acacia__Registration_##name(__FILE__, #name, __Acacia__Test__##name); \
void __Acacia__Test__##name()

#endif //ACACIA_ACACIA_H
