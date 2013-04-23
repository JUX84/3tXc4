#ifndef _MISC_HPP_
#define _MISC_HPP_

#include <unistd.h>

#define wait(a) usleep(a*1000)

#include <iostream>
#include <cstring>
#include <stdint.h>

#define ENTER 10
#define ESC 27

#define KEY_C 99
#define KEY_E 101
#define KEY_H 104
#define KEY_I 105
#define KEY_N 110
#define KEY_O 111
#define KEY_P 112
#define KEY_R 114
#define KEY_S 115
#define KEY_T 116
#define KEY_W 119
#define KEY_Y 121
#define KEY_V 118
#define KEY_L 108

static std::string STR_OPTIONS ( "[O]PTIONS" );
static std::string STR_TITLE_GAME ( "__3tXc4__" );
static std::string STR_TITLE_OPTIONS ( "_OPTIONS_" );
static std::string STR_PLAY ( "[P]LAY!" );
static std::string STR_EXIT ( "[E]XIT" );
static std::string STR_INSERT ( "[I]NSERT" );
static std::string STR_ROTATE ( "[R]OTATE" );
static std::string STR_P1 ( "Player 1 !" );
static std::string STR_P2 ( "Player 2 !" );
static std::string STR_WIN_P1 ( "Player 1 has won!" );
static std::string STR_WIN_P2 ( "Player 2 has won!" );
static std::string STR_CONTINUE ( "Press any key to continue ([E]SC to quit) ..." );
static std::string STR_ARROW_LEFT ( "<-" );
static std::string STR_ARROW_RIGHT ( "->" );
static std::string STR_TIE ( "It's a tie..." );
static std::string STR_WARN_EXIT ( "ARE YOU SURE?" );
static std::string STR_WARN_YES ( "[Y]ES" );
static std::string STR_WARN_NO ( "[N]O" );
static std::string STR_HELP ( "PRESS [F1] FOR HELP" );
static std::string STR_HEIGHT ( "[H]EIGHT" );
static std::string STR_WIDTH ( "[W]IDTH" );
static std::string STR_ALIGN_SIZE ( "ALIGNMENT [S]IZE" );
static std::string STR_ALIGN_TOTAL ( "ALIGNMENT [T]OTAL" );
static std::string STR_OK ( "[O]K" );
static std::string STR_CANCEL ( "[C]ANCEL" );
static std::string STR_CLOCKWISE ( "CLOCK[W]ISE" );
static std::string STR_CCLOCKWISE ( "[C]OUNTER-CLOCKWISE" );
static std::string STR_1N1 ( "NEW PLAYER [V]ERSUS PLAYER" );
static std::string STR_1NAI ( "NEW PLAYER VERSUS [A]I" );
static std::string STR_LOAD ( "[L]OAD GAME" );
static std::string STR_PLAY_MENU ( "__PLAY MENU__" );
static std::string STR_FAIL_LOAD ( "FAILED TO OPEN FILE" );
static std::string STR_SAVE ( "PRESS F1 TO SAVE" );
static std::string STR_SAVE_QUIT ( "PRESS F2 TO SAVE & QUIT" );
static std::string STR_NO_SAVE ( "CAN'T FIND ANY SAVED GAME" );
static std::string STR_LOAD_MENU ( "__LOAD_GAME__" );
static std::string STR_SAVE_EMPTY ( "THE SAVE INDEX FILE WAS EMPTY" );
static std::string STR_SAVE_REP ( "saves" );
static std::string STR_SAVE_PRE ( "game" );
static std::string STR_SAVE_EXT ( "sav" );
static std::string STR_SAVE_CHK ( "check" );
static std::string STR_SAVE_IND ( "index" );

static void _debug8_t ( std::string name , uint8_t value , uint16_t time ) { // prints the desired value ant its name in the middle of the screen during a period of time

	uint8_t row , col;
	getmaxyx ( stdscr , row , col );
	clear ();
	mvprintw ( row / 2 , ( col - name.length () + 1 ) / 2 , name.c_str () );
	printw ( " %d" , value );
	refresh ();
	wait ( time );
}

static void _debug16_t ( std::string name , uint16_t value , uint16_t time ) {

	uint8_t row , col;
	getmaxyx ( stdscr , row , col );
	clear ();
	mvprintw ( row / 2 , ( col - name.length () + 1 ) / 2 , name.c_str () );
	printw ( " %d" , value );
	refresh ();
	wait ( time );
}

#endif
