W32=i686-w64-mingw32-g++

SOURCES=main.cpp
CFLAGS=-Wall
LDFLAGSW32=-Xlinker --enable-auto-import -lSDL2_image -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static

EXECUTABLE=sdltest.exe

all: $(SOURCES)
	$(W32) $(SOURCES) $(LDFLAGSW32) $(CFLAGS) -o $(EXECUTABLE)
