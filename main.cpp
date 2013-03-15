#include <iostream>
#include "windows.h"
#include "grid.hpp"

bool warnExit ( void ) {

    int selected (1);
    int Key;

    while ( true ) {

        if ( selected < 1 )
            selected = 1;

        if ( selected > 2 )
            selected = 2;

        system ("cls");

        endLine ( 6 );

        tab ( 32 );

        std::cout << "ARE YOU SURE ?";

        endLine ( 4 );

        tab ( 15 );

        if ( selected == 1 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "YES";

        if ( selected == 1 )
            std::cout << " <-";
        else
            std::cout << "   ";

        tab ( 30 );

        if ( selected == 2 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "NO";

        if ( selected == 2 )
            std::cout << " <-";
        else
            std::cout << "   ";

        endLine ( 1 );

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

        if ( defaultAlignWinSize > defaultSize )
            defaultAlignWinSize = defaultSize;

        if ( defaultAlignWinSize < 3 )
            defaultAlignWinSize = 3;

        if ( defaultAlignWinTotal < 1 )
            defaultAlignWinTotal = 1;

        if ( defaultAlignWinTotal > 4 )
            defaultAlignWinTotal = 4;

        clear;

        endLine ( 2 );

        tab (27);

        std::cout << "OPTIONS";

        endLine ( 4 );

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

        endLine ( 2 );

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

        endLine ( 2 );

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

        for ( i = 0 ; i < defaultAlignWinTotal ; ++i )
            std::cout << "-----";

        for ( i = 4 ; i > defaultAlignWinTotal ; --i )
            std::cout << "     ";

        std::cout << "]";

        if ( selected == 3 )
            std::cout << " <-";
        else
            std::cout << "   ";

        std::cout << std::endl;

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

void play ( int size , int alignWinSize , int alignWinTotal ) {

    grid G ( size , alignWinSize , alignWinTotal );

    while ( true ) {

        G.play ( 1 );
        G.gravitate ();

        if ( G.checkWin () == 1 ) {

        }

        if ( G.checkWin () == 2 ) {

        }

        G.play ( 2 );
        G.gravitate ();

        if ( G.checkWin () == 1 ) {

        }

        if ( G.checkWin () == 2 ) {

        }
    }
}

int main ( int argc , char *arvg[] ) {

    int selected (1);
    int defaultSize (5);
    int defaultAlignWinSize (5);
    int defaultAlignWinTotal (1);
    int Key;

    while ( true ) {
        clear;

        if ( selected < 1 )
            selected = 1;
        if ( selected > 3 )
            selected = 3;

        endLine ( 6 );

        tab ( 34 );
        std::cout << "Welcome!";
        endLine( 2 );

        tab( 27 );
        if ( selected == 1 )
            std::cout << "->      ";
        else
            std::cout << "        ";
        std::cout << "PLAY!";
        if ( selected == 1 )
            std::cout << "      <-";
        endLine( 2 );

        tab( 27 );
        if ( selected == 2 )
            std::cout << "->     ";
        else
            std::cout << "       ";
        std::cout << "OPTIONS";
        if ( selected == 2 )
            std::cout << "     <-";
        endLine( 2 );

        tab( 27 );
        if ( selected == 3 )
            std::cout << "->      ";
        else
            std::cout << "        ";
        std::cout << "EXIT";
        if ( selected == 3 )
            std::cout << "      <-";
        std::cout << std::endl;

        Key=getKey();
        if ( Key == ARROW_DOWN )
            selected += 1;

        if ( Key == ARROW_UP )
            selected -= 1;

        if ( Key == KEY_ENTER ) {

            if ( selected == 1 )
                play ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );

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
}
