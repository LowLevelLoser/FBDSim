#include <stdio.h>

// Exported function to get library name
char *get_library_name() {
    return "I add 2 to ints";
}

// Exported function to perform the operation
__attribute__((visibility("default")))
int do_op(int i) {
    return i + 2;
}


//char *get_library_name(){
//    return "I add 2 to ints";
//}
//
//int do_op(int i){
//    return i+2;
//}
