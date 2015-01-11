CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
  CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
  LDFLAGS = -framework GLUT -framework OpenGL \
      -L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
      -lGL -lGLU -lm -lstdc++
else
  CFLAGS = -g -std=c++0x -DGL_GLEXT_PROTOTYPES -I./include/ -Iglut-3.7.6-bin
  LDFLAGS = -lglut -lGLU
endif

OBJECTS = viewport.o lodepng.o color.o light.o vector.o circle.o

RM = /bin/rm -f
all: main
main: example_01.o $(OBJECTS)
	$(CC) $(CFLAGS) -o as1 example_01.o $(LDFLAGS) $(OBJECTS)
example_01.o: src/example_01.cpp
	$(CC) $(CFLAGS) -c src/example_01.cpp -o example_01.o
viewport.o: src/viewport.cpp
	$(CC) $(CFLAGS) -c src/viewport.cpp -o viewport.o 
lodepng.o: lodepng/lodepng.cpp
	$(CC) $(CFLAGS) -c lodepng/lodepng.cpp -o lodepng.o
light.o: src/light.cpp
	$(CC) $(CFLAGS) -c src/light.cpp -o light.o
color.o: src/color.cpp
	$(CC) $(CFLAGS) -c src/color.cpp -o color.o
vector.o: src/vector.cpp
	$(CC) $(CFLAGS) -c src/vector.cpp -o vector.o
circle.o: src/circle.cpp
	$(CC) $(CFLAGS) -c src/circle.cpp -o circle.o
clean:
	$(RM) *.o as1
