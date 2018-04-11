#pragma once
#include <string>
#include <vector>

class txtDictionary;

struct nounPhrase {
	std::string determinant;
	std::string adjective;
	std::string noun;
};

struct verbPhrase {
	std::string verb;
	nounPhrase np;
};

struct sentence {
	nounPhrase np;
	verbPhrase vp;
};

class txtCommand
{
	std::vector<std::string> rawWords;
	void identifyUnknowns(txtDictionary& dictionary);
	void parse(std::string in);
public:
	txtCommand();
	~txtCommand();
	void getCommand(txtDictionary& dictionary);
};

