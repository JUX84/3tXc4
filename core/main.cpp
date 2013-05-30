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

#include <ncurses.h>
#include "ui/ui.hpp"

int main ( int argc , char **argv ) {

	initscr (); // ncurses screen init
	timeout ( -1 ); // disable getch timeout
	raw (); // disable buffer
	keypad ( stdscr , TRUE ); // enable arrow keys
	noecho (); // disable getch echo
	curs_set ( 0 ); // disable cursor blinking

	ui (); // main menu

	return 0;
}
