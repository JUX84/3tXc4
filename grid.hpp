#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <cstring>

class grid {

    private:
        int **XO;
        int width;
        int height;
        int alignWinSize;
        int alignWinTotal;

    public:
        grid ( void );
        grid ( int height , int width , int newAlignWinSize , int newAlignWinTotal );
        grid ( const char *file );
        ~grid ( void );
        void draw ( void );
        void gravitate ( void );
        void play ( int player );
        void rotate ( bool clockwise );
        void insert ( int player , int pos );
        int checkWin ( void );
        void save ( void );
        static bool initXO;

    protected:

};

#endif
