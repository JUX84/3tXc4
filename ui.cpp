#include <iostream>
#include "pdcurses/curses.h"
#include "misc.hpp"
#include "grid.hpp"

bool warnExit ( void ) {

    int selected (1);
    int Key;

    while ( true ) {

        if ( selected < 1 )
            selected = 1;

        if ( selected > 2 )
            selected = 2;

        clear ();

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

        Key = getch ();

        if ( Key == KEY_LEFT )
            selected -= 1;

        if ( Key == KEY_RIGHT )
            selected += 1;

        if ( Key == ENTER ) {

            if ( selected == 1 )
                return true;

            if ( selected == 2 )
                return false;
        }
    }
}

void options ( int &defaultSize , int &defaultAlignWinSize , int &defaultAlignWinTotal ) {

    int selected ( 1 );
    int i;
    int row,col;

    while ( true ) {

        getmaxyx ( stdscr , row , col );

        if ( selected < 1 )
            selected = 1;

        if ( selected > 4 )
            selected = 4;

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

        clear ();

        mvprintw ( row / 4 , ( col - STR_OPTIONS.length () + 1 ) / 2 , STR_OPTIONS.c_str () );

        endLine ( 6 );

        tab ( 20 );

        if ( selected == 1 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "Size";

        tab ( 7 );

        std::cout << defaultSize;

        if ( defaultSize < 10 )
            std::cout << " ";

        tab ( 2 );

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

        tab ( 15 );

        if ( selected == 2 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "Alignment Size";

        tab ( 2 );

        std::cout << defaultAlignWinSize;

        if ( defaultAlignWinSize < 10 )
            std::cout << " ";

        tab ( 2 );

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

        tab ( 14 );

        if ( selected == 3 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "Alignment Total";

        tab ( 2 );

        std::cout << defaultAlignWinTotal;

        if ( defaultAlignWinTotal < 10 )
            std::cout << " ";

        tab ( 2 );

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

        endLine ( 3 );

        tab ( 33 );

        if ( selected == 4 )
            std::cout << "-> ";
        else
            std::cout << "   ";

        std::cout << "[OK]";

        if ( selected == 4 )
            std::cout << " <-";
        else
            std::cout << "   ";

        endLine ( 1 );

        int Key = getch ();

        if ( Key == KEY_LEFT ) {

            if ( selected == 1 )
                defaultSize--;

            if ( selected == 2 )
                defaultAlignWinSize--;

            if ( selected == 3 )
                defaultAlignWinTotal--;
        }

        if ( Key == KEY_RIGHT ) {

            if ( selected == 1 )
                defaultSize++;

            if ( selected == 2 )
                defaultAlignWinSize++;

            if ( selected == 3 )
                defaultAlignWinTotal++;
        }

        if ( Key == KEY_DOWN )
            selected++;

        if ( Key == KEY_UP )
            selected--;

        if ( Key == ENTER && selected == 4 )
            break;

        if ( Key == ESC )
            break;
    }
}

void play ( int size , int alignWinSize , int alignWinTotal ) {

    grid G ( size , alignWinSize , alignWinTotal );
    int win;
    int Key;
    int row , col;

    while ( true ) {

        clear ();

        getmaxyx ( stdscr , row , col );

        mvprintw ( row / 3 , ( col - STR_P1.length () + 1 ) / 2 , STR_P1.c_str () );

        mvprintw ( 2 * row / 3 , ( col - STR_CONTINUE.length () + 1 ) / 2 , STR_CONTINUE.c_str () );

        refresh ();

        Key = getch ();

        if ( Key == ESC )
            break;

        G.play ( 1 );
        G.gravitate ();

        win = G.checkWin ();

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

        if ( win == 3 ) {

            mvprintw ( row / 2 , ( col - STR_TIE.length () + 1 ) / 2 , STR_TIE.c_str () );

            refresh ();

            wait ( 2000 );

            break;
        }

        mvprintw ( row / 3 , ( col - STR_P2.length () + 1 ) / 2 , STR_P2.c_str () );

        mvprintw ( 2 * row / 3 , ( col - STR_CONTINUE.length () + 1 ) / 2 , STR_CONTINUE.c_str () );

        refresh ();

        Key = getch ();

        if ( Key == ESC )
            break;

        G.play ( 2 );
        G.gravitate ();

        if ( G.checkWin () == 1 ) {

        }

        if ( G.checkWin () == 2 ) {

        }
    }
}

void ui ( void ) {

    int selected ( 1 );
    int defaultSize ( 5 );
    int defaultAlignWinSize ( 5 );
    int defaultAlignWinTotal ( 1 );
    int Key;
    int row , col;

    while ( true ) {

        clear ();

        getmaxyx ( stdscr , row , col );

        if ( selected < 1 )
            selected = 1;

        if ( selected > 3 )
            selected = 3;

        attron(A_BOLD);

        mvprintw ( row / 4 , ( col - STR_TITLE.length () + 1 ) / 2 , STR_TITLE.c_str () );

        mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , ( col - 20 ) / 2 , STR_ARROW_RIGHT.c_str () );
        mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , ( col + 20 ) / 2 , STR_ARROW_LEFT.c_str () );

        attroff(A_BOLD);

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

            if ( selected == 1 )
                play ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );

            if ( selected == 3 ) {
                if ( warnExit () ) {
                    endwin ();
                    return;
                }
            }

            if ( selected == 2 )
                options ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );
        }

        if ( Key == ESC ) {
            if ( warnExit () ) {
                endwin ();
                return;
            }
        }
    }
}
