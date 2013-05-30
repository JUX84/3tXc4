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
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include "ui.hpp"
#include "../grid/grid.hpp"
#include "../misc/misc.hpp"

bool warnExit ( void ) { // exit warning menu

	uint8_t selected ( 1 );
	std::string STR_SELECTED;
	uint8_t TAB;
	int32_t Key;
	uint8_t row , col;

	while ( true ) {

		if ( selected < 1 )
			selected = 1;

		if ( selected > 2 )
			selected = 2;

		switch ( selected ) {

			case 1:
				STR_SELECTED = STR_WARN_YES;
				TAB = 1;
				break;

			case 2:
				STR_SELECTED = STR_WARN_NO;
				TAB = 2;
				break;
		}

		getmaxyx ( stdscr , row , col ); // get number of rows and columns in terminal

		clear (); // clears screen

		attron ( A_BOLD ); // enable bold style

		mvprintw ( row / 3 , ( col - STR_WARN_EXIT.length () + 1 ) / 2 , STR_WARN_EXIT.c_str () ); // prints text on desired position

		mvprintw ( 2 * row / 3 , ( TAB * col / 3 ) - STR_SELECTED.length () - 2 , STR_ARROW_RIGHT.c_str () );
		mvprintw ( 2 * row / 3 , ( TAB * col / 3 ) + STR_SELECTED.length () , STR_ARROW_LEFT.c_str () );

		attroff ( A_BOLD ); // disable bold style

		mvprintw ( 2 * row / 3 , ( col / 3 ) - ( STR_WARN_YES.length () / 2 ) , STR_WARN_YES.c_str () );
		mvprintw ( 2 * row / 3 , ( 2 * col / 3 ) - ( STR_WARN_NO.length () / 2 ) , STR_WARN_NO.c_str () );

		refresh (); // prints the text placed with mvprintw on screen

		Key = getch ();

		if ( Key == KEY_RIGHT )
			selected++;

		if ( Key == KEY_LEFT )
			selected--;

		if ( Key == ENTER ) {

			if ( selected == 1 )
				return true;

			if ( selected == 2 )
				return false;
		}

		if ( Key == KEY_Y )
			return true;

		if ( Key == KEY_N || Key == ESC )
			return false;
	}
}

void options_help ( void ) { // options help menu

}

