TARGET = guildwars

CXX    = g++
CFLAGS = -Wall -g -std=c++11 -Wno-deprecated

# Windows builds
ifeq ($(OS), Windows_NT)
	INCPATH += -IC:/Strawberry/c/include/
	LIBS = -lglut -lopengl32 -lglu32 -LC:/Strawberry/c/lib/

# Mac builds
else ifeq ($(shell uname), Darwin)
	LIBS = -framework GLUT -framework OpenGL -framework Cocoa -lpthread

# Linux and all other builds
else
	LIBS = -lglut -lGL -lGLU
endif

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)

depend:
	rm -f Makefile.bak
	mv Makefile Makefile.bak
	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
	echo '# DEPENDENCIES' >> Makefile
	$(CXX) -MM *.cpp >> Makefile

.c.o:
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cc.o:
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

$(TARGET): main.o Camera.o Drawable.o Tree.o Point.o BezierCurve.o Vector2.o Vector3.o
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)

# DEPENDENCIES
%.o : %.cpp
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<
