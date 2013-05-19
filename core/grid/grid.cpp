#include <ncurses.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <climits>
#include "grid.hpp"
#include "../misc/misc.hpp"

bool grid::initXO = false;
std::string grid::ID = "";
bool grid::AI = false;

grid::grid ( void ) { // grid c-tor #1

	uint8_t i , j;

	height = 5;
	width = 5;

	AI_prof = 3;

	XO = new uint8_t*[height];
	for ( i = 0 ; i < height ; ++i )
		XO[i] = new uint8_t[width];

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j )
			XO[i][j] = 0;
	}

	alignWinSize = 5;
	alignWinTotal = 1;

	initXO = false;
	AI = false;
}

grid::grid ( uint8_t newHeight , uint8_t newWidth , uint8_t newAlignWinSize , uint8_t newAligneWinTotal , bool vsAI , uint8_t newAI_prof ) { // grid c-tor #2

	uint8_t i , j;

	height = newHeight;
	width = newWidth;

	XO = new uint8_t*[height];
	for ( i = 0 ; i < height ; ++i )
		XO[i] = new uint8_t[width];

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j )
			XO[i][j] = 0;
	}

	alignWinSize = newAlignWinSize;
	alignWinTotal = newAligneWinTotal;

	initXO = true;
	AI = vsAI;
	AI_prof = newAI_prof;

	time_t now = time ( 0 );
	tm *ltm = localtime ( &now );
	uint32_t year = ltm->tm_year + 1900;
	uint8_t month = ltm->tm_mon + 1;
	uint8_t day = ltm->tm_mday;
	uint8_t hour = ltm->tm_hour;
	uint8_t min = ltm->tm_min;
	uint8_t sec = ltm->tm_sec;

	std::string str_year ( std::to_string ( year ) );

	std::string str_month ( "" );
	if ( month < 10 ) {
		str_month += "0";
	}
	str_month += std::to_string ( month );

	std::string str_day ( "" );
	if ( day < 10 ) {
		str_day += "0";
	}
	str_day += std::to_string ( day );

	std::string str_hour ( "" );
	if ( hour < 10 ) {
		str_hour += "0";
	}
	str_hour += std::to_string ( hour );

	std::string str_min ( "" );
	if ( min < 10 ) {
		str_min += "0";
	}
	str_min += std::to_string ( min );

	std::string str_sec ( "" );
	if ( sec < 10 ) {
		str_sec += "0";
	}
	str_sec += std::to_string ( sec );

	std::string date = str_year + str_month + str_day + str_hour + str_min + str_sec;

	ID = date;
}

grid::grid ( std::string gameID ) { // grid c-tor #3

	std::ifstream input ( STR_SAVE_REP + "/" + STR_SAVE_PRE + gameID + "." + STR_SAVE_EXT );
	if ( !input ) {

		uint8_t row , col;

		getmaxyx ( stdscr , row , col );

		clear ();
		mvprintw ( row / 2 , ( col - STR_FAIL_LOAD.length() + 1 ) / 2 , STR_FAIL_LOAD.c_str() );
		refresh ();
		wait ( 2000 );

		initXO = false;
	}
	else {

		uint8_t i , j;
		uint8_t buff;

		ID = gameID;

		std::string s;

		input >> AI;
		input >> AI_prof;
		input >> height >> width;
		input >> alignWinSize >> alignWinTotal;

		XO = new uint8_t*[height];
		for ( i = 0 ; i < height ; ++i )
			XO[i] = new uint8_t[width];

		for ( i = 0 ; i < height ; ++i ) {

			for ( j = 0 ; j < width ; ++j ) {

				input >> buff;

				switch ( buff ) {

					case 1:
						XO[i][j] = 1;
						break;

					case 2:
						XO[i][j] = 2;
						break;

					default:
						XO[i][j] = 0;
						break;
				}
			}
		}

		input.close ();

		initXO = true;
	}
}

grid::grid ( grid *G ) { // grid c-tor #4

	uint8_t i;
	uint8_t j;

	width = G->getWidth ();
	height = G->getHeight ();
	alignWinSize = G->getAlignWinSize ();
	alignWinTotal = G->getAlignWinTotal ();
	AI_prof = G->getAI_prof ();

	XO = new uint8_t*[height];
	for ( i = 0 ; i < height ; ++i )
		XO[i] = new uint8_t[width];

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j )
			XO[i][j] = G->getXO ( i , j );
	}
}

