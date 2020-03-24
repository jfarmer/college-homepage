#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

#include "Lexicon.h"
#include "Parse.h"

#define DEFAULT_DATA "data/kjv"

using namespace std;

string doParse(Lexicon *, Parse *);
void usage(const char *);
bool quiet = false;

int main(int argc, char **argv) {
	size_t i,j;
	string data = DEFAULT_DATA;
	string s = "";
	Parse *p, *q;
	Lexicon *lexicon;

	for (i = 1; i < argc; i++) {
		string arg = argv[i];
		for (j = 0; j < arg.size() - 1; j++ ) {
			if (arg[0] == '-') {
				switch (arg[1]) {
					case 'd':
						if (i+1 == argc) {
							cerr << "ERROR: No filename specified, but -d option supplied." << endl;
							usage(argv[0]);
							return 0;
						}
						data = argv[++i];
						break;
					case 's':
						if (i+1 == argc) {
							cerr << "ERROR: No string specified, but -s option supplied." << endl;
							usage(argv[0]);
							return 0;
						}
						s = argv[++i];
						break;
					case 'q':
						quiet = true;
						break;
					case 'h':
						usage(argv[0]);
						return 0;
						break;
					default:
						break;
				}
			}
		}
	}

	if (s.length() == 0) {
		usage(argv[0]);
		return 0;
	}


	lexicon = new Lexicon(data);

	if (s == "-") {
		while(getline(cin, s)) {
			string s1, s2, tmp;
			vector <int>breaks;
			i = s.find("\t");

			if (i == string::npos)
				continue;
			s1 = s.substr(0,i);
			tmp = s.substr(i+1,s.length()-i-1);

			for (j = 0; j < tmp.length(); j++) {
				if (tmp[j] == '|') {
					// Insert a morpheme break, and then use everything after the break
					breaks.push_back(j);
					tmp = tmp.substr(0,j) + tmp.substr(j+1, tmp.length() - j -1);
					j++;
				}
			}
			q = new Parse(0.0, tmp, breaks);
			p = new Parse(s1);

			cout << doParse(lexicon, p) << endl;
			p->compare(q);
		}
	} else {
		p = new Parse(s);
		cout << doParse(lexicon, p) << endl;
	}

	cout << "------------" << endl;
	cout << "Precision:  " << p->precision() << endl;
	cout << "Recall:     " << p->recall() << endl;
	cout << "F-score:    " << 2 * 1/(1/p->precision() + 1/p->recall()) << endl;
}

void usage(const char *app)
{
	cout << "USAGE" << endl;
	cout << "  " << app << " -s [<string>|-]" << endl;
	cout << "OPTIONS" << endl;
	cout << "  -d <file>         Use <file> as the training data.  Default is 'data/kjv'" << endl;
	cout << "  -h                Display this message." << endl;
	cout << "  -q                Turn off verbose messages." << endl;
	cout << "  -s [<string>|-]   Parse <string>.  If <string> is '-' then read data from stdin." << endl;
}

string doParse(Lexicon *lexicon, Parse *p)
{
	unsigned int i;
	string s = p->getPhrase();

	for( i = 0; i < s.size(); i++ ) {
		string w = s.substr(0,i);
		string t = s.substr(0,i+1);
		string u = s.substr(0,i+2);

		if (lexicon->isBreak(w,t,u)) p->addBreak(i+1);
	}

	return p->parse('|');
}
