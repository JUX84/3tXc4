/*
 * ------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <mehdi.mhiri@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Mehdi Mhiri
 * ------------------------------------------------------------------------------
 * License originally written by Poul-Henning Kamp <phk@FreeBSD.ORG>
 * ------------------------------------------------------------------------------
 */

#ifndef _UI_HPP_
#define _UI_HPP_

#include <stdint.h>

class grid;

void ui ( void );
void play ( grid G , uint8_t size , uint8_t alignWinSize , uint8_t alignWinTotal , bool vsAI , uint8_t AI_prof );
void options ( uint8_t &defaultheight , uint8_t &defaultWidth , uint8_t &defaultAlignWinSize , uint8_t &defaultAlignWinTotal , uint8_t &defaultAI_prof);
bool warnExit ( void );

#endif
