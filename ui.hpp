#ifndef _UI_HPP_
#define _UI_HPP_

class grid;

void ui ( void );
void play ( grid G , int size , int alignWinSize , int alignWinTotal );
void options ( int &defaultheight , int &defaultWidth , int &defaultAlignWinSize , int &defaultAlignWinTotal );
bool warnExit ( void );

#endif
