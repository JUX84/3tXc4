#========== 3tXtc4 makefile ==========#

3tXc4:	main.o grid.o ui.o
		g++ main.o grid.o ui.o -lncurses -o 3tXc4   # Compiling 3tXc4 executable

ui.o:	ui.cpp ui.hpp misc.hpp grid.hpp
		g++ -c ui.cpp   # Compiling UI object

main.o:	main.cpp ui.hpp
		g++ -c main.cpp     # Compiling main object

grid.o:	grid.cpp grid.hpp
		g++ -c grid.cpp     # Compiling grid object

clean:
		rm -rvf *.o 3tXc4   # Removing object files and executable

#========== makefile end ==========#
