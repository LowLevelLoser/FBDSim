#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
    if(argc < 3){
        printf("usage %s <library> <number>\n", argv[0]);
        exit(1);
    }

    char* librarypath = argv[1];
    int thenum = atoi(argv[2]);


    void* libhandle = dlopen(librarypath, RTLD_LAZY);

    if(libhandle == NULL){
        fprintf(stderr, "Error opening library: %s\n", dlerror());
        perror("dlopen");
        exit(1);
    }

    int (*opfunc) (int);
    opfunc = dlsym(libhandle, "do_operation");
    printf("fuku\n");

    printf("%d --> %d\n", thenum, opfunc(thenum));
    //printf("%d --> %d\n", thenum, opfunc(thenum));

    dlclose(libhandle);
}
