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
