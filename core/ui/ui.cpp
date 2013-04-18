#include <ncurses.h>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include "ui.hpp"
#include "../grid/grid.hpp"
#include "../misc/misc.hpp"

bool warnExit ( void ) {

    int selected ( 1 );
    std::string STR_SELECTED;
    int TAB;
    int Key;
    int row , col;

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

        getmaxyx ( stdscr , row , col );

        clear ();

        attron ( A_BOLD );

        mvprintw ( row / 3 , ( col - STR_WARN_EXIT.length () + 1 ) / 2 , STR_WARN_EXIT.c_str () );

        mvprintw ( 2 * row / 3 , ( TAB * col / 3 ) - STR_SELECTED.length () - 2 , STR_ARROW_RIGHT.c_str () );
        mvprintw ( 2 * row / 3 , ( TAB * col / 3 ) + STR_SELECTED.length () , STR_ARROW_LEFT.c_str () );

        attroff ( A_BOLD );

        mvprintw ( 2 * row / 3 , ( col / 3 ) - ( STR_WARN_YES.length () / 2 ) , STR_WARN_YES.c_str () );
        mvprintw ( 2 * row / 3 , ( 2 * col / 3 ) - ( STR_WARN_NO.length () / 2 ) , STR_WARN_NO.c_str () );

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

void options_help ( void ) {

}

void options ( int &defaultHeight , int &defaultWidth , int &defaultAlignWinSize , int &defaultAlignWinTotal ) {

    int selected ( 1 );
    int i;
    int row,col;
    int backupHeight ( defaultHeight );
    int backupWidth ( defaultWidth );
    int backupAlignWinSize ( defaultAlignWinSize );
    int backupAlignWinTotal ( defaultAlignWinTotal );
    std::string STR_SELECTED;

    while ( true ) {

        getmaxyx ( stdscr , row , col );

        if ( selected < 1 )
            selected = 1;

        if ( selected > 4 )
            selected = 4;

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

        if ( defaultAlignWinTotal > 4 )
            defaultAlignWinTotal = 4;

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
            printw ( "-----" );
        for ( i = 4 ; i > defaultAlignWinTotal ; --i )
            printw ( "     " );
        printw ( "]" );

        mvprintw ( row - 4 , ( col - STR_OK.length () + 1 ) / 4 , STR_OK.c_str () );
        mvprintw ( row - 4 , 3 * ( col - STR_CANCEL.length () + 1 ) / 4 , STR_CANCEL.c_str () );

        refresh ();

        int Key = getch ();

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
            break;
        }

        if ( Key == KEY_F ( 1 ) )
            options_help ();
    }
}

void play ( grid *G , int height , int width , int alignWinSize , int alignWinTotal ) {

    if ( !grid::initXO ) {

        G = new grid ( height , width , alignWinSize , alignWinTotal );
    }

    int win;
    int Key;
    int row , col;

    while ( true ) {

        clear ();

        getmaxyx ( stdscr , row , col );

        attron ( A_BOLD );

        mvprintw ( 2 , 2 , STR_SAVE.c_str () );
        mvprintw ( 2 , 5 + STR_SAVE.length () , STR_SAVE_QUIT.c_str() );

        attroff ( A_BOLD );

        mvprintw ( row / 3 , ( col - STR_P1.length () + 1 ) / 2 , STR_P1.c_str () );

        mvprintw ( 2 * row / 3 , ( col - STR_CONTINUE.length () + 1 ) / 2 , STR_CONTINUE.c_str () );

        refresh ();

        Key = getch ();

        if ( Key == ESC || Key == KEY_E )
            break;

        if ( Key == KEY_F ( 1 ) )
            G->save ();

        if ( Key == KEY_F ( 2 ) ) {

            G->save ();
            break;
        }

        G->play ( 1 );
        G->gravitate ();

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

        G->play ( 2 );
        G->gravitate ();

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

        if ( win == 3 ) {

            mvprintw ( row / 2 , ( col - STR_TIE.length () + 1 ) / 2 , STR_TIE.c_str () );

            refresh ();

            wait ( 2000 );

            break;
        }
    }
}

