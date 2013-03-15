#ifndef _GRID_HPP_
#define _GRID_HPP_

//#include <cstring>
#include <CONIO.h>

enum
{
    KEY_ESC = 27,
    KEY_ENTER = 13,
    ARROW_UP = 256 + 72,
    ARROW_DOWN = 256 + 80,
    ARROW_LEFT = 256 + 75,
    ARROW_RIGHT = 256 + 77
};

static int getKey () {
    int ch = getch ();
    if ( ch == 0 || ch == 224 )
        ch = 256 + getch ();
    return ch;
}

class grid {

    private:
        int **XO;
        int size;
        int alignWinSize;
        int alignWinTotal;

    public:
        grid ();
        grid ( int newSize , int newAlignWinSize , int newAlignWinTotal );
        //grid ( std::string file );
        //~grid ();
        void draw ();
        void gravitate ();
        void play ( int player );
        void rotate ( bool clockwise );
        void insert ( int player , int pos );
        bool checkWin ( int player );
        bool checkLine ( int line );
        bool checkColumn ( int column );

    protected:

};

#endif // _GRID_HPP_
