#========== 3tXtc4 makefile ==========#

3tXc4:	main.o grid.o ui.o
		@g++ main.o grid.o ui.o -lncurses -o 3tXc4 ; $(info #***** Compiling 3tXc4 executable *****#)

ui.o:	ui.cpp ui.hpp misc.hpp grid.hpp
		@g++ -c ui.cpp ; $(info #***** Compiling UI object *****#)

grid.o:	grid.cpp grid.hpp
		@g++ -std=c++0x -c grid.cpp ; $(info #***** Compiling grid object *****#)
        
main.o:	main.cpp ui.hpp
		@g++ -c main.cpp ; $(info #***** Compiling main object *****#)

clean:
		@rm -rvf *.o 3tXc4 ; $(info #***** Removing object files and executable *****#)

#========== makefile end ==========#
