#include <curses.h>
#include "txtDictionary.h"
#include "txtCommand.h"

/*
Use pre-defined grammar of
SENTENCE -> NOUNPHRASE VERBPHRASE
NOUNPHRASE -> (OPTIONAL)DETERMINANT (OPTIONAL)ADJECTIVE NOUN
VERBPHRASE -> VERB NOUNPHRASE
*/

using namespace std;

int main(int argc, char *argv[])
{
	initscr();
	printw("Type a command!\n");
	refresh();
	txtDictionary dict;
	dict.build("wordMap.txt");
	txtCommand command;
	command.getCommand(dict);
	

	endwin();
	return 0;
}