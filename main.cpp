#include "pdcurses/curses.h"
#include "ui.hpp"

int main ( int argc , char **argv ) {

    initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	while ( true ) {

        int Key = getch ();

        int row,col;

        getmaxyx(stdscr,row,col);

        clear ();

        mvprintw(row/2,col/2,"%d",Key);

        refresh ();

	}

	ui ();

	return 0;
}
