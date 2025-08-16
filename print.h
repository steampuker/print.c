#ifndef PRINT_C_H
#define PRINT_C_H

#include <stdlib.h>
#include <stdio.h>

struct PrintableType { 
    enum {PRINTABLE_INT, PRINTABLE_BOOL, PRINTABLE_CHAR, PRINTABLE_STRING} type;
    union {
        long long as_int;
        char* as_str;
        _Bool as_bool;
        char as_char;
    };
};

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

#define TYPE_TO_ARG(x)  _Generic(x, \
                        int: (struct PrintableType) {PRINTABLE_INT, .as_int = (long long)x}, \
                        _Bool: (struct PrintableType) {PRINTABLE_BOOL, .as_bool = !!x}, \
                        char: (struct PrintableType) {PRINTABLE_BOOL, .as_bool = (char)(long)x}, \
                        char*: (struct PrintableType) {PRINTABLE_STRING, .as_str = (char*)x})

#define VA_GET_1ST(_1, ...) _1
#define VA_GET_REST(x, ...) __VA_ARGS__ 

#define TYPE_ARR(...) (struct PrintableType[]) {FOR_EACH(TYPE_TO_ARG, __VA_ARGS__) __VA_OPT__(,) {0} }

// #define INDIRECT(call, ...) call(__VA_ARGS__)
// #define DEPAREN(prefix, x) INDIRECT(PARENS_PROCESS, prefix, PARENS_CAPTURED x)
// #define PARENS_CAPTURED(...) NOTHING __VA_ARGS__
// #define PARENS_PROCESS(prefix, ...) prefix ## __VA_ARGS__
// #define PROCESS_PARENS_CAPTURED .newline = 1, .stream = stdout, .format = 
// #define PROCESS_NOTHING .format = 

#define OVERLOAD_PARAM1(x) _Generic(x, \
                           char*: &(struct print_ctx_t){.newline = 1, .stream = stdout, .format = (const char*)x, .length = sizeof _Generic(x, char*: x, default: (char[2]){}) - 1}, \
                           const char*: &(struct print_ctx_t){.newline = 1, .stream = stdout, .format = (const char*)x, .length = sizeof _Generic(x, char*: x, default: (char[2]){}) - 1}, \
                           struct print_ctx_t*: x)


#define print(x, ...) fmt_print_impl(OVERLOAD_PARAM1(x), \
                      TYPE_ARR(__VA_ARGS__), \
                      VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))

typedef struct print_ctx_t {
    const char* format; 
    FILE* stream;
    size_t length;
    _Bool newline;
} print_ctx_t;

void fmt_print_impl(const struct print_ctx_t* format, struct PrintableType args[], size_t arg_count);

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
