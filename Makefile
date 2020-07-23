CXX = g++
CFLAGS = -std=c++11 
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

build:
	$(CXX) $(CFLAGS) -c src/*.cpp -I ~/SFML/include && $(CXX) *.o -o sfml-app $(CFLAGS) -L ~/SFML/lib $(SFML_FLAGS)

clean:
	rm *.o
