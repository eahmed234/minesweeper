linux:
	g++ -c *.cpp
	g++ *.o -o minesweeper.out -lsfml-graphics -lsfml-window -lsfml-system
	rm -r *.o