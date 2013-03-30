#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <iostream>
#include "pdcurses/curses.h"
#include "misc.hpp"

class grid {

	private:
		int **XO;
		int size;
		int alignWinSize;
		int alignWinTotal;

	public:
		grid ( void );
		grid ( int newSize , int newAlignWinSize , int newAlignWinTotal );
		//grid ( std::string file );
		~grid ( void );
		void draw ( void );
		void gravitate ( void );
		void play ( int player );
		void rotate ( bool clockwise );
		void insert ( int player , int pos );
		int checkWin ( void );

	protected:

};

#endif
