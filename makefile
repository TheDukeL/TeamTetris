executable: main.o  #TARGET,  PREREQs
        @g++ -std=c++11 -o Tetris main.o #COMMAND
main.o: main.cpp  #TARGET,  PREREQs
        @g++ -std=c++11 -c main main.cpp #COMMAND

cleanup:
        echo "Cleaning up object files!" #output to screen
        rm *.o
