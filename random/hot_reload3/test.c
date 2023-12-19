// https://www.youtube.com/watch?v=_kIa4D7kQ8I

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*op_ptr)(int) ;

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
        exit(1);
    }

    //op_ptr opfunc;
    //opfunc = dlsym(libhandle, "do_op");

    //op_ptr opfunc = dlsym(libhandle, "do_op");
    op_ptr opfunc;

    opfunc = dlsym(libhandle, "do_op");
    if (opfunc == NULL) {
        fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
        dlclose(libhandle);
        exit(1);
    }

    char str[2];
    while(1){
        fgets(str, 2, stdin);
        if(str[0] == 'q'){
            break;
        }
        if(str[0] == 'p'){
            printf("%d --> %d\n", thenum, opfunc(thenum));
        }
        else if(str[0] == 'r'){
            dlclose(libhandle);
            printf("reload\n");
            libhandle = dlopen(librarypath, RTLD_LAZY);
            if(libhandle == NULL){
                perror("dlopen");
            }
            opfunc = dlsym(libhandle, "do_op");
            if (opfunc == NULL) {
                fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
                dlclose(libhandle);
                exit(1);
            }
        }
    }


    dlclose(libhandle);

    return EXIT_SUCCESS;
}