void options ( uint8_t &defaultHeight , uint8_t &defaultWidth , uint8_t &defaultAlignWinSize , uint8_t &defaultAlignWinTotal , uint8_t &defaultAI_prof ) { // options menu

	uint8_t selected ( 1 );
	uint8_t i;
	uint8_t row , col;
	uint8_t backupHeight ( defaultHeight );
	uint8_t backupWidth ( defaultWidth );
	uint8_t backupAlignWinSize ( defaultAlignWinSize );
	uint8_t backupAlignWinTotal ( defaultAlignWinTotal );
	uint8_t backupAI_prof ( defaultAI_prof );
	int32_t Key;
	std::string STR_SELECTED;

	while ( true ) {

		getmaxyx ( stdscr , row , col );

		if ( selected < 1 )
			selected = 1;

		if ( selected > 5 )
			selected = 5;

		if ( defaultHeight < 3 )
			defaultHeight = 3;

		if ( defaultHeight > 20 )
			defaultHeight = 20;

		if ( defaultWidth < 3 )
			defaultWidth = 3;

		if ( defaultWidth > 20 )
			defaultWidth = 20;

		if ( defaultAlignWinSize > defaultWidth )
			defaultAlignWinSize = defaultWidth;

		if ( defaultAlignWinSize > defaultHeight )
			defaultAlignWinSize = defaultHeight;

		if ( defaultAlignWinSize < 3 )
			defaultAlignWinSize = 3;

		if ( defaultAlignWinTotal < 1 )
			defaultAlignWinTotal = 1;

		if ( defaultAlignWinTotal > 10 )
			defaultAlignWinTotal = 10;

		if ( defaultAI_prof < 3 )
			defaultAI_prof = 9;

		if ( defaultAI_prof > 9 )
			defaultAI_prof = 3;

		switch ( selected ) {

			case 1:
				STR_SELECTED = STR_HEIGHT;
				break;

			case 2:
				STR_SELECTED = STR_WIDTH;
				break;

			case 3:
				STR_SELECTED = STR_ALIGN_SIZE;
				break;

			case 4:
				STR_SELECTED = STR_ALIGN_TOTAL;
				break;

			case 5:
				STR_SELECTED = STR_AI_PROF;
				break;
		}

		clear ();

		attron ( A_BOLD );

		mvprintw ( row / 4 , ( col - STR_TITLE_OPTIONS.length () + 1 ) / 2 , STR_TITLE_OPTIONS.c_str () );

		mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , col / 20 , STR_ARROW_RIGHT.c_str () );
		mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , 19 * col / 20 , STR_ARROW_LEFT.c_str () );

		mvprintw ( 2 , 2 , STR_HELP.c_str () );

		attroff ( A_BOLD );

		mvprintw ( ( row / 2 ) , ( col - STR_HEIGHT.length() + 1 ) / 3 , STR_HEIGHT.c_str() );
		mvprintw ( ( row / 2 ) + 2 , ( col - STR_WIDTH.length() + 1 ) / 3 , STR_WIDTH.c_str() );
		mvprintw ( ( row / 2 ) + 4 , ( col - STR_ALIGN_SIZE.length() + 1 ) / 3 , STR_ALIGN_SIZE.c_str() );
		mvprintw ( ( row / 2 ) + 6 , ( col - STR_ALIGN_TOTAL.length() + 1 ) / 3 , STR_ALIGN_TOTAL.c_str() );
		mvprintw ( ( row / 2 ) + 8 , ( col - STR_AI_PROF.length () + 1 ) / 3 , STR_AI_PROF.c_str () );

		mvprintw ( ( row / 2 ) , ( col / 2 ) , "%d" , defaultHeight );
		mvprintw ( ( row / 2 ) , ( col / 2 ) + ( col / 20 ) , "[" );
		for ( i = 0 ; i < defaultHeight ; ++i )
			printw ( "-" );
		for ( i = 20 ; i > defaultHeight ; --i )
			printw ( " " );
		printw ( "]" );

		mvprintw ( ( row / 2 ) + 2 , ( col / 2 ) , "%d" , defaultWidth );
		mvprintw ( ( row / 2 ) + 2 , ( col / 2 ) + ( col / 20 ) , "[" );
		for ( i = 0 ; i < defaultWidth ; ++i )
			printw ( "-" );
		for ( i = 20 ; i > defaultWidth ; --i )
			printw ( " " );
		printw ( "]" );

		mvprintw ( ( row / 2 ) + 4 , ( col / 2 ) , "%d" , defaultAlignWinSize );
		mvprintw ( ( row / 2 ) + 4 , ( col / 2 ) + ( col / 20 ) , "[" );
		for ( i = 0 ; i < defaultAlignWinSize ; ++i )
			printw ( "-" );
		for ( i = 20 ; i > defaultAlignWinSize ; --i )
			printw ( " " );
		printw ( "]" );

		mvprintw ( ( row / 2 ) + 6 , ( col / 2 ) , "%d" , defaultAlignWinTotal );
		mvprintw ( ( row / 2 ) + 6 , ( col / 2 ) + ( col / 20 ) , "[" );
		for ( i = 0 ; i < defaultAlignWinTotal ; ++i )
			printw ( "--" );
		for ( i = 10 ; i > defaultAlignWinTotal ; --i )
			printw ( "  " );
		printw ( "]" );

		switch ( defaultAI_prof ) {

			case 3:
				mvprintw ( ( row / 2 ) + 8 , ( col / 2 ) + ( col / 20 ) + 9 , "EASY" );
				break;

			case 6:
				mvprintw ( ( row / 2 ) + 8 , ( col / 2 ) + ( col / 20 ) + 8 , "MEDIUM" );
				break;

			case 9:
				mvprintw ( ( row / 2 ) + 8 , ( col / 2 ) + ( col / 20 ) + 9 , "HARD" );
				break;
		}

		mvprintw ( row - 2 , ( col - STR_OK.length () + 1 ) / 4 , STR_OK.c_str () );
		mvprintw ( row - 2 , 3 * ( col - STR_CANCEL.length () + 1 ) / 4 , STR_CANCEL.c_str () );

		refresh ();

		Key = getch ();

		if ( Key == KEY_LEFT ) {

			switch ( selected ) {

				case 1:
					defaultHeight--;
					break;

				case 2:
					defaultWidth--;
					break;

				case 3:
					defaultAlignWinSize--;
					break;

				case 4:
					defaultAlignWinTotal--;
					break;

				case 5:
					defaultAI_prof -= 3;
					break;
			}
		}

		if ( Key == KEY_RIGHT ) {

			switch ( selected ) {

				case 1:
					defaultHeight++;
					break;

				case 2:
					defaultWidth++;
					break;

				case 3:
					defaultAlignWinSize++;
					break;

				case 4:
					defaultAlignWinTotal++;
					break;

				case 5:
					defaultAI_prof += 3;
					break;
			}
		}

		if ( Key == KEY_DOWN )
			selected++;

		if ( Key == KEY_UP )
			selected--;

		if ( Key == ENTER || Key == KEY_O )
			break;

		if ( Key == ESC || Key == KEY_C ) {

			defaultHeight = backupHeight;
			defaultWidth = backupWidth;
			defaultAlignWinSize = backupAlignWinSize;
			defaultAlignWinTotal = backupAlignWinTotal;
			defaultAI_prof = backupAI_prof;
			break;
		}

		if ( Key == KEY_F ( 1 ) )
			options_help ();
	}
}

