#ifndef _GRID_HPP_
#define _GRID_HPP_

//#include <cstring>
#ifdef _WIN32

#include <windows.h>
#include <CONIO.h>

#define clear system("cls")
#define wait(a) Sleep(a)

#else

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define clear system("CLS")
#define wait(a) sleep(a*1000)

char getch ( void ) {
    struct termios oldattr, newattr;
    tcgetattr ( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr ( STDIN_FILENO, TCSANOW, &newattr );
    char ch = getchar ();
    tcsetattr ( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

#endif

enum {
    KEY_ESC = 27,
    KEY_ENTER = 13,
    ARROW_UP = 256 + 72,
    ARROW_DOWN = 256 + 80,
    ARROW_LEFT = 256 + 75,
    ARROW_RIGHT = 256 + 77
};

static int getKey ( void ) {
    int Key = getch ();
    if ( Key == 0 || Key == 224 )
        Key = 256 + getch ();
    return Key;
}

static void endLine ( int endl ) {
    int i;
    for ( i = 0 ; i < endl ; ++i )
        std::cout << std::endl;
}

static void tab ( int space ) {
    int i;
    for ( i = 0 ; i < space ; ++i )
        std::cout << " ";
}

class grid {

    private:
        int **XO;
        int size;
        int alignWinSize;
        int alignWinTotal;

    public:
        grid ( void );
        grid ( int newSize , int newAlignWinSize , int newAlignWinTotal );
        //grid ( std::string file );
        //~grid ( void );
        void draw ( void );
        void gravitate ( void );
        void play ( int player );
        void rotate ( bool clockwise );
        void insert ( int player , int pos );
        int checkWin ( void );

    protected:

};

#endif // _GRID_HPP_
