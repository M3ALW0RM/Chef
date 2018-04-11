#include "txtDictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

txtDictionary::txtDictionary()
{
}


txtDictionary::~txtDictionary()
{
}

void txtDictionary::build(std::string filePath)
{
	this->filePath = filePath;
	ifstream file;
	file.open(filePath);
	if (!file.is_open())
		return;
	string line;
	while (getline(file, line)) {
		wordMap.insert({
			line.substr(0, line.find_first_of(' ')),
			(partOfSpeech)atoi(line.substr(line.find_first_of(' ')).c_str()) });
	}
	file.close();
}

void txtDictionary::updateWordMap(unordered_map<std::string, int>& newWords, std::string filePath)
{
	if (filePath == "")
		filePath = this->filePath;
	if (newWords.size() == 0)
		return;
	ofstream file;
	file.open(filePath, ios::app);
	if (!file.is_open())
		return;
	unordered_map<std::string, int>::iterator it = newWords.begin();
	for (int i = 0; i < newWords.size(); ++i) {
		file << (*it).first + ' ' + to_string((*it).second) + '\n';
		advance(it, 1);
	}
}

bool txtDictionary::contains(std::string key)
{
	return (wordMap.find(key) != wordMap.end());
}
