#ifndef _UI_HPP_
#define _UI_HPP_

#include "pdcurses/curses.h"
#include "misc.hpp"
#include "grid.hpp"

void ui ( void );
void play ( int size , int alignWinSize , int alignWinTotal );
void options ( int &defaultheight , int &defaultWidth , int &defaultAlignWinSize , int &defaultAlignWinTotal );
bool warnExit ( void );

#endif
