3tXc4:	main.o grid.o ui.o
		g++ main.o grid.o -lpdcurses -o 3tXc4
ui.o:	ui.cpp ui.hpp
		g++ -c ui.cpp
main.o:	main.cpp grid.hpp
		g++ -c main.cpp
grid.o:	grid.cpp grid.hpp
		g++ -c grid.cpp
clean:
		rm -rvf *.o 3tXc4