void play ( grid *G , uint8_t height , uint8_t width , uint8_t alignWinSize , uint8_t alignWinTotal , bool vsAI , uint8_t AI_prof ) { // play menu

	if ( !grid::initXO ) { // if no game is loaded, create new one

		G = new grid ( height , width , alignWinSize , alignWinTotal , vsAI , AI_prof );
	}

	uint8_t win;
	int32_t Key;
	uint8_t row , col;

	while ( true ) {

		clear ();

		getmaxyx ( stdscr , row , col );

		attron ( A_BOLD );

		mvprintw ( 2 , 2 , STR_SAVE.c_str () ); // beginning of P1 turn, ask if wants to save
		mvprintw ( 2 , 5 + STR_SAVE.length () , STR_SAVE_QUIT.c_str() ); // or save & quit

		attroff ( A_BOLD );

		mvprintw ( row / 3 , ( col - STR_P1.length () + 1 ) / 2 , STR_P1.c_str () );

		mvprintw ( 2 * row / 3 , ( col - STR_CONTINUE.length () + 1 ) / 2 , STR_CONTINUE.c_str () );

		refresh ();

		Key = getch ();

		if ( Key == ESC || Key == KEY_E )
			break;

		if ( Key == KEY_F ( 6 ) )
			G->save ();

		if ( Key == KEY_F ( 7 ) ) {

			G->save ();
			break;
		}

		G->play ( 1 );
		G->gravitate ( false );

		win = G->checkWin ();

		clear ();

		if ( win == 1 ) {

			mvprintw ( row / 2 , ( col - STR_WIN_P1.length () + 1 ) / 2 , STR_WIN_P1.c_str () );

			refresh ();

			wait ( 2000 );

			break;
		}

		if ( win == 2 ) {

			mvprintw ( row / 2 , ( col - STR_WIN_P2.length () + 1 ) / 2 , STR_WIN_P2.c_str () );

			refresh ();

			wait ( 2000 );

			break;
		}

		if ( win == 3 ) { // in case of rotation, possibility of tie

			mvprintw ( row / 2 , ( col - STR_DRAW.length () + 1 ) / 2 , STR_DRAW.c_str () );

			refresh ();

			wait ( 2000 );

			break;
		}

		if ( !G->AI ) {

			mvprintw ( row / 3 , ( col - STR_P2.length () + 1 ) / 2 , STR_P2.c_str () );

			mvprintw ( 2 * row / 3 , ( col - STR_CONTINUE.length () + 1 ) / 2 , STR_CONTINUE.c_str () );

			refresh ();

			Key = getch ();

			if ( Key == ESC || Key == KEY_E )
				break;

			G->play ( 0 );

		}
		else
			G->AI_play();

		G->gravitate ( false );

		win = G->checkWin ();

		clear ();

		if ( win == 1 ) {

			mvprintw ( row / 2 , ( col - STR_WIN_P1.length () + 1 ) / 2 , STR_WIN_P1.c_str () );

			refresh ();

			wait ( 2000 );

			break;
		}

		if ( win == 2 ) {

			mvprintw ( row / 2 , ( col - STR_WIN_P2.length () + 1 ) / 2 , STR_WIN_P2.c_str () );

			refresh ();

			wait ( 2000 );

			break;
		}

		if ( win == 3 || G->full() ) {

			mvprintw ( row / 2 , ( col - STR_DRAW.length () + 1 ) / 2 , STR_DRAW.c_str () );

			refresh ();

			wait ( 2000 );

			break;
		}
	}
}

