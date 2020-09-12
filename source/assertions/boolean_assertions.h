//
// Created by Michel Kremer on 05.08.2020.
//

#ifndef ACACIA_BOOLEAN_ASSERTIONS_H
#define ACACIA_BOOLEAN_ASSERTIONS_H

void __acacia_assertTrue(bool value, const char *file, unsigned int line);

#define assertTrue(value) \
__acacia_assertTrue(value, __FILE__, __LINE__)

void __acacia_assertFalse(bool value, const char *file, unsigned int line);

#define assertFalse(value) \
__acacia_assertFalse(value, __FILE__, __LINE__)

#endif //ACACIA_BOOLEAN_ASSERTIONS_H
