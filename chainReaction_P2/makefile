compile:
	g++ GridPosition.cpp -c -Wall
	g++ Board.cpp -c -Wall
	g++ BoardMaker.cpp -c -Wall
	g++ BoardSolver.cpp -c -Wall
	g++ driver.cpp Board.o GridPosition.o BoardMaker.o BoardSolver.o -Wall -o driver.exe

run:
	./driver.exe

clean:
	del *.o
	del *.exe