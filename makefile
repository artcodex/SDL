CXX = clang++
SDL = -framework SDL2
OPENGL = -framework OpenGL

CXXFLAGS = -F/Library/Frameworks -Wall -c -std=c++11
LDFLAGS = -F/Library/Frameworks $(SDL) $(OPENGL)
EXE = test

all: $(EXE)

$(EXE): test.o rectangle.o texturedrectangle.o shape.o coordinatehelper.o
				$(CXX) $(LDFLAGS) $^ -o $@

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