grid::~grid ( void ) { // grid d-tor

	uint8_t i;

	for ( i = 0 ; i < height ; ++i )
		delete []XO[i];
	delete []XO;

	initXO = false;
	AI = false;
}

void grid::destroy ( void ) { // XO grid d-tor

	uint8_t i;

	for ( i = 0 ; i < height ; ++i )
		delete []XO[i];
	delete []XO;
}

uint8_t grid::getWidth ( void ) {

	return width;
}

uint8_t grid::getHeight ( void ) {

	return height;
}

uint8_t grid::getAlignWinSize ( void ) {

	return alignWinSize;
}

uint8_t grid::getAlignWinTotal ( void ) {

	return alignWinTotal;
}

uint8_t grid::getAI_prof ( void ) {

	return AI_prof;
}

uint8_t grid::getXO ( uint8_t i , uint8_t j ) {

	return XO[i][j];
}

void grid::save ( void ) { // grid save

	std::ofstream check ( STR_SAVE_REP + "/" + STR_SAVE_IND + "." + STR_SAVE_EXT , std::ios::app );

	if ( !check ) {

		std::string command = "mkdir -p " + STR_SAVE_REP;
		system(command.c_str());
	}

	if ( check )
		check.close ();

	std::ifstream indexread ( STR_SAVE_REP + "/" + STR_SAVE_IND + "." + STR_SAVE_EXT );

	if ( indexread ) {

		std::list<std::string> listID;
		std::list<std::string>::iterator it;
		std::string buff;

		while ( !indexread.eof() ) {

			indexread >> buff;
			if ( std::find ( listID.begin () , listID.end () , buff ) == listID.end () )
				listID.push_back(buff);
		}

		if ( std::find ( listID.begin () , listID.end () , ID ) == listID.end () )
			listID.push_back(ID);

		indexread.close ();

		std::ofstream indexwrite ( STR_SAVE_REP + "/" + STR_SAVE_IND + "." + STR_SAVE_EXT );

		for ( it = listID.begin() ; it != listID.end () ; ++it )
			indexwrite << (*it) << std::endl;

		indexwrite.close();
	}
	else {

		std::ofstream index ( STR_SAVE_REP + "/" + STR_SAVE_IND + "." + STR_SAVE_EXT );

		index << ID << std::endl;

		index.close ();
	}

	std::ofstream save ( STR_SAVE_REP + "/" + STR_SAVE_PRE + ID + "." + STR_SAVE_EXT );

	save << AI << std::endl;
	save << AI_prof << std::endl;
	save << height << " " << width << std::endl;
	save << alignWinSize << " " << alignWinTotal << std::endl;

	uint8_t i , j;

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			save << XO[i][j] << " ";
		}

		save << std::endl;
	}

	save.close ();

	return;
}

void grid::insert ( bool player , int8_t pos ) { // grid insert X or O

	uint8_t i;
	uint8_t row , col;
	uint32_t Key;

	while ( true ) {

		getmaxyx ( stdscr , row , col );

		if ( pos < 0 )
			pos = width - 1;

		if ( pos > width - 1 )
			pos = 0;

		clear ();

		draw ();

		mvprintw ( ( row / 2 ) - ( height*2 / 2 ) - 1 , ( col / 2 ) - ( width*4 / 2 ) , "  " );

		for ( i = 0 ; i < pos ; ++i )
			printw ( "    " );

		if ( player )
			printw ( "X" );
		else
			printw ( "O" );

		refresh ();

		Key = getch ();

		switch ( Key ) {

			case KEY_LEFT:
				pos--;
				break;

			case KEY_RIGHT:
				pos++;
				break;

			default:
				break;
		}

		if ( Key == ENTER ) {

			if ( XO[0][pos] == 0 ) {

				if ( player )
					XO[0][pos] = 1;
				else
					XO[0][pos] = 2;

				break;
			}
		}
	}
}

