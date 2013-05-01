#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <string>
#include <cstring>
#include <stdint.h>

class grid {

	private:
		uint8_t **XO;
		uint8_t width;
		uint8_t height;
		uint8_t alignWinSize;
		uint8_t alignWinTotal;

	public:
		grid ( void );
		grid ( uint8_t height , uint8_t width , uint8_t newAlignWinSize , uint8_t newAlignWinTotal , bool vsIA );
		grid ( std::string file );
		~grid ( void );
		void draw ( void );
		void gravitate ( void );
		void play ( bool player );
		void IA_play ( void );
		void rotate ( bool clockwise );
		void insert ( bool player , uint8_t pos );
		uint8_t checkWin ( void );
		void save ( void );
		static bool initXO;
		static std::string ID;
		static bool IA;

	protected:

};

#endif
