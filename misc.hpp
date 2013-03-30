#ifndef _MISC_HPP_
#define _MISC_HPP_

#ifdef _WIN32

#include <windows.h>

#define wait(a) Sleep(a)

#else

#include <unistd.h>

#define wait(a) usleep(a*1000)

#endif

#include <iostream>
#include <cstring>

#define ENTER 13
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


inline void endLine ( int endl ) {

	int i;

	for ( i = 0 ; i < endl ; ++i )
		std::cout << std::endl;
}

inline void tab ( int space ) {

	int i;

	for ( i = 0 ; i < space ; ++i )
		std::cout << " ";
}

#endif
