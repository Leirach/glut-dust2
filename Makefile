CC = clang++
CFLAGS = -std=c++11 -stdlib=libc++ -lglfw -Wall -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon
f = triangulo

all: opengl

opengl: $(f).cpp
	$(CC) -o $(f) $(CFLAGS) $(f).cpp 
