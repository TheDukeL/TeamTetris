CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
SFFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

all:
	$(CXX) -c *.cpp $(GTKFLAGS)
	$(CXX) -o tetris *.o $(SFFLAGS) $(GTKFLAGS)
	
cleanup:
	rm *.o
	rm tetris