uint8_t grid::checkWin ( void ) { // grid win check

	int8_t h , i , j , k , l;
	uint8_t countX , countO;

	uint8_t alignX ( 0 );
	uint8_t alignO ( 0 );

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j <= ( width - alignWinSize ) ; ++j ) {

			countX = 0;
			countO = 0;

			if ( j > width - alignWinSize )
                break;

			for ( k = j ; k < j + alignWinSize ; ++k ) {

				if ( XO[i][k] == 1 )
					countX++;

				if ( XO[i][k] == 2 )
					countO++;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				j += alignWinSize - 1;
			}
		}
	}

	for ( i = 0 ; i <= ( height - alignWinSize ) ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			countX = 0;
			countO = 0;

			if ( i > height - alignWinSize )
                break;

			for ( k = i ; k < i + alignWinSize ; ++k ) {

				if ( XO[k][j] == 1 )
					countX++;

				if ( XO[k][j] == 2 )
					countO++;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i += alignWinSize - 1;
			}
		}
	}

	for ( h = height - alignWinSize ; h >= 0 ; --h ) {

		i = h;
		j = 0;

		while ( ( i <= ( height - alignWinSize ) ) && ( j <= (width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k < i + alignWinSize && l < j + alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				++k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			++i;
			++j;
		}
	}

	for ( h = 1 ; h <= width - alignWinSize ; ++h ) {

		i = 0;
		j = h;

		while ( ( i <= ( height - alignWinSize ) ) && ( j <= ( width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k < i + alignWinSize && l < j + alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				++k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
			}

			++i;
			++j;
		}
	}

	for ( h = width - alignWinSize ; h >= 0 ; --h ) {

		i = height - 1;
		j = h;

		while ( ( i >= ( alignWinSize - 1 ) ) && ( j <= ( width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k >= 0 && l < j + alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				--k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			--i;
			++j;
		}
	}

	for ( h = height - 2 ; h >= alignWinSize - 1 ; --h ) {

		i = h;
		j = 0;

		while ( ( i >= ( alignWinSize - 1 ) ) && ( j <= ( width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k >= 0 && l < j +alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				--k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			--i;
			++j;
		}
	}

	if ( alignX >= alignWinTotal )
		alignX = 1;
	else
		alignX = 0;

	if ( alignO >= alignWinTotal )
		alignO = 2;
	else
		alignO = 0;

	return alignX+alignO;
}

void grid::rotate ( bool silent , bool clockwise ) { // grid rotation

	clear ();

	uint8_t i , j;
	uint8_t next_i , next_j;

	uint8_t **TMP_XO;

	TMP_XO = new uint8_t*[width];
	for ( i = 0 ; i < width ; ++i )
		TMP_XO[i] = new uint8_t[height];

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			if ( clockwise ) {

				next_i = j;
				next_j = height - i - 1;
			}
			else {

				next_i = width - j - 1;
				next_j = i;
			}

			TMP_XO[next_i][next_j] = XO[i][j];
		}
	}

	uint8_t tmp = width;
	width = height;
	height = tmp;

	XO = new uint8_t*[height];
	for ( i = 0 ; i < height ; ++i )
		XO[i] = new uint8_t[width];

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j )
			XO[i][j]=TMP_XO[i][j];
	}

	if ( !silent )
		draw ();

	for ( i = 0 ; i < height ; ++i )
		delete []TMP_XO[i];
	delete []TMP_XO;
}

void grid::gravitate ( bool silent ) { // grid gravitation

	uint8_t i , j;

	bool modified ( true );

	while ( modified ){

		modified = false;

		for ( i = 0 ; i < height-1 ; ++i ) {

			for ( j = 0 ; j < width ; ++j ) {

				if ( XO[i+1][j] != 1 && XO[i+1][j] != 2 && XO[i][j] != 0 ) {

					XO[i+1][j] = XO[i][j];
					XO[i][j] = 0;

					modified = true;
				}
			}

			if ( modified && !silent ) {

				clear ();
				draw ();
				wait ( 100 );
			}
		}
	}

	if ( !silent ) {

		clear ();
		draw ();
		wait ( 500 );
	}
}

void grid::play ( bool player ) { // grid play (insert or rotate)

	uint8_t selected ( 1 );
	std::string STR_SELECTED;
	uint8_t TAB;
	uint8_t row , col;
	uint32_t Key;

	while ( true ) {

		getmaxyx ( stdscr , row , col );

		if ( selected < 1 )
			selected = 1;

		if ( selected > 2 )
			selected = 2;

		if ( selected == 1 ) {
			STR_SELECTED = STR_INSERT;
			TAB = 1;
		}

		if ( selected == 2 ) {
			STR_SELECTED = STR_ROTATE;
			TAB = 2;
		}

		clear ();

		draw ();

		attron ( A_BOLD );

		mvprintw ( 3 , ( col / 2 ) - ( STR_P1.length () / 2 ) + 1 , STR_P1.c_str () );

		mvprintw ( row - 4 , ( TAB * col / 3 ) - STR_SELECTED.length () - 2 , STR_ARROW_RIGHT.c_str () );
		mvprintw ( row - 4 , ( TAB * col / 3 ) + STR_SELECTED.length () , STR_ARROW_LEFT.c_str () );

		attroff ( A_BOLD );

		mvprintw ( row - 4 , ( col / 3 ) - ( STR_INSERT.length () / 2 ) , STR_INSERT.c_str () );
		mvprintw ( row - 4 , ( 2 * col / 3 ) - ( STR_ROTATE.length () / 2 ) , STR_ROTATE.c_str () );

		refresh ();

		Key = getch ();

		if ( Key == KEY_RIGHT )
			selected ++;

		if ( Key == KEY_LEFT )
			selected --;

		if ( Key == ENTER ) {

			if ( selected == 1 )
				insert ( player , 0 );

			if ( selected == 2 ) {

				selected = 3;

				while ( true ) {

					clear ();

					draw ();

					if ( selected < 3 )
						selected = 3;

					if ( selected > 4 )
						selected = 4;

					if ( selected == 3 ) {
						STR_SELECTED = STR_CLOCKWISE;
						TAB = 1;
					}

					if ( selected == 4 ) {
						STR_SELECTED = STR_CCLOCKWISE;
						TAB = 2;
					}

					attron ( A_BOLD );

					mvprintw ( row - 4 , ( TAB * col / 3 ) - STR_SELECTED.length () - 2 , STR_ARROW_RIGHT.c_str () );
					mvprintw ( row - 4 , ( TAB * col / 3 ) + STR_SELECTED.length () , STR_ARROW_LEFT.c_str () );

					attroff ( A_BOLD );

					mvprintw ( row - 4 , ( col / 3 ) - ( STR_CLOCKWISE.length () / 2 ) , STR_CLOCKWISE.c_str () );
					mvprintw ( row - 4 , ( 2 * col / 3 ) - ( STR_CCLOCKWISE.length () / 2 ) , STR_CCLOCKWISE.c_str () );

					refresh ();

					Key = getch  ();

					if ( Key == KEY_RIGHT )
						selected ++;

					if ( Key == KEY_LEFT )
						selected --;

					if ( Key == ENTER ) {

						if ( selected == 3 )
							rotate ( false , true );

						if ( selected == 4 )
							rotate ( false , false );

						break;
					}
				}
			}
			break;
		}

		if ( Key == ESC )
			break;
	}
}

int8_t grid::AI_value ( void ) { // grid value (minimax)

	int8_t h , i , j , k , l;
	uint8_t countX , countO;

	int8_t alignX ( 0 );
	int8_t alignO ( 0 );

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j <= ( width - alignWinSize ) ; ++j ) {

			countX = 0;
			countO = 0;

			if ( j > width - alignWinSize )
                break;

			for ( k = j ; k < j + alignWinSize ; ++k ) {

				if ( XO[i][k] == 1 )
					countX++;

				if ( XO[i][k] == 2 )
					countO++;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				j += alignWinSize - 1;
			}
		}
	}

	for ( i = 0 ; i <= ( height - alignWinSize ) ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			countX = 0;
			countO = 0;

			if ( i > height - alignWinSize )
                break;

			for ( k = i ; k < i + alignWinSize ; ++k ) {

				if ( XO[k][j] == 1 )
					countX++;

				if ( XO[k][j] == 2 )
					countO++;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i += alignWinSize - 1;
			}
		}
	}

	for ( h = height - alignWinSize ; h >= 0 ; --h ) {

		i = h;
		j = 0;

		while ( ( i <= ( height - alignWinSize ) ) && ( j <= (width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k < i + alignWinSize && l < j + alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				++k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			++i;
			++j;
		}
	}

	for ( h = 1 ; h <= width - alignWinSize ; ++h ) {

		i = 0;
		j = h;

		while ( ( i <= ( height - alignWinSize ) ) && ( j <= ( width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k < i + alignWinSize && l < j + alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				++k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i += alignWinSize - 1;
				j += alignWinSize - 1;
			}

			++i;
			++j;
		}
	}

	for ( h = width - alignWinSize ; h >= 0 ; --h ) {

		i = height - 1;
		j = h;

		while ( ( i >= ( alignWinSize - 1 ) ) && ( j <= ( width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k >= 0 && l < j + alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				--k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			--i;
			++j;
		}
	}

	for ( h = height - 2 ; h >= alignWinSize - 1 ; --h ) {

		i = h;
		j = 0;

		while ( ( i >= ( alignWinSize - 1 ) ) && ( j <= ( width - alignWinSize ) ) ) {

			countX = 0;
			countO = 0;

			k = i;
			l = j;

			while ( k >= 0 && l < j +alignWinSize ) {

				if ( XO[k][l] == 1 )
					countX++;

				if ( XO[k][l] == 2 )
					countO++;

				--k;
				++l;
			}

			if ( countX >= alignWinSize ) {

				alignX++;
				countX = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			if ( countO >= alignWinSize ) {

				alignO++;
				countO = 0;
				i -= alignWinSize - 1;
				j += alignWinSize - 1;
			}

			--i;
			++j;
		}
	}

	if ( alignX >= alignWinTotal )
		alignX = INT8_MAX;

	if ( alignO >= alignWinTotal )
		alignO = INT8_MAX;

	return alignO-alignX;
}

bool grid::full ( void ) { // checks if the grid is full

	int i , j;

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			if ( XO[i][j] == 0 )
				return false;
		}
	}

	return true;
}

int8_t grid::max ( uint8_t prof , int8_t alpha , int8_t beta ) { // maximizing function (minimax)

	uint8_t i , j;
	int8_t tmp;

	uint8_t c = checkWin();

	if ( prof == 0 || full() || c != 0 )
		return AI_value();

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			if ( XO[i][j] == 0 ) {

				if ( ( i < height - 1 ) && ( XO[i + 1][j] == 0 ) )
					continue;

				XO[i][j] = 2;

				tmp = min ( prof - 1 , alpha , beta );

				XO[i][j] = 0;

				if ( alpha < tmp )
					alpha = tmp;

                if ( beta <= alpha )
                    return alpha;
			}
		}
	}

	grid *tmpG = new grid ( this );

	tmpG->rotate ( true , true );
	tmpG->gravitate ( true );

	tmp = tmpG->min ( prof - 1 , alpha , beta );

	tmpG->destroy ();

	if ( alpha < tmp )
		alpha = tmp;

    if ( beta <= alpha )
        return alpha;

	tmpG = new grid ( this );

	tmpG->rotate ( true , false );
	tmpG->gravitate ( true );

	tmp = tmpG->min ( prof - 1 , alpha , beta );

	tmpG->destroy ();

	if ( alpha < tmp )
		alpha = tmp;

	return alpha;
}

int8_t grid::min ( uint8_t prof , int8_t alpha , int8_t beta ) { // minimizing function (minimax)

	uint8_t i , j;
	int8_t tmp;

	uint8_t c = checkWin();

	if ( prof == 0 || full() || c != 0 )
		return AI_value();

	for ( i = 0 ; i < height ; ++i ) {

		for ( j = 0 ; j < width ; ++j ) {

			if ( XO[i][j] == 0 ) {

				if ( ( i < height - 1 ) && ( XO[i + 1][j] == 0 ) )
					continue;

				XO[i][j] = 1;

				tmp = max ( prof - 1 , alpha , beta );

				if ( beta > tmp )
					beta = tmp;

				XO[i][j] = 0;

				if ( beta <= alpha )
                    return beta;
			}
		}
	}

	grid *tmpG = new grid ( this );

	tmpG->rotate ( true , true );
	tmpG->gravitate ( true );

	tmp = tmpG->max ( prof - 1 , alpha , beta );

	if ( beta > tmp )
		beta = tmp;

 	if ( beta <= alpha )
        return beta;

	tmpG->destroy ();

	tmpG = new grid ( this );

	tmpG->rotate ( true , false );
	tmpG->gravitate ( true );

	tmp = tmpG->max ( prof - 1 , alpha , beta );

	if ( beta > tmp )
		beta = tmp;

	tmpG->destroy ();

	return beta;
}

uint8_t grid::minimax ( uint8_t prof ) { // minimax function (with alpha-beta pruning)

	uint8_t i , j;
	int8_t tmp;
	int8_t alpha ( INT8_MIN );
	int8_t beta ( INT8_MAX );
	int8_t nextj = -1;

	if ( ( prof != 0 ) || ( !full() ) ) {

		for ( i = 0 ; i < height ; ++i ) {

			for ( j = 0 ; j < width ; ++j ) {

				if ( XO[i][j] == 0 ) {

					if ( ( i < height - 1 ) && ( XO[i + 1][j] == 0 ) )
						continue;

					XO[i][j] = 2;

					tmp = min ( prof - 1 , alpha , beta );

					if ( alpha < tmp ) {

						alpha = tmp;
						nextj = j;
					}

					XO[i][j] = 0;
				}
			}
		}

		grid *tmpG = new grid ( this );

		tmpG->rotate ( true , true );
		tmpG->gravitate ( true );

		tmp = tmpG->min ( prof - 1 , alpha , beta );

		if ( alpha < tmp ) {

			alpha = tmp;
			nextj = width;
		}

		tmpG->destroy ();

		tmpG = new grid ( this );

		tmpG->rotate ( true , false );
		tmpG->gravitate ( true );

		tmp = tmpG->min ( prof - 1 , alpha , beta );

		if ( alpha < tmp ) {

			alpha = tmp;
			nextj = width + 1;
		}

		tmpG->destroy ();
	}

	return nextj;
}

void grid::AI_play ( void ) { // AI play function (calls minimax function)

	uint8_t row , col;

	getmaxyx ( stdscr , row , col );

	mvprintw ( row / 2 + 1 , ( ( col - STR_THINKING.length() ) / 2 ) + 1 , STR_THINKING.c_str() );

	refresh ();

	uint8_t nextj = minimax ( AI_prof ); // calls minimax function

	if ( nextj == width ) { // in case of clockwise rotation

		rotate ( false , true );
		gravitate ( false );
	}
	else if ( nextj == width + 1 ) { // counter-clockwise rotation

		rotate ( false , false );
		gravitate ( false );
	}
	else
		XO[0][nextj] = 2; // insertion
}

void grid::draw ( void ) { // draws the grid

	uint8_t i , j;
	uint8_t row , col;

	getmaxyx ( stdscr , row , col );

	mvprintw ( ( row / 2 ) - ( height*2 / 2 ) , ( col / 2 ) - ( width*4 / 2 ) , "|--" );
	for ( i = 0 ; i < width-1 ; ++i ) {
		printw ( "----" );
	}
	printw ( "-|" );

	for( i = 0 ; i < height ; ++i ) {

		mvprintw ( ( row / 2 ) - ( height*2 / 2 ) + ( i * 2 ) + 1 , ( col / 2 ) - ( width*4 / 2 ) , "|" );

		for ( j = 0 ; j < width ; ++j ) {

			printw ( " " );
			if ( XO[i][j]==1 ) printw ( "X" );
			else if ( XO[i][j]==2 ) printw ( "O" );
			else printw ( " " );

			printw ( " |" );
		}

		mvprintw ( ( row / 2 ) - ( height*2 / 2 ) + ( i * 2 ) + 2 , ( col / 2 ) - ( width*4 / 2 ) , "|--" );
		for ( j = 0 ; j < width-1 ; ++j ) {
			printw ( "----" );
		}
		printw ( "-|" );
	}

	refresh ();
}
