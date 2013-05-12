#========== FLAGS ==========#

OBJ=obj/
BIN=bin/
CORE=core/
UI=ui/
GRID=grid/
MISC=misc/
SAV=saves/
CPP0X=-std=c++0x
IBIN=***** Compiling 3tXc4 binary *****
IUI=***** Compiling UI object *****
IGRID=***** Compiling grid objet *****
IMAIN=***** Compiling main objet *****
IRM=***** Removing object files and binary *****
W=-Wall
P=-pedantic

#========== 3tXtc4 MAKEFILE ==========#

$(BIN)3tXc4.bin:	$(OBJ)main.o $(OBJ)grid.o $(OBJ)ui.o
	@g++ $(W) $(P) $(OBJ)main.o $(OBJ)grid.o $(OBJ)ui.o -lncurses -o $(BIN)3tXc4.bin ; $(info $(IBIN))

$(OBJ)ui.o:		$(CORE)$(UI)ui.cpp $(CORE)$(UI)ui.hpp $(CORE)$(MISC)misc.hpp $(CORE)$(GRID)grid.hpp
	@g++ $(W) $(P) -c $(CORE)$(UI)ui.cpp -o $(OBJ)ui.o ; $(info $(IUI))

$(OBJ)grid.o:		$(CORE)$(GRID)grid.cpp $(CORE)$(GRID)grid.hpp $(CORE)$(MISC)misc.hpp
	@g++ $(W) $(P) $(CPP0X) -c $(CORE)$(GRID)grid.cpp -o $(OBJ)grid.o ; $(info $(IGRID))

$(OBJ)main.o:		$(CORE)main.cpp $(CORE)$(UI)ui.hpp $(CORE)$(MISC)misc.hpp
	@g++ $(W) $(P) -c $(CORE)main.cpp -o $(OBJ)main.o ; $(info $(IMAIN))

clean:
	@rm -rvf $(OBJ)*.o $(BIN)3tXc4.bin $(BIN)$(SAV)game* $(BIN)$(SAV)index.sav ; $(info $(IRM))

#========== MAKEFILE END ==========#
