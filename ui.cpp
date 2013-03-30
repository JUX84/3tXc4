#include "ui.hpp"

bool warnExit ( void ) {

    int selected ( 1 );
    int Key;
    int row , col;

    while ( true ) {

        if ( selected < 1 )
            selected = 1;

        if ( selected > 2 )
            selected = 2;

        getmaxyx ( stdscr , row , col );

        clear ();

        attron ( A_BOLD );

        mvprintw ( row / 3 , ( col - STR_WARN_EXIT.length () + 1 ) / 2 , STR_WARN_EXIT.c_str () );

        mvprintw ( 2 * row / 3 , ( ( col - 30 ) / 3 ) + ( ( selected - 1 ) * 26 ) , STR_ARROW_RIGHT.c_str () );
        mvprintw ( 2 * row / 3 , ( ( col + 30 ) / 3 ) + ( ( selected - 1 ) * 26 ) , STR_ARROW_LEFT.c_str () );

        attroff ( A_BOLD );

        mvprintw ( 2 * row / 3 , ( col - STR_WARN_YES.length () + 1 ) / 3 , STR_WARN_YES.c_str () );
        mvprintw ( 2 * row / 3 , 2 * ( col - STR_WARN_NO.length () + 1 ) / 3 , STR_WARN_NO.c_str () );

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

        if ( Key == KEY_N )
            return false;

        if ( Key == ESC )
            return false;
    }
}

void options ( int &defaultSize , int &defaultAlignWinSize , int &defaultAlignWinTotal ) {

    int selected ( 1 );
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

        attron ( A_BOLD );

        mvprintw ( row / 4 , ( col - STR_TITLE_OPTIONS.length () + 1 ) / 2 , STR_TITLE_OPTIONS.c_str () );

        mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , ( col - 30 ) / 4 , STR_ARROW_RIGHT.c_str () );
        mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , col - ( ( col - 30 ) / 4 ) , STR_ARROW_LEFT.c_str () );

        attroff ( A_BOLD );

        mvprintw ( ( row / 2 ) , ( col - STR_HEIGHT.length() + 1 ) / 4 , STR_HEIGHT.c_str() );
        mvprintw ( ( row / 2 ) + 2 , ( col - STR_WIDTH.length() + 1 ) / 4 , STR_WIDTH.c_str() );
        mvprintw ( ( row / 2 ) + 4 , ( col - STR_ALIGN_SIZE.length() + 1 ) / 4 , STR_ALIGN_SIZE.c_str() );
        mvprintw ( ( row / 2 ) + 6 , ( col - STR_ALIGN_TOTAL.length() + 1 ) / 4 , STR_ALIGN_TOTAL.c_str() );

        refresh ();

        /*
            GOTTA CONTINUE
        */

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

        if ( Key == ESC ||Key == KEY_E )
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

        if ( Key == ESC || Key == KEY_E )
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

        if ( Key == ESC || Key == KEY_E )
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

        attron ( A_BOLD );

        mvprintw ( row / 4 , ( col - STR_TITLE_GAME.length () + 1 ) / 2 , STR_TITLE_GAME.c_str () );

        mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , ( col - 20 ) / 2 , STR_ARROW_RIGHT.c_str () );
        mvprintw ( ( row / 2 ) + ( ( selected - 1 ) * 2 ) , ( col + 20 ) / 2 , STR_ARROW_LEFT.c_str () );

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

            if ( selected == 1 )
                play ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );

            if ( selected == 2 )
                options ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );

            if ( selected == 3 ) {
                if ( warnExit () ) {
                    endwin ();
                    return;
                }
            }
        }

        if ( Key == KEY_P )
            play ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );

        if ( Key == KEY_O )
            options ( defaultSize , defaultAlignWinSize , defaultAlignWinTotal );

        if ( Key == ESC || Key == KEY_E ) {
            if ( warnExit () ) {
                endwin ();
                return;
            }
        }
    }
}
