cc -o grid main.c utils.c -Wall -lraylib -lm -ldl -lrt -lX11
cc -Wall -fPIC -shared -o rendering.so rendering.c utils.c
cc -Wall -fPIC -shared -o logic.so logic.c utils.c
#cc -Wall -fPIC -shared -o utils.so utils.c
