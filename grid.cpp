#include <iostream>
#include "windows.h"
#include "grid.hpp"

grid::grid () {
    size = 5;
    XO = new int*[size];
    int i;
    for ( i = 0 ; i < size ; ++i )
        XO[i] = new int[size];
    int j;
    for ( i = 0 ; i < size ; ++i ) {
        for ( j = 0 ; j < size ; ++j )
            XO[i][j] = 0;
    }
    alignWinSize = 5;
    alignWinTotal = 1;
}

grid::grid ( int newsize , int newAlignWinSize , int newAligneWinTotal ) {
    size = newsize;
    XO = new int*[size];
    int i;
    for ( i = 0 ; i < size ; ++i )
        XO[i] = new int[size];
    int j;
    for ( i = 0 ; i < size ; ++i ) {
        for ( j = 0 ; j < size ; ++j )
            XO[i][j] = 0;
    }
    alignWinSize = newAlignWinSize;
    alignWinTotal = newAligneWinTotal;
}

void grid::insert ( int player , int pos ) {
	int i;
	if ( pos < 0 ) pos = 0;
	if ( pos > 4 ) pos = 4;
	system("cls");
	std::cout << std::endl;
	std::cout << "      ";
	for ( i = 0 ; i < pos ; ++i )
        std::cout << "    ";
    if ( player == 1 ) std::cout << "X" << std::endl;
    if ( player == 2 ) std::cout << "O" << std::endl;
	draw ();
	while ( true ) {
        int Key=getKey();
        if ( Key == ARROW_LEFT ) {
            insert ( player , pos-1 );
            break;
        }
        if ( Key == ARROW_RIGHT ) {
            insert ( player , pos+1 );
            break;
        }
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

bool grid::checkWin ( int player ) {
    int i;
    int j;
    int countLine;
    int countColumn;

    /**** TO-DO ****

    int countDiag1;
    int countDiag2;

    ***************/

    for ( i = 0 ; i < size ; ++i ) {
        if ( checkLine ( i ) ) {
            countLine = 0;
            for ( j = 0 ; j < size ; ++j ) {
                countLine += XO[i][j];
            }
            if ( countLine == 5*player )
                return true;
        }
    }
    for ( j = 0 ; j < size ; ++j ) {
        if ( checkColumn ( j ) ) {
            countColumn = 0;
            for ( i = 0 ; i < size ; ++i ) {
                countColumn += XO[i][j];
            }
            if ( countColumn == 5*player )
                return true;
        }
    }
    return false;
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
            TMP_XO[next_i][next_j]=XO[i][j]; // 90 degrees clockwise
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

void grid::gravitate () {
    int i;
    int j;
    bool modified(true);
    while(modified){
        modified=false;
        for ( i = 0 ; i < size-1 ; ++i ) {
            system("cls");
            std::cout << std::endl << std::endl;
            draw (); // draws each step of the fall
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
    int choice;
    system("cls");
    std::cout << std::endl << std::endl;
    draw ();
    std::cout << std::endl;
    std::cout << "PLAYER " << player << " !" << std::endl << std::endl;
    std::cout << "(1) insert" << std::endl << "(2) rotate" << std::endl; std::cin >> choice;
    if ( choice == 1 )
        insert ( player , 0 );
    else if ( choice == 2 ) {
        while ( true ) {
            std::cout << "(1) clockwise" << std::endl << "(2) counter-clockwise" << std::endl; std::cin >> choice;
            if ( choice == 1 ) {
                rotate ( true );
                break;
            }
            else if ( choice == 2 ) {
                rotate ( false );
                break;
            }
            std::cout << "Please, type 1 or 2, then press ENTER..." << std::endl;
        }
    }
    else {
        std::cout << "Please, type 1 or 2, then press ENTER..." << std::endl;
        play ( player );
    }
}

void grid::draw () {
	int i;
	int j;
	std::cout << "    |--";
	for ( i = 0 ; i < size-1 ; ++i ) {
		std::cout << "----";
	}
	std::cout << "-|" << std::endl;
	for( i = 0 ; i < size ; ++i ) {

		std::cout << "    |";
		for ( j = 0 ; j < size ; ++j ) {
			std::cout << " ";

			if ( XO[i][j]==1 ) std::cout << "X";
			else if ( XO[i][j]==2 ) std::cout << "O";
			else std::cout << " ";

			std::cout << " |";
		}
		std::cout << std::endl;
		std::cout << "    |--";
		for ( j = 0 ; j < size-1 ; ++j ) {
			std::cout << "----";
		}
		std::cout << "-|" << std::endl;
	}
}
