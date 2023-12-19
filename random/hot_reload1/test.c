// https://www.youtube.com/watch?v=_kIa4D7kQ8I

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//typedef int (*op_ptr)(int) ;

int main(int argc, char *argv[]) {
    if(argc < 3){
        printf("usage %s <library> <number>\n", argv[0]);
        exit(1);
    }

    char* librarypath = argv[1];
    int thenum = atoi(argv[2]);

    void* libhandle = dlopen(librarypath, RTLD_LAZY);
    if(libhandle == NULL){
        perror("dlopen");
    }

    //op_ptr opfunc;
    //opfunc = dlsym(libhandle, "do_op");

    //op_ptr opfunc = dlsym(libhandle, "do_op");
    int (*opfunc) (int);
    opfunc = dlsym(libhandle, "do_op");
    if (opfunc == NULL) {
        fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
        dlclose(libhandle);
        exit(1);
    }

    printf("%d --> %d\n", thenum, opfunc(thenum));

    dlclose(libhandle);

    return EXIT_SUCCESS;
}
