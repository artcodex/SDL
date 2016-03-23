CXX = clang++
LD = /usr/i686-pc-mingw32/bin/ld
SDL = -lSDL2
OPENGL = -lopengl32
BOX2D = -lBox2D
GLEW = -lGlew32

CXXFLAGS = -IC:\Source\Projects\Box2D\Box2D -IC:\Users\abrenner\Downloads\SDL2-devel-2.0.4-VC\SDL2-2.0.4\include -IC:\Users\abrenner\Downloads\glew-1.13.0-win32\glew-1.13.0\include -Wall -c -std=c++11
LDFLAGS = -L.\libs
LIBS = $(BOX2D) $(SDL) $(OPENGL) $(GLEW)
EXE = test
EXE_DETAIL = testd

all: $(EXE)

$(EXE): test.o rectangle.o texturedrectangle.o shape.o coordinatehelper.o
				$(CXX) $(LDFLAGS) $^ -o $@ $(LIBS)

$(EXE_DETAIL): test.o rectangle.o texturedrectangle.o shape.o coordinatehelper.o
				$(CXX) $(LDFLAGS) $^ -o $@ -v $(LIBS)

test.o: test.cpp
				$(CXX) $(CXXFLAGS) $< -o $@

rectangle.o: Rectangle.cpp
				$(CXX) $(CXXFLAGS) $< -o $@

texturedrectangle.o: TexturedRectangle.cpp
				$(CXX) $(CXXFLAGS) $< -o $@

shape.o: Shape.cpp
				$(CXX) $(CXXFLAGS) $< -o $@

coordinatehelper.o: CoordinateHelper.cpp
				$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