void load_menu () {

    int Key;
    int i;
    int row , col;
    int top ( 0 );
    int selected ( 1 );
    std::string currentID;
    std::list<std::string> listID;
    std::list<std::string>::iterator it;
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

        for ( it = listID.begin() ; it != listID.end() ; ++it ) {

            currentID = (*it);

            if ( i >= top + 10 )
                break;

            if ( i >= top ) {
                
                if ( std::find ( vectorID.begin () , vectorID.end () , currentID ) == vectorID.end () )
                    vectorID.push_back( currentID );
            }

            ++i;
        }

        if ( selected < 1 )
            selected = 1;

        if ( selected > 20 )
            selected = 20;

        if ( selected >= 2 * vectorID.size() ) {

            selected = ( 2 * vectorID.size() ) - 1;
        }

        getmaxyx ( stdscr , row , col );

        clear ();

        attron ( A_BOLD );

        mvprintw ( row / 5 , ( col - STR_LOAD_MENU.length () + 1 ) / 2 , STR_LOAD_MENU.c_str () );

        mvprintw ( ( row / 3 ) + selected - 2 + ( selected % 2 ) , 5 * col / 20 , STR_ARROW_RIGHT.c_str () );
        mvprintw ( ( row / 3 ) + selected - 2 + ( selected % 2 ) , 15 * col / 20 , STR_ARROW_LEFT.c_str () );

        mvprintw ( 2 , 2 , STR_HELP.c_str () );

        attroff ( A_BOLD );

        for ( i = 0 ; i < vectorID.size () ; ++i ) {

            mvprintw ( ( row / 3 ) + ( i * 2 ) , ( col - 13 ) / 2 , vectorID[i].c_str() );
        }

        int current = ( selected - 0.5 ) / 2;
        currentID = vectorID[current];

        refresh ();

        Key = getch ();

        if ( Key == ENTER ) {

            if ( selected % 2 == 1 ) {

                grid *G = new grid ( currentID.c_str() );
                if ( grid::initXO ) {
                    play ( G , 5 , 5 , 5 , 1 );
                }
            }
            else {

                //delete_save ( currentID );
            }
        }

        if ( Key == KEY_DOWN )
            selected += 2;

        if ( Key == KEY_UP )
            selected -= 2;

        if ( Key == KEY_RIGHT && selected % 2 == 1 )
            selected++;

        if ( Key == KEY_LEFT && selected % 2 == 0 )
            selected--;

        if ( Key == ESC )
            return;
    }

    return;
}

void play_menu ( int height , int width , int alignWinSize , int alignWinTotal ) {

    int Key;
    int row , col;
    int selected ( 1 );

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
                play ( G , height , width , alignWinSize , alignWinTotal );
            }

            //if ( selected == 2 )

            if ( selected == 3 )
                load_menu ();

            break;
        }

        if ( Key == KEY_V ) {

            grid *G = new grid ();
            play ( G , height , width , alignWinSize , alignWinTotal );
        }

        //if ( Key == KEY_A )

        if ( Key == KEY_L )
            load_menu ();

        if ( Key == ESC )
            return;
    }
}

void ui_help ( void ) {

}

void ui ( void ) {

    int selected ( 1 );
    int defaultHeight ( 5 );
    int defaultWidth ( 5 );
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

                play_menu ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal );
            }

            if ( selected == 2 )
                options ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal );

            if ( selected == 3 ) {
                if ( warnExit () ) {
                    endwin ();
                    return;
                }
            }
        }

        if ( Key == KEY_P ) {

            play_menu ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal );
        }

        if ( Key == KEY_O )
            options ( defaultHeight , defaultWidth , defaultAlignWinSize , defaultAlignWinTotal );

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
