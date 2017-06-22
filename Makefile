soChess: main.cpp
	gcc -o soChess main.cpp boardClear.cpp boardState.cpp figureGenerator.cpp -lncurses -lstdc++ -std=gnu++11 -pthread

test: soChess
	./soChess
