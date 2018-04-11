#include "txtCommand.h"
#include "txtDictionary.h"

#include <curses.h>
#include <unordered_map>


using namespace std;

txtCommand::txtCommand()
{
}


txtCommand::~txtCommand()
{
}

void txtCommand::parse(std::string in) {
	if (in.size() == 0)
		return;
	std::string temp;
	int len = in.size();
	for (int i = 0; i<len; i++)
	{
		bool isSeparator = false;
		if (in[i] == ' ')
			isSeparator = true;
		if (!isSeparator)
		{
			temp += in[i];
			continue;
		}
		if (temp != "")
			rawWords.push_back(temp);
		temp = "";
	}
	if (temp != "")
		rawWords.push_back(temp);
}

void txtCommand::identifyUnknowns(txtDictionary & dictionary)
{
	unordered_map<std::string, int> unknownWords;
	for (int i = 0; i < rawWords.size(); ++i) {
		if (!dictionary.contains(rawWords[i])) {
			printw("I'm sorry. I don't know the word \"%s\".\n", rawWords[i].c_str());
			printw("Is it a \n\tDeterminant [1]\n");
			printw("\tAdjective [2]\n");
			printw("\tNoun [3]\n");
			printw("\tVerb [4]\n");
			printw("\tOr a mistake [0]\n");
			std::string answer;
			int input;
			refresh();
			input = getch();
			if (input - 49 == -1) {
				printw("\n");
				noecho();
				getch();
				echo();
				continue;
			}
			noecho();
			getch();
			echo();
			printw("\n");
			unknownWords.insert({ rawWords[i], input - 49 });
		}
	}
	dictionary.updateWordMap(unknownWords);
}

void txtCommand::getCommand(txtDictionary & dictionary)
{
	std::string line;
	char command[50];
	getstr(command);
	line = command;
	parse(line);
	identifyUnknowns(dictionary);
}