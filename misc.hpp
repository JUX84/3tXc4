#ifdef _WIN32

#include <windows.h>

#define wait(a) Sleep(a)
#define ENTER 13
#define ESC 27

#else

#include <unistd.h>

#define wait(a) usleep(a*1000)
#define ENTER 13
#define ESC 27

#endif

#include <cstring>

static std::string STR_OPTIONS ( "[O]PTIONS" );
static std::string STR_TITLE ( "__3tXc4__" );
static std::string STR_PLAY ( "[P]LAY!" );
static std::string STR_EXIT ( "[E]XIT" );
static std::string STR_INSERT ( "[I]NSERT" );
static std::string STR_ROTATE ( "[R]OTATE" );
static std::string STR_P1 ( "Player 1 !" );
static std::string STR_P2 ( "Player 2 !" );
static std::string STR_WIN_P1 ( "Player 1 has won!" );
static std::string STR_WIN_P2 ( "Player 2 has won!" );
static std::string STR_CONTINUE ( "Press any key to continue ([E]SC to quit) ..." );
static std::string STR_ARROW_LEFT ( "<-" );
static std::string STR_ARROW_RIGHT ( "->" );
static std::string STR_TIE ( "It's a tie..." );
static std::string STR_WARN_EXIT ( "ARE YOU SURE?" );
static std::string STR_WARN_YES ( "[Y]ES" );
static std::string STR_WARN_NO ( "[N]" );
static std::string STR_HELP ( "NEED [H]ELP?" );


inline void endLine ( int endl ) {

	int i;

	for ( i = 0 ; i < endl ; ++i )
		std::cout << std::endl;
}

inline void tab ( int space ) {

	int i;

	for ( i = 0 ; i < space ; ++i )
		std::cout << " ";
}
