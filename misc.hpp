#ifdef _WIN32

#include <windows.h>
#include <CONIO.h>

#define clear system("cls")
#define wait(a) Sleep(a)

enum {
	KEY_ENTER = 13,
	ARROW_UP = 256 + 72,
	ARROW_DOWN = 256 + 80,
	ARROW_LEFT = 256 + 75,
	ARROW_RIGHT = 256 + 77
};

inline int getKey ( void ) {
	int Key = getch ();
	if ( Key == 0 || Key == 224 )
		Key = 256 + getch ();
	return Key;
}

#else

#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <cstdio>

#define clear system("clear")
#define wait(a) usleep(a*1000)

enum {
	KEY_ENTER = 10,
	ARROW_UP = 183,
	ARROW_DOWN = 184,
	ARROW_LEFT = 186,
	ARROW_RIGHT = 185
};

inline char getch ( void ) {

	struct termios oldattr, newattr;
	tcgetattr ( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr ( STDIN_FILENO, TCSANOW, &newattr );

	char ch = getchar ();

	tcsetattr ( STDIN_FILENO, TCSANOW, &oldattr );

	return ch;
}

inline int getKey ( void ) {

	int Key = getch ();

	if ( Key == 27 )
		Key += getch () + getch ();

	return Key;
}

#endif

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
