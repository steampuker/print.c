# print.c
A proof-of-concept print macro that supports Python-style formatting. 

Automatically infers argument types (for now, only `int`, `_Bool` and `char` are supported).

## Usage

print.c adds two macros:
 - print(string, args...) - formats `string` replacing `"{}"` with `args` and prints it to the standard output.
 - printn(string, args...) - same as `print` but with a newline. 

## Example

``` c
#include "print.h"

int main(void) {
    printn("Hello every {}!", 1);
}
```

Output:

    Hello every 1!


## Compiling

This project requires a conforming C23 compiler (due to `__VA_OPT__`) but can also work with:
 - GCC 8+
 - Clang 6+
 - MSVC 2019+

For MSVC, enable /Zc:preprocessor and /std:c11

## Feedback

This project is experimental, most of the features (positional arguments, additional formatting, float-to-string conversion, etc.) are missing.

The performance is also not great, about 10 times slower than a regular printf.

Still, I'd appreciate if you [open an issue](https://github.com/steampuker/print.c/issues).

## Related

This project is based on [fmt](https://github.com/fmtlib/fmt) library.
