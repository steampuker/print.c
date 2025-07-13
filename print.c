#include <stdio.h>
#include <string.h>
#include "print.h"

#define BUFFER_SIZE 1024

size_t log2ill(unsigned long long x) {
    return 63 - __builtin_clzll(x | 1);
}

//https://lemire.me/blog/2021/05/28/computing-the-number-of-digits-of-an-integer-quickly/
size_t log10ill(unsigned long long x) {
    static const unsigned long long digit_lookup[] = {9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, 9999999999, 99999999999, 999999999999, 9999999999999, 99999999999999, 999999999999999ULL, 9999999999999999ULL, 99999999999999999ULL, 999999999999999999ULL, 9999999999999999999ULL};
    unsigned digits = (log2ill(x) * 19) >> 6;
    digits += x > digit_lookup[digits];
    return digits + 1;
}

size_t uintToStr(unsigned long long value, char *receiver) {
    size_t length = log10ill(value);
    unsigned i = 0;
    
    do {
      receiver[length - ++i] = value % 10 + '0';
    } while ((value /= 10) != 0);  
    
    return length;
}

size_t intToStr(long long value, char *receiver) {
    size_t length = 0;
    if(value < 0) {
        length = 1;
        value = -value;
        receiver[0] = '-';
        receiver += 1;
    }
    
    return length + uintToStr(value, receiver);
}

size_t boolToStr(_Bool value, const char **receiver) {
    *receiver = value ? "true" : "false";
    return 4 + !value;
}

static struct {
    int cursor;
    char buffer[BUFFER_SIZE];
} print_buffer;

void print_flush(void) {
    printf("%.*s", print_buffer.cursor, print_buffer.buffer);
    print_buffer.cursor = 0;
}

unsigned interpret_format(unsigned current_arg, struct PrintableType args[], size_t arg_count) {
    char arg_buf[20] = {0};
    const char* print_ptr = arg_buf;
    size_t length;
    
    switch(args[current_arg].type) {
        case PRINTABLE_INT: length = intToStr(args[current_arg].as_int, arg_buf); break;
        case PRINTABLE_BOOL: length = boolToStr(args[current_arg].as_bool, &print_ptr); break;
        case PRINTABLE_CHAR: arg_buf[0] = args[current_arg].as_char; length = 1; break; 
    }
    
    if(print_buffer.cursor + length > (BUFFER_SIZE - 1))
        print_flush();
    
    memcpy(print_buffer.buffer + print_buffer.cursor, print_ptr, length);
    print_buffer.cursor += length;
    return current_arg + 1;
}

void fmt_print_impl(const char* fstring, size_t length, struct PrintableType args[], size_t arg_count) {
    unsigned current_arg = 0;
    for(int cursor = 0; cursor < length; ++cursor) {
        switch(fstring[cursor]) {
        case '{':
            switch(fstring[++cursor]) {
            case '{': break;  
            case '}': 
                if(arg_count <= current_arg) continue;
                current_arg = interpret_format(current_arg, args, arg_count);
                continue;
            }
        default:
                if(fstring[cursor] == '{') cursor++;
                print_buffer.buffer[print_buffer.cursor] = fstring[cursor];
                print_buffer.cursor++;
                
                if(fstring[cursor] == '\n' || print_buffer.cursor > (BUFFER_SIZE - 1))
                    print_flush();
        }
    }
}
