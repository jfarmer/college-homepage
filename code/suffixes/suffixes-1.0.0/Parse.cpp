#include "Parse.h"

int Parse::a = 0;
int Parse::b = 0;
int Parse::c = 0;

void Parse::addBreak(int i) 
{
	breaks.push_back(i);
}

Parse::Parse(string p)
{
	cost = -1.0;
	phrase = p;
}
Parse::Parse(double c, string p, vector <int> v) 
{
	cost = c;
	phrase = p;
	breaks = v;
}

Parse::Parse(void)
{
	cost = -1.0;
	phrase = "";
	
}

string Parse::getPhrase(void)
{
	return phrase;
}

Parse Parse::operator +(Parse p)
{
	Parse r;
	unsigned int i;
	
	r.cost = cost + p.cost;
	r.phrase = phrase + p.phrase;
	
	/* If "phrase" is empty we shouldn't be adding any breaks */
	if (phrase.size())
		r.breaks = breaks;
	
	for (i = 0; i < p.breaks.size(); i++)
		r.breaks.push_back(p.breaks[i] + phrase.size());
	
	return r;
}

bool Parse::operator < (Parse p)
{
	return (p.cost < 0 || cost < p.cost);
}

string Parse::parse(void)
{
	
	return parse('#');
}

void Parse::compare(Parse *gold) 
{
	unsigned int i;
	
	for( i = 0; i < breaks.size() ; i++ ) {
		if (find(gold->breaks.begin(), gold->breaks.end(), breaks[i]) != gold->breaks.end())
			a++;
		else
			b++;
	}
	
	for( i = 0; i < (gold->breaks).size() ; i++ ) {
		if (find(breaks.begin(), breaks.end(), gold->breaks[i]) == breaks.end())
			c++;
	}
}

double Parse::precision(void)
{
	return a/((double)(a+b));
}

double Parse::recall(void)
{
	return a/((double)(a+c));
}
string Parse::parse(const char c)
{
	string parsedString;
	unsigned int i,j;
	j = 0;

	for ( i = 0; i <= phrase.size(); i++ ) {
		if ( j < breaks.size() && i == breaks[j] ) {
			parsedString.push_back(c);
			j++;
		}
		parsedString.push_back(phrase[i]);
	}
	
	return parsedString;
}