void load_menu () { // load game menu

	int32_t Key;
	uint8_t i;
	uint8_t row , col;
	uint16_t top ( 0 );
	uint8_t selected ( 1 );
	std::string currentID;
	std::list<std::string> listID;
	std::list<std::string>::reverse_iterator it;
	std::vector<std::string> vectorID;

	std::ifstream input ( "saves/index.sav" );
	if ( !input ) {

		getmaxyx ( stdscr , row , col );
		clear ();
		mvprintw ( row / 2 , ( col - STR_NO_SAVE.length () + 1 ) / 2 , STR_NO_SAVE.c_str() );
		refresh ();
		wait ( 2000 );
		return;
	}

	std::string buff;

	while ( !input.eof() ) {

		input >> buff;
		if ( buff != "" )
			listID.push_back(buff);
	}

	if ( listID.empty () ) {

		getmaxyx ( stdscr , row , col );
		clear ();
		mvprintw ( row / 2 , ( col - STR_SAVE_EMPTY.length () + 1 ) / 2 , STR_SAVE_EMPTY.c_str () );
		refresh ();
		wait ( 2000 );
		return;
	}

	while ( true ) {

		i = 0;

		if ( !vectorID.empty() )
			vectorID.clear();

		if ( selected < 1 ) {
			if ( top > 0 )
				top--;
			selected = 1;
		}

		if ( selected > 10 ) {

			if ( top < listID.size() )
				top++;
			selected = 10;
		}

		for ( it = listID.rbegin() ; it != listID.rend() ; ++it ) {

			currentID = (*it);

			if ( i > top + 10 )
				break;

			if ( i >= top ) {

				if ( std::find ( vectorID.rbegin () , vectorID.rend () , currentID ) == vectorID.rend () )
					vectorID.push_back( currentID );
			}

			++i;
		}

		if ( selected > vectorID.size() ) {

			selected = vectorID.size();
		}

		getmaxyx ( stdscr , row , col );

		clear ();

		attron ( A_BOLD );

		mvprintw ( row / 5 , ( col - STR_LOAD_MENU.length () + 1 ) / 2 , STR_LOAD_MENU.c_str () );

		mvprintw ( ( row / 3 ) + selected*2 - 2 , 5 * col / 20 , STR_ARROW_RIGHT.c_str () );
		mvprintw ( ( row / 3 ) + selected*2 - 2 , 15 * col / 20 , STR_ARROW_LEFT.c_str () );

		mvprintw ( 2 , 2 , STR_HELP.c_str () );

		attroff ( A_BOLD );

		for ( i = 0 ; i < vectorID.size () ; ++i ) {

			mvprintw ( ( row / 3 ) + ( i * 2 ) , ( col - 13 ) / 2 , vectorID[i].c_str() );
		}

		uint8_t current = selected - 1;
		currentID = vectorID[current];

		refresh ();

		Key = getch ();

		if ( Key == ENTER ) {

			grid *G = new grid ( currentID.c_str() );
			if ( grid::initXO ) {
				play ( G , 5 , 5 , 5 , 1 , G->AI , G->getAI_prof() );
				return;
			}
		}

		if ( Key == KEY_DOWN )
			selected++;

		if ( Key == KEY_UP )
			selected--;

		if ( Key == ESC )
			return;
	}

	return;
}

