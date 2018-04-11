#pragma once
#include <string>
#include <unordered_map>
enum class partOfSpeech : int {
	eDet,
	eAdj,
	eNoun,
	eVerb
};
class txtDictionary
{
	std::unordered_map<std::string, partOfSpeech> wordMap;
	std::string filePath;
public:
	txtDictionary();
	~txtDictionary();
	void build(std::string filePath);
	void updateWordMap(std::unordered_map<std::string, int>& newWords, std::string filepath = "");
	bool contains(std::string key);
};

