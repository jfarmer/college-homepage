#ifndef _LEXICON_H
#define _LEXICON_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

class Lexicon {
public:
	map<string, vector <string> > successors;

		Lexicon(string);
		int successorFreq(string);
		bool isBreak(string, string, string);
};
#endif