void play_menu ( uint8_t height , uint8_t width , uint8_t alignWinSize , uint8_t alignWinTotal , uint8_t AI_prof ) { // play game menu

	int32_t Key;
	uint8_t row , col;
	uint8_t selected ( 1 );

	while ( true ) {

		getmaxyx ( stdscr , row , col );

		if ( selected < 1 )
			selected = 1;

		if ( selected > 3 )
			selected = 3;

		clear ();

		attron ( A_BOLD );

		mvprintw ( row / 4 , ( col - STR_PLAY_MENU.length () + 1 ) / 2 , STR_PLAY_MENU.c_str () );

		mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , 5 * col / 20 , STR_ARROW_RIGHT.c_str () );
		mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , 15 * col / 20 , STR_ARROW_LEFT.c_str () );

		mvprintw ( 2 , 2 , STR_HELP.c_str () );

		attroff ( A_BOLD );

		mvprintw ( row / 2 , ( col - STR_1N1.length () + 1 ) / 2 , STR_1N1.c_str () );
		mvprintw ( ( row / 2 ) + 2 , ( col - STR_1NAI.length () + 1 ) / 2 , STR_1NAI.c_str () );
		mvprintw ( ( row / 2 ) + 4 , ( col - STR_LOAD.length () + 1 ) / 2 , STR_LOAD.c_str () );

		refresh();

		Key = getch ();

		if ( Key == KEY_DOWN )
			selected += 1;

		if ( Key == KEY_UP )
			selected -= 1;

		if ( Key == ENTER ) {

			if ( selected == 1 ) {

				grid *G = new grid ();
				play ( G , height , width , alignWinSize , alignWinTotal , false , AI_prof );
			}

			if ( selected == 2 ) {

				grid *G = new grid ();
				play ( G, height , width , alignWinSize , alignWinTotal , true , AI_prof );
			}

			if ( selected == 3 )
				load_menu ();

			break;
		}

		if ( Key == KEY_V ) {

			grid *G = new grid ();
			play ( G , height , width , alignWinSize , alignWinTotal , false , AI_prof );
		}

		if ( Key == KEY_A ) {

			grid *G = new grid ();
			play ( G , height , width , alignWinSize , alignWinTotal , true , AI_prof );
		}

		if ( Key == KEY_L )
			load_menu ();

		if ( Key == ESC )
			return;
	}
}

void ui_help ( void ) { // user interface help menu

}

void ui ( void ) { // main menu

	uint8_t selected ( 1 );
	uint8_t defaultHeight ( 5 );
	uint8_t defaultWidth ( 5 );
	uint8_t defaultAlignWinSize ( 5 );
	uint8_t defaultAlignWinTotal ( 1 );
	uint8_t defaultAI_prof ( 3 );
	int32_t Key;
	uint8_t row , col;

	while ( true ) {

		clear ();

		getmaxyx ( stdscr , row , col );

		if ( selected < 1 )
			selected = 1;

		if ( selected > 3 )
			selected = 3;

		attron ( A_BOLD );

		mvprintw ( row / 4 , ( col - STR_TITLE_GAME.length () + 1 ) / 2 , STR_TITLE_GAME.c_str () );

		mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , 5 * col / 20 , STR_ARROW_RIGHT.c_str () );
		mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , 15 * col / 20 , STR_ARROW_LEFT.c_str () );

		mvprintw ( 2 , 2 , STR_HELP.c_str () );

		attroff ( A_BOLD );

		mvprintw ( row / 2 , ( col - STR_PLAY.length () + 1 ) / 2 , STR_PLAY.c_str () );
		mvprintw ( ( row / 2 ) + 2 , ( col - STR_OPTIONS.length () + 1 ) / 2 , STR_OPTIONS.c_str () );
		mvprintw ( ( row / 2 ) + 4 , ( col - STR_EXIT.length () + 1 ) / 2 , STR_EXIT.c_str () );

		refresh();

		Key = getch ();

		if ( Key == KEY_DOWN )
			selected += 1;

		if ( Key == KEY_UP )
			selected -= 1;

		if ( Key == ENTER ) {

			if ( selected == 1 ) {

				play_menu ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal , defaultAI_prof );
			}

			if ( selected == 2 )
				options ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal , defaultAI_prof );

			if ( selected == 3 ) {
				if ( warnExit () ) {
					endwin ();
					return;
				}
			}
		}

		if ( Key == KEY_P ) {

			play_menu ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal , defaultAI_prof );
		}

		if ( Key == KEY_O )
			options ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal , defaultAI_prof );

		if ( Key == ESC || Key == KEY_E ) {
			if ( warnExit () ) {
				endwin ();
				return;
			}
		}

		if ( Key == KEY_F ( 1 ) )
			ui_help ();
	}
}
