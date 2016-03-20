CXX = clang++
SDL = -framework SDL2
OPENGL = -framework OpenGL
BOX2D = -lBox2D

CXXFLAGS = -F/Library/Frameworks -I/Users/avibrenner/Documents/Projects/Box2D/Box2D -Wall -c -std=c++11
LDFLAGS = -F/Library/Frameworks -L/usr/local/lib $(SDL) $(OPENGL) $(BOX2D)
LIBS = $(BOX2D)
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
