#ifdef _WIN32

#include <pdcurses/curses.h>

#else

#include <ncurses.h>

#endif

#include "grid.hpp"
#include "misc.hpp"

bool grid::initXO = false;

grid::grid ( void ) {

    int i , j;

    height = 5;
    width = 5;

    XO = new int*[height];
    for ( i = 0 ; i < height ; ++i )
        XO[i] = new int[width];

    for ( i = 0 ; i < height ; ++i ) {

        for ( j = 0 ; j < width ; ++j )
            XO[i][j] = 0;
    }

    alignWinSize = 5;
    alignWinTotal = 1;
}

grid::grid ( int newHeight , int newWidth , int newAlignWinSize , int newAligneWinTotal ) {

    int i , j;

    height = newHeight;
    width = newWidth;

    XO = new int*[height];
    for ( i = 0 ; i < height ; ++i )
        XO[i] = new int[width];

    for ( i = 0 ; i < height ; ++i ) {

        for ( j = 0 ; j < width ; ++j )
            XO[i][j] = 0;
    }

    alignWinSize = newAlignWinSize;
    alignWinTotal = newAligneWinTotal;

    initXO = true;
}

grid::~grid ( void ) {

    int i;

    for ( i = 0 ; i < height ; ++i )
        delete []XO[i];
    delete []XO;
}

void grid::insert ( int player , int pos ) {

    int i;
    int row , col;

    while ( true ) {

        getmaxyx ( stdscr , row , col );

        if ( pos < 0 )
            pos = 0;

        if ( pos > width - 1 )
            pos = width - 1;

        clear ();

        draw ();

        mvprintw ( ( row / 2 ) - ( height*2 / 2 ) - 1 , ( col / 2 ) - ( width*4 / 2 ) , "  " );

        for ( i = 0 ; i < pos ; ++i )
            printw ( "    " );

        if ( player == 1 )
            printw ( "X" );
        if ( player == 2 )
            printw ( "O" );

        refresh ();

        int Key = getch ();

        if ( Key == KEY_LEFT )
            pos--;

        if ( Key == KEY_RIGHT )
            pos++;

        if ( Key == ENTER ) {

            XO[0][pos] = player;
            break;
        }
    }
}

int grid::checkWin ( void ) {

    int i , j , k , l;
    int countX , countO;

    int Xi[4];
    int Oi[4];

    for ( i = 0 ; i < 4 ; ++i ) {

        Xi[i] = 0;
        Oi[i] = 0;
    }

    for ( i = 0 ; i < height ; ++i ) {

        for ( j = 0 ; j <= ( width - alignWinSize ) ; ++j ) {

            countX = 0;
            countO = 0;

            for ( k = j ; k < alignWinSize ; ++k ) {

                if ( XO[i][k] == 1 )
                    countX += XO[i][k];

                if ( XO[i][k] == 2 )
                    countO += XO[i][k];
            }

            if ( countX == alignWinSize )
                Xi[0] = 1;

            if ( countO == 2*alignWinSize )
                Oi[0] = 1;
        }
    }

    for ( i = 0 ; i <= ( height - alignWinSize ) ; ++i ) {

        for ( j = 0 ; j < width ; ++j ) {

            countX = 0;
            countO = 0;

            for ( k = i ; k < alignWinSize ; ++k ) {

                if ( XO[k][j] == 1 )
                    countX += XO[k][j];

                if ( XO[k][j] == 2 )
                    countO += XO[k][j];
            }

            if ( countX == alignWinSize )
                Xi[1] = 1;

            if ( countO == 2*alignWinSize )
                Oi[1] = 1;
        }
    }

    for ( i = 0 , j = 0 ; i <= ( std::min ( height , width ) - alignWinSize ) , j <= ( std::min ( height , width ) - alignWinSize ) ; ++i , ++j ) {

        countX = 0;
        countO = 0;

        for ( k = i , l = j ; k < alignWinSize , l < alignWinSize ; ++k , ++l ) {

            if ( XO[k][l] == 1 )
                countX += XO[k][l];

            if ( XO[k][l] == 2 )
                countO += XO[k][l];
        }

        if ( countX == alignWinSize )
            Xi[2] = 1;

        if ( countO == 2*alignWinSize )
            Oi[2] = 1;
    }

    for ( i = height - 1 , j = 0 ; i >= alignWinSize , j <= ( std::min ( height , width ) - alignWinSize ) ; --i , ++j ) {

        countX = 0;
        countO = 0;

        for ( k = i , l = j ; k > 0 , l < alignWinSize ; --k , ++l ) {

            if ( XO[k][l] == 1 )
                countX += XO[k][l];

            if ( XO[k][l] == 2 )
                countO += XO[k][l];
        }

        if ( countX == alignWinSize )
            Xi[3] = 1;

        if ( countO == 2*alignWinSize )
            Oi[3] = 1;
    }

    int X = Xi[0] + Xi[1] + Xi[2] + Xi[3];

    int O = Oi[0] + Oi[1] + Oi[2] + Oi[3];

    if ( X >= alignWinTotal )
        X = 1;
    else
        X = 0;

    if ( O >= alignWinTotal )
        O = 2;
    else
        O = 0;

    return X+O;
}

void grid::rotate ( bool clockwise ) {

    clear ();

    int i , j;
    int next_i , next_j;

    int **TMP_XO;

    TMP_XO = new int*[width];
    for ( i = 0 ; i < width ; ++i )
        TMP_XO[i] = new int[height];

    for ( i = 0 ; i < width ; ++i ) {

        for ( j = 0 ; j < height ; ++j )
            TMP_XO[i][j] = 0;
    }

    for ( i = 0 ; i < height ; ++i ) {

        for ( j = 0 ; j < width ; ++j ) {

            if ( XO[i][j] != 0 ) {

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
    }

    int tmp = width;
    width = height;
    height = tmp;

    XO = new int*[height];
    for ( i = 0 ; i < height ; ++i )
        XO[i] = new int[width];

    for ( i = 0 ; i < height ; ++i ) {

        for ( j = 0 ; j < width ; ++j )
            XO[i][j]=TMP_XO[i][j];
    }

    draw ();

    for ( i = 0 ; i < height ; ++i )
        delete []TMP_XO[i];
    delete []TMP_XO;
}

void grid::gravitate ( void ) {

    int i , j;

    bool modified(true);

    while(modified){

        modified=false;

        for ( i = 0 ; i < height-1 ; ++i ) {

            clear ();

            draw ();

            wait ( 200 );

            for ( j = 0 ; j < width ; ++j ) {

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
    std::string STR_SELECTED;
    int TAB;
    int row , col;
    int Key;

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

                    endLine ( 3 );

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
                            rotate ( true );

                        if ( selected == 4 )
                            rotate ( false );

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

void grid::draw ( void ) {

    int i , j;
    int row , col;

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
