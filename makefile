CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
SFFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

all:
	@$(CXX) -c *.cpp $(GTKFLAGS)						# Compile all object files
	@$(CXX) -o Tetris *.o $(SFFLAGS) $(GTKFLAGS)		# Compile excutable

portable:												# Portable version for machine without sfml installed
	@$(CXX) -c *.cpp -Iinclude $(GTKFLAGS)				# Compile all object files
	@$(CXX) -o Tetris *.o -Llib $(SFFLAGS) $(GTKFLAGS)	# Compile excutable
	
run: Tetris
	@export LD_LIBRARY_PATH=lib && ./Tetris				# Run game on machine without sfml installed
		
cleanup:
	@rm *.o
	@rm Tetris