#ifndef PRINT_C_H
#define PRINT_C_H

#include <stdlib.h>
#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1) __VA_OPT__(, FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define VA_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16

#define TYPE_TO_ARG(x) (struct PrintableType) { _Generic(x, \
                        int: PRINTABLE_INT, \
                        _Bool: PRINTABLE_BOOL, \
                        char: PRINTABLE_CHAR), \
                        {x}}

#define VA_GET_1ST(_1, ...) _1
#define VA_GET_REST(x, ...) __VA_ARGS__ 

#define TYPE_ARR(...) (struct PrintableType[]) {FOR_EACH(TYPE_TO_ARG, __VA_ARGS__) __VA_OPT__(,) {0} }
#define print(x, ...) fmt_print_impl(x, sizeof(x) - 1, \
                      TYPE_ARR(__VA_ARGS__), \
                      VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))

#define printn(x, ...) print(x "\n", __VA_ARGS__)

struct source_string {
    const char* string; size_t length;
};

struct PrintableType { 
    enum {PRINTABLE_INT, PRINTABLE_BOOL, PRINTABLE_CHAR} type;
    union {
        long long as_int;
        _Bool as_bool;
        char as_char;
    };
};

void fmt_print_impl(const char* fstring, size_t length, struct PrintableType args[], size_t arg_count);

#endif

/*
MIT License

Copyright (c) 2025 steampuker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
