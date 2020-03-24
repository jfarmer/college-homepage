#ifndef _PARSE_H
#define _PARSE_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Parse {
		double cost;
		string phrase;
		vector <int> breaks;
		static int a,b,c;
	public:
		Parse(double, string, vector <int>);
		Parse(string);
		Parse(void);
		Parse operator + (Parse);
		bool operator < (Parse);
		void addBreak(int);
		string getPhrase(void);
		string parse(void);
		string parse(const char);
		double precision(void);
		double recall(void);
		void compare(Parse *);
};

#endif
