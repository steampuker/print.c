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
                        char: (struct PrintableType) {PRINTABLE_CHAR, .as_char = (char)(long)x}, \
                        char*: (struct PrintableType) {PRINTABLE_STRING, .as_str = (char*)x})

#define VA_GET_1ST(_1, ...) _1
#define VA_GET_REST(x, ...) __VA_ARGS__ 

#define TYPE_ARR(...) (struct PrintableType[]) {FOR_EACH(TYPE_TO_ARG, __VA_ARGS__) __VA_OPT__(,) {0} }

struct print_ctx_t {
    const char* format; 
    FILE* stream;
    size_t length;
};

void fmt_print_impl(const struct print_ctx_t* format, struct PrintableType args[], size_t arg_count);

#endif

#define print(format_string, ...) fmt_print_impl(&(struct print_ctx_t){.stream = stdout, .format = format_string, .length = sizeof format_string - 1}, \
                      TYPE_ARR(__VA_ARGS__), \
                      VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))

#define println(format_string, ...) fmt_print_impl(&(struct print_ctx_t){.stream = stdout, .format = format_string "\n", .length = sizeof format_string}, \
                      TYPE_ARR(__VA_ARGS__), \
                      VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))

#define print_to(out, format_string, ...) fmt_print_impl(&(struct print_ctx_t){.stream = out, .format = format_string, .length = sizeof format_string - 1}, \
                      TYPE_ARR(__VA_ARGS__), \
                      VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))

#define println_to(out, format_string, ...) fmt_print_impl(&(struct print_ctx_t){.stream = out, .format = format_string "\n", .length = sizeof format_string}, \
                      TYPE_ARR(__VA_ARGS__), \
                      VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))
