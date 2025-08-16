# print.c
A proof-of-concept set of print macros that support Python-style formatting. 

Automatically infers argument types (for now, only `int`, `_Bool`/`bool`, `char` and `char*` are supported).

## Usage

The API consists of 4 macros:
 - print(format_string, args...) - formats `format_string` replacing `"{}"` with `args` and prints it to the standard output.
 - println(format_string, args...) - same as print but appends a newline.
 - print_to(out, args...) - same as `print` but instead outputs it to the `out` file stream.
 - println(format_string, args...) - same as `println` but instead outputs it to the `out` file stream.

## Example

``` c
#include "print.h"

#define bool(x) (_Bool)x
#define char(x) (char)x

int main(void) {
    /* Printing without a newline */
    print("Here are a few examples: ");
    
    /* Appending to the previous one and printing with a newline */
    /* bool and char need a cast, since C uses int by default */
    println("int: {}, bool: {}, char: {}, string: {}", 21, bool(0), char('a'), "bazinga");
    
    /* Printing an error with println_to */
    println_to(stderr, "Error: Bad coding style - {}", bool(1));
}
```

Output:

    Here are a few examples: int: 21, bool: false, char: a, string: bazinga
    Error: Bad coding style - true


## Compiling

This project requires a conforming C23 compiler (due to `__VA_OPT__`) but can also work with:
 - GCC 8+
 - Clang 6+
 - MSVC 2019+

For MSVC, enable /Zc:preprocessor and /std:c11

## Feedback

This is experimental, most of the features (positional arguments, additional formatting, float-to-string conversion, etc.) are missing.

It is also not optimized for performance (uses standard print functions instead of OS syscalls).

Still, I'd appreciate if you [open an issue](https://github.com/steampuker/print.c/issues).

## Related

This project is largely based on [fmt](https://github.com/fmtlib/fmt) library.

## License

print.c is [Public Domain](https://unlicense.org/)


