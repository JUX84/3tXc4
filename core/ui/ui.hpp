#ifndef _UI_HPP_
#define _UI_HPP_

#include <stdint.h>

class grid;

void ui ( void );
void play ( grid G , uint8_t size , uint8_t alignWinSize , uint8_t alignWinTotal , bool vsAI , uint8_t AI_prof );
void options ( uint8_t &defaultheight , uint8_t &defaultWidth , uint8_t &defaultAlignWinSize , uint8_t &defaultAlignWinTotal , uint8_t &defaultAI_prof);
bool warnExit ( void );

#endif
