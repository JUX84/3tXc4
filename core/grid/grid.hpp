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
		uint8_t AI_prof;

	public:
		grid ( void );
		grid ( uint8_t height , uint8_t width , uint8_t newAlignWinSize , uint8_t newAlignWinTotal , bool vsIA );
		grid ( std::string file );
		~grid ( void );
		void draw ( void );
		void gravitate ( bool silent );
		void play ( bool player );
		int AI_value ( void );
		void AI_play ( void );
		bool full ( void );
		int calcMin ( uint8_t prof );
		int calcMax ( uint8_t prof );
		uint8_t minimax ( uint8_t prof );
		void rotate ( bool silent , bool clockwise );
		void insert ( bool player , uint8_t pos );
		uint8_t checkWin ( void );
		void save ( void );
		static bool initXO;
		static std::string ID;
		static bool AI;

	protected:

};

#endif
