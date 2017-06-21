soChess: main.cpp
	gcc -o soChess main.cpp -lncurses -lstdc++

test: soChess
	./soChess
