#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

/*
Use pre-defined grammar of
SENTENCE -> NOUNPHRASE VERBPHRASE
NOUNPHRASE -> (OPTIONAL)DETERMINANT NOUN
VERBPHRASE -> VERB NOUNPHRASE
*/

using namespace std;

enum partOfSpeech {
	eDet = 0,
	eAdj,
	eNoun,
	eVerb
};

struct nounPhrase {
	string determinant;
	string adjective;
	string noun;
};

struct verbPhrase {
	string verb;
	nounPhrase np;
};

struct sentence {
	nounPhrase np;
	verbPhrase vp;
};

struct dictionary {
	unordered_map<std::string, partOfSpeech> wordMap;
	int build(std::string filePath);
};

void parse(std::string& in, size_t& outN, vector<string>& outSV) {
	if (in.size() == 0)
		return;
	outN = 1;
	for (int off = 0; in.find_first_of(' ', off) != in.npos; off = in.find_first_of(' ', off)) {
		outSV.push_back(in.substr(off, in.find_first_of(' ', off)));
	}
	if (outN == 1)
		outSV.push_back(in);
}

void updateWordMap(string filepath, unordered_map<string, partOfSpeech>& newWords) {
	if (newWords.size() == 0)
		return;
	ofstream file;
	file.open(filepath, ios::app);
	if (!file.is_open())
		return;
	unordered_map<string, partOfSpeech>::iterator it = newWords.begin();
	for (int i = 0; i < newWords.size(); ++i) {
		file << (*it).first + ' ' + to_string((*it).second) + '\n';
		advance(it, 1);
	}
}

int main() {
	dictionary dic;
	dic.build("wordMap.txt");
	unordered_map<std::string, partOfSpeech> unknownWords;

	std::string line;
	getline(cin, line);
	size_t nWords;
	vector<string> wordA;
	parse(line, nWords, wordA);
	for (int i = 0; i < wordA.size(); ++i) {
		if (dic.wordMap.find(wordA[i]) == dic.wordMap.end()) {
			cout << "I'm sorry. I don't know the word \"" << wordA[i] << "\".\n";
			cout << "Is it a \n\tDeterminant [0]\n";
			cout << "\tAdjective [1]\n";
			cout << "\tNoun [2]\n";
			cout << "\tVerb [3]\n";
			std::string answer;
			getline(cin, answer);
			cin.ignore();
			unknownWords.insert({ wordA[i], (partOfSpeech)atoi(answer.c_str()) });
		}
	}
	return 0;
}

int dictionary::build(string filePath) {
	ifstream file;
	file.open(filePath);
	if (!file.is_open())
		return 0;
	string line;
	while (getline(file, line)) {
		wordMap.insert({ 
			line.substr(0, line.find_first_of(' ')),
			(partOfSpeech)atoi(line.substr(line.find_first_of(' ')).c_str())});
	}
	file.close();
}
