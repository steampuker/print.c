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
