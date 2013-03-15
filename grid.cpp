#include <iostream>
#include "windows.h"
#include "grid.hpp"

grid::grid ( void ) {

    int i;
    int j;

    size = 5;

    XO = new int*[size];
    for ( i = 0 ; i < size ; ++i )
        XO[i] = new int[size];

    for ( i = 0 ; i < size ; ++i ) {

        for ( j = 0 ; j < size ; ++j )
            XO[i][j] = 0;
    }

    alignWinSize = 5;
    alignWinTotal = 1;
}

grid::grid ( int newsize , int newAlignWinSize , int newAligneWinTotal ) {

    int i;
    int j;

    size = newsize;

    XO = new int*[size];
    for ( i = 0 ; i < size ; ++i )
        XO[i] = new int[size];

    for ( i = 0 ; i < size ; ++i ) {

        for ( j = 0 ; j < size ; ++j )
            XO[i][j] = 0;
    }

    alignWinSize = newAlignWinSize;
    alignWinTotal = newAligneWinTotal;
}

void grid::insert ( int player , int pos ) {

	int i;

	while ( true ) {

        if ( pos < 0 )
        pos = 0;

        if ( pos > size - 1 )
            pos = size - 1;

        system("cls");

        endLine ( 2 );

        tab ( (130/size)+2 );

        for ( i = 0 ; i < pos ; ++i )
            std::cout << "    ";

        if ( player == 1 )
            std::cout << "X" << std::endl;
        if ( player == 2 )
            std::cout << "O" << std::endl;

        draw ();

        int Key = getKey();

        if ( Key == ARROW_LEFT )
            pos--;

        if ( Key == ARROW_RIGHT )
            pos++;

        if ( Key == KEY_ENTER ) {

            XO[0][pos] = player;
            break;
        }
	}
}

bool grid::checkLine ( int line ) {

    int j;

    for ( j = 0 ; j < size ; ++j ) {

        if ( XO[line][j] == 0 )
            return false;
    }

    return true;
}

bool grid::checkColumn ( int column ) {

    int i;

    for ( i = 0 ; i < size ; ++i ) {

        if ( XO[i][column] == 0 )
            return false;
    }

    return true;
}

int grid::checkWin ( void ) {

    /*int i;
    int j;
    int countLine;
    int countColumn;

    int countDiag1;
    int countDiag2;

    for ( i = 0 ; i < size ; ++i ) {
        if ( checkLine ( i ) ) {
            countLine = 0;
            for ( j = 0 ; j < size ; ++j ) {
                countLine += XO[i][j];
            }
            if ( countLine/5 == 1 || countLine/5 ==  2 )
                return countLine/5;
        }
    }
    for ( j = 0 ; j < size ; ++j ) {
        if ( checkColumn ( j ) ) {
            countColumn = 0;
            for ( i = 0 ; i < size ; ++i ) {
                countColumn += XO[i][j];
            }
            if ( countColumn/alignSizeWin == 1 || countColumn/5 == 2 )
                return countColumn/5;
        }
    }
    */

    return 0;
}

void grid::rotate ( bool clockwise ) {

    system("cls");

    int i;
    int j;

    int next_i;
    int next_j;

    int **TMP_XO;
    TMP_XO = new int*[size];
	for ( i = 0 ; i < size ; ++i ) {
		TMP_XO[i] = new int[size];
	}

    for ( i = 0 ; i < size ; ++i ) {

        for ( j = 0 ; j < size ; ++j ) {

            if ( clockwise ) {

                next_i=j;
                next_j=size-i-1;
            }
            else {

                next_i=size-j-1;
                next_j=i;
            }

            TMP_XO[next_i][next_j]=XO[i][j];
        }
    }
    for ( i = 0 ; i < size ; ++i ) {

        for ( j = 0 ; j < size ; ++j )
            XO[i][j]=TMP_XO[i][j];
    }

    draw ();

    for ( i = 0 ; i < size ; ++i )
        delete []TMP_XO[i];
    delete []TMP_XO;
}

void grid::gravitate ( void ) {

    int i;
    int j;

    bool modified(true);

    while(modified){

        modified=false;

        for ( i = 0 ; i < size-1 ; ++i ) {

            system("cls");

            endLine ( 3 );

            draw ();

            Sleep(100);

            for ( j = 0 ; j < size ; ++j ) {

                if ( XO[i+1][j] != 1 && XO[i+1][j] != 2 && XO[i][j] != 0 ) {

                    XO[i+1][j] = XO[i][j];
                    XO[i][j] = 0;

                    modified=true;
                }
            }
        }
    }
}

void grid::play ( int player ) {

    int selected ( 1 );
    int Key;

    while ( true ) {

        if ( selected < 1 )
            selected = 1;

        if ( selected > 2 )
            selected = 2;

        system("cls");

        endLine ( 3 );

        draw ();

        endLine ( 3 );

        tab ( 30 );

        std::cout << "PLAYER " << player << " !";

        endLine ( 2 );

        tab ( 15 );

        if ( selected == 1 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "Insert";

        tab ( 20 );

        if ( selected == 2 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "Rotate";

        endLine ( 1 );

        Key = getKey();

        if ( Key == ARROW_RIGHT )
            selected ++;

        if ( Key == ARROW_LEFT )
            selected --;

        if ( Key == KEY_ENTER ) {

            if ( selected == 1 )
                insert ( player , 0 );

            if ( selected == 2 ) {

                selected = 3;

                while ( true ) {

                    clear;

                    endLine ( 3 );

                    draw ();

                    endLine ( 3 );

                    if ( selected < 3 )
                        selected = 3;

                    if ( selected > 4 )
                        selected = 4;

                    tab ( 15 );

                    if ( selected == 3 )
                        std::cout << "-> ";
                    else
                        std::cout << "   ";

                    std::cout << "Clockwise";

                    tab ( 20 );

                    if ( selected == 4 )
                        std::cout << "-> ";
                    else
                        std::cout << "   ";

                    std::cout << "Counter-clockwise";

                    Key = getKey ();

                    if ( Key == ARROW_RIGHT )
                        selected ++;

                    if ( Key == ARROW_LEFT )
                        selected --;

                    if ( Key == KEY_ENTER ) {

                        if ( selected == 3 )
                            rotate ( true );

                        if ( selected == 4 )
                            rotate ( false );

                        break;
                    }

                    if ( Key == KEY_ESC )
                        break;
                }
            }

            if ( Key == KEY_ESC )
                continue;

            break;
        }

        if ( Key == KEY_ESC )
            break;
    }
}

void grid::draw ( void ) {

	int i;
	int j;

	endLine ( 2 );

	tab ( 130/size );

	std::cout << "|--";
	for ( i = 0 ; i < size-1 ; ++i ) {
		std::cout << "----";
	}
	std::cout << "-|" << std::endl;

	for( i = 0 ; i < size ; ++i ) {

        tab ( 130/size );

		std::cout << "|";
		for ( j = 0 ; j < size ; ++j ) {

			std::cout << " ";
			if ( XO[i][j]==1 ) std::cout << "X";
			else if ( XO[i][j]==2 ) std::cout << "O";
			else std::cout << " ";

			std::cout << " |";
		}

		endLine ( 1 );

		tab ( 130/size );

		std::cout << "|--";
		for ( j = 0 ; j < size-1 ; ++j ) {
			std::cout << "----";
		}
		std::cout << "-|" << std::endl;
	}
}
