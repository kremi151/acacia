//
// Created by Michel on 07.06.2020.
//

#ifndef ACACIA_OUTPUT_ASSERTIONS_H
#define ACACIA_OUTPUT_ASSERTIONS_H

void __acacia_assertStandardOutputHas(const char *text, const char *fileName, unsigned int line);

#define assertStandardOutputHas(text) \
__acacia_assertStandardOutputHas(text, __FILE__, __LINE__)

void __acacia_assertStandardOutputHasNot(const char *text, const char *fileName, unsigned int line);

#define assertStandardOutputHasNot(text) \
__acacia_assertStandardOutputHasNot(text, __FILE__, __LINE__)

void __acacia_assertErrorOutputHas(const char *text, const char *fileName, unsigned int line);

#define assertErrorOutputHas(text) \
__acacia_assertErrorOutputHas(text, __FILE__, __LINE__)

void __acacia_assertErrorOutputHasNot(const char *text, const char *fileName, unsigned int line);

#define assertErrorOutputHasNot(text) \
__acacia_assertErrorOutputHasNot(text, __FILE__, __LINE__)

#endif //ACACIA_OUTPUT_ASSERTIONS_H
