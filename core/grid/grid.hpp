#ifndef _GRID_HPP_
#define _GRID_HPP_

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
		grid ( uint8_t height , uint8_t width , uint8_t newAlignWinSize , uint8_t newAlignWinTotal , bool vsIA , uint8_t AI_prof );
		grid ( std::string file );
		grid ( grid *G );
		~grid ( void );
		void destroy ( void );
		void draw ( void );
		void gravitate ( bool silent );
		void play ( bool player );
		int8_t AI_value ( void );
		void AI_play ( void );
		bool full ( void );
		int8_t min ( uint8_t prof , int8_t alpha , int8_t beta );
		int8_t max ( uint8_t prof , int8_t alpha , int8_t beta );
		uint8_t minimax ( uint8_t prof );
		void rotate ( bool silent , bool clockwise );
		void insert ( bool player , int8_t pos );
		uint8_t checkWin ( void );
		void save ( void );
		void invert ( void );
		uint8_t getWidth ( void );
		uint8_t getHeight ( void );
		uint8_t getAlignWinSize ( void );
		uint8_t getAlignWinTotal ( void );
		uint8_t getAI_prof ( void );
		uint8_t getXO ( uint8_t i , uint8_t j );
		static bool initXO;
		static std::string ID;
		static bool AI;

	protected:

};

#endif
