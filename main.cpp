#include <iostream>
#include "windows.h"
#include "grid.hpp"

void endLine ( void ) {
    std::cout << std::endl << std::endl;
}

void tab ( int space ) {
    int i;
    for ( i = 0 ; i < space ; ++i )
        std::cout << " ";
}

bool warnExit ( void ) {
    int selected (1);
    int Key;
    while ( true ) {
        if ( selected < 1 )
            selected = 1;
        if ( selected > 2 )
            selected = 2;
        system ("cls");
        endLine ();
        endLine ();
        tab ( 25 );
        std::cout << "ARE YOU SURE ?";
        endLine ();
        endLine ();

        tab ( 12 );
        if ( selected == 1 )
            std::cout << "-> ";
        else
            std::cout << "   ";
        std::cout << "YES";
        if ( selected == 1 )
            std::cout << " <-";
        else
            std::cout << "   ";
        tab ( 22 );
        if ( selected == 2 )
            std::cout << "-> ";
        else
            std::cout << "   ";
        std::cout << "NO";
        if ( selected == 2 )
            std::cout << " <-";
        else
            std::cout << "   ";
        Key = getKey ();
        if ( Key == ARROW_LEFT )
            selected -= 1;
        if ( Key == ARROW_RIGHT )
            selected += 1;
        if ( Key == KEY_ENTER ) {
            if ( selected == 1 )
                return true;
            if ( selected == 2 )
                return false;
        }
    }
}

void options ( int &defaultSize , int &defaultAlignWinSize , int &defaultAlignWinTotal ) {

    int selected (1);
    int i;
    while ( true ) {
        if ( selected < 1 )
            selected = 1;
        if ( selected > 3 )
            selected = 3;
        if ( defaultSize < 3 )
            defaultSize = 3;
        if ( defaultSize > 20 )
            defaultSize = 20;
        if ( defaultAlignWinSize > defaultSize ) {
            defaultAlignWinSize = defaultSize;
        }
        if ( defaultAlignWinSize < 3 ) {
            defaultAlignWinSize = 3;
        }
        if ( defaultAlignWinTotal < 1 ) {
            defaultAlignWinTotal = 1;
        }
        if ( defaultAlignWinTotal > 4 ) {
            defaultAlignWinTotal = 4;
        }

        system("cls");
        endLine ();
        tab (27);
        std::cout << "OPTIONS";
        endLine ();

        endLine ();
        tab (15);
        if ( selected == 1 )
            std::cout << "-> ";
        else
            std::cout << "   ";
        std::cout << "Size";
        tab (7);
        std::cout << defaultSize;
        if ( defaultSize < 10 )
            std::cout << " ";
        tab (2);
        std::cout << "[";
        for ( i = 0 ; i < defaultSize ; ++i ) {
            std::cout << "-";
        }
        for ( i = 20 ; i > defaultSize ; --i ) {
            std::cout << " ";
        }
        std::cout << "]";
        if ( selected == 1 )
            std::cout << " <-";
        else
            std::cout << "   ";

        endLine ();
        tab (10);
        if ( selected == 2 )
            std::cout << "-> ";
        else
            std::cout << "   ";
        std::cout << "Alignment Size";
        tab (2);
        std::cout << defaultAlignWinSize;
        if ( defaultAlignWinSize < 10 )
            std::cout << " ";
        tab (2);
        std::cout << "[";
        for ( i = 0 ; i < defaultAlignWinSize ; ++i ) {
            std::cout << "-";
        }
        for ( i = 20 ; i > defaultAlignWinSize ; --i ) {
            std::cout << " ";
        }
        std::cout << "]";
        if ( selected == 2 )
            std::cout << " <-";
        else
            std::cout << "   ";

        endLine ();
        tab (9);
        if ( selected == 3 )
            std::cout << "-> ";
        else
            std::cout << "   ";
        std::cout << "Alignment Total";
        tab (2);
        std::cout << defaultAlignWinTotal;
        if ( defaultAlignWinTotal < 10 )
            std::cout << " ";
        tab (2);
        std::cout << "[";
        for ( i = 0 ; i < defaultAlignWinTotal ; ++i ) {
            std::cout << "-----";
        }
        for ( i = 4 ; i > defaultAlignWinTotal ; --i ) {
            std::cout << "     ";
        }
        std::cout << "]";
        if ( selected == 3 )
            std::cout << " <-";
        else
            std::cout << "   ";

        int Key = getKey ();
        if ( Key == KEY_ESC )
            break;
        if ( Key == ARROW_LEFT ) {
            if ( selected == 1 )
                defaultSize--;
            if ( selected == 2 )
                defaultAlignWinSize--;
            if ( selected == 3 )
                defaultAlignWinTotal--;
        }
        if ( Key == ARROW_RIGHT ) {
            if ( selected == 1 )
                defaultSize++;
            if ( selected == 2 )
                defaultAlignWinSize++;
            if ( selected == 3 )
                defaultAlignWinTotal++;
        }
        if ( Key == ARROW_DOWN )
            selected++;
        if ( Key == ARROW_UP )
            selected--;
    }
}

int main ( int argc , char *arvg[] ) {
    int selected (1);
    int defaultSize (5);
    int defaultAlignWinSize (5);
    int defaultAlignWinTotal (1);
    int Key;

    while ( true ) {
        system ("cls");

        if ( selected < 1 )
            selected = 1;
        if ( selected > 3 )
            selected = 3;

        endLine ();

        tab ( 27 );
        std::cout << "Welcome!";
        endLine();

        tab( 20 );
        if ( selected == 1 )
            std::cout << "->      ";
        else
            std::cout << "        ";
        std::cout << "PLAY!";
        if ( selected == 1 )
            std::cout << "      <-";
        endLine();

        tab( 20 );
        if ( selected == 2 )
            std::cout << "->     ";
        else
            std::cout << "       ";
        std::cout << "OPTIONS";
        if ( selected == 2 )
            std::cout << "    <-";
        endLine();

        tab( 20 );
        if ( selected == 3 )
            std::cout << "->      ";
        else
            std::cout << "        ";
        std::cout << "EXIT";
        if ( selected == 3 )
            std::cout << "      <-";
        endLine ();

        Key=getKey();

        if ( Key == ARROW_DOWN )
            selected += 1;

        if ( Key == ARROW_UP )
            selected -= 1;

        if ( Key == KEY_ENTER ) {

            if ( selected == 3 ) {
                if ( warnExit () )
                    return 0;
            }

            if ( selected == 2 )
                options ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );
        }

        if ( Key == KEY_ESC ) {
            if ( warnExit () )
                return 0;
        }
    }

    /*
    grid G ( 5 , 5 , 1 );
    G.draw();
    */
	/*
	int size;
	int **XO;
	std::cout << "size? "; std::cin >> size;
	int i;
	XO = new int*[size];
	for ( i = 0 ; i < size ; ++i ) {
		XO[i] = new int[size];
	}
	int j;
	for ( i = 0 ; i < size ; ++i ) {
        for ( j = 0 ; j < size ; ++j )
            XO[i][j]=0;
	}
	while ( true ) {
        std::cout << std::endl << "PLAYER 1!" << std::endl << std::endl;
		play ( XO , 1 , size );
		gravitate ( XO , size );
		system("cls");
		draw ( XO , size );
		std::cout << std::endl << "PLAYER 2!" << std::endl << std::endl;
		play ( XO , 2 , size );
		gravitate ( XO , size );
		system("cls");
		draw ( XO , size );
	}
	return 0;
	*/
}
