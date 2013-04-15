#ifndef _GRID_HPP_
#define _GRID_HPP_

class grid {

	private:
		int **XO;
		int width;
		int height;
		int size;
		int alignWinSize;
		int alignWinTotal;

	public:
		grid ( void );
		grid ( int height , int width , int newAlignWinSize , int newAlignWinTotal );
		//grid ( std::string file );
		~grid ( void );
		void draw ( void );
		void gravitate ( void );
		void play ( int player );
		void rotate ( bool clockwise );
		void insert ( int player , int pos );
		int checkWin ( void );
        bool initXO;

	protected:

};

#endif
