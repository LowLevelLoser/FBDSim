#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

typedef void (*HelloFunction)();

int main() {
    void *libraryHandle;
    HelloFunction hello;

    while (1) {
        // Load the shared library
        libraryHandle = dlopen("./mylibrary.so", RTLD_LAZY);
        if (!libraryHandle) {
            fprintf(stderr, "Error loading library: %s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        // Load the function from the library
        hello = (HelloFunction)dlsym(libraryHandle, "hello");
        if (!hello) {
            fprintf(stderr, "Error loading function: %s\n", dlerror());
            dlclose(libraryHandle);
            exit(EXIT_FAILURE);
        }

        // Call the function
        hello();

        // Unload the library
        dlclose(libraryHandle);

        // Sleep for a while before reloading
        sleep(2);
    }

    return 0;
}

