clang++ `sdl2-config --libs --cflags`  \
        -I/usr/local/include           \
        -L/usr/local/lib               \
        -llua                          \
        -lSDL2_image                   \
        -lSDL2_ttf                     \
        -llua                          \
        src/*.cpp
