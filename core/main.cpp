#include <ncurses.h>
#include "ui/ui.hpp"
#include "misc/misc.hpp"

int main ( int argc , char **argv ) {

    initscr (); // ncurses screen init
    timeout ( -1 ); // disable getch timeout
    raw (); // disable buffer
    keypad ( stdscr , TRUE ); // enable arrow keys
    noecho (); // disable getch echo
    curs_set ( 0 ); // disable cursor blinking

    ui (); // main menu

    return 0;
}
