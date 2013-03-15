3tXc4:	main.o grid.o
		g++ main.o grid.o -o 3tXc4
main.o:	main.cpp grid.hpp
		g++ -c main.cpp
grid.o:	grid.cpp grid.hpp
		g++ -c grid.cpp
clean:
		rm -rvf *.o 3tXc4