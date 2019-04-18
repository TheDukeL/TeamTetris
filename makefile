CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
SFFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

all: *.h
	$(CXX) $(CXXFLAGS) -c *.o -Iinclude $(GTKFLAGS)

ex: main.o
	$(CXX) $(CXXFLAGS) -o Tetris *.o -Llib $(SFFLAGS) $(GTKFLAGS)

run: Tetris
		export LD_LIBRARY_PATH=lib && ./Tetris

cleanup:
		@echo "Cleaning up object files and executable!"
		rm *.o
		rm Tetris
