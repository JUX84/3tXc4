#include <iostream>
#include "windows.h"
#include "grid.hpp"

void endLine () {
    std::cout << std::endl << std::endl;
}

void tab () {
    int i;
    for ( i = 0 ; i < 10 ; ++i )
        std::cout << " ";
}

bool warnExit () {
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
        tab ();
        tab ();
        std::cout << "ARE YOU SURE ?";
        endLine ();
        tab ();
        if ( selected == 1 )
            std::cout << "-> ";
        else
            std::cout << "   ";
        std::cout << "YES";
        if ( selected == 1 )
            std::cout << " <-";
        else
            std::cout << "   ";
        tab ();
        tab ();
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

        tab ();
        std::cout << "       ";
        std::cout << "Welcome!";
        endLine();

        tab();
        if ( selected == 1 )
            std::cout << "->      ";
        else
            std::cout << "        ";
        std::cout << "PLAY!";
        if ( selected == 1 )
            std::cout << "      <-";
        endLine();

        tab();
        if ( selected == 2 )
            std::cout << "->     ";
        else
            std::cout << "       ";
        std::cout << "OPTIONS";
        if ( selected == 2 )
            std::cout << "    <-";
        endLine();

        tab();
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

            if ( selected == 2 ) {
                options ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );
            }
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
