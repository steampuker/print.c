# print.c
A proof-of-concept print macro that supports Python-style formatting. 

Automatically infers argument types (for now, only `int`, `_Bool`/`bool`, `char` and `char*` are supported).

## Usage

print.c adds a macro with two overloads:
 - print(string, args...) - formats `string` replacing `"{}"` with `args` and prints it to the standard output (with a newline).
 - print(print_ctx_t*, args...) - uses a pointer to a `print_ctx_t` structure.

`print_ctx_t` is a struct with the following members:
 - `format` - a character pointer with the format string.
 - `length` - the length of the format string.
 - `stream` - a `FILE*` the output is sent to (stdout, stderr or open files).
 - `newline` - if `true`, prints a newline after the format string 

## Example

``` c
#include "print.h"

int main(void) {
    print("Here are a few examples:");
    /* bool and char need a cast, since C uses int by default */
    print("int: {}, bool: {}, char: {}, string: {}", 21, (_Bool)0, (char)'a', "bazinga");
    
    /* More expressive logging with print_ctx_t */
    print_ctx_t err_ctx = {.stream = stderr, .newline = 0, 
                           .format = "ERROR: Awful code involved - {}", .length = 31};
    print(&err_ctx, (_Bool)1);
    
    /* Newline! */
    print("");
}
```

Output:

    Here are a few examples:
    int: 21, bool: false, char: true, string: bazinga
    ERROR: Awful code involved - true

## Compiling

This project requires a conforming C23 compiler (due to `__VA_OPT__`) but can also work with:
 - GCC 8+
 - Clang 6+
 - MSVC 2019+

For MSVC, enable /Zc:preprocessor and /std:c11

## Feedback

This project is experimental, most of the features (positional arguments, additional formatting, float-to-string conversion, etc.) are missing.

It is also not optimized for performance (uses standard print functions instead of OS syscalls).

Still, I'd appreciate if you [open an issue](https://github.com/steampuker/print.c/issues).

## Related

This project is based on [fmt](https://github.com/fmtlib/fmt) library.

