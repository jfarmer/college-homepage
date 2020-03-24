#include "Lexicon.h"

extern bool quiet;

Lexicon::Lexicon (string file) {
	string line;
	ifstream lexicon;
	unsigned int i;
	
	if (!quiet) cout << "Loading lexicon from \"" + file + "\"...";
	fflush(NULL);
	lexicon.open(file.c_str());
	
	if (!lexicon) {
		cout << "error!" << endl;
		exit(1);
	}

	while(lexicon >> line) {
		string s;

		for (i = 1; i <= line.size(); i++ ) {
			string w = line.substr(0,i);
			if (line.substr(i,line.size()-i).size() == 0)
				s = "#";
			else
				s = line[i];
			
			if (find(successors[w].begin(), successors[w].end(), s) == successors[w].end())
				successors[w].push_back(s);	
		}
	}
	
	if (!quiet) cout << "done" << endl;
	fflush(NULL);
	
	lexicon.close();
}


int Lexicon::successorFreq(string s) {
	return successors[s].size();
}

bool Lexicon::isBreak(string w, string t, string u)
{
	double sw = (double)successorFreq(w);
	double st = (double)successorFreq(t);
	double su = (double)successorFreq(u);
	int k = w.size();
	bool a = (st/sw) >= 1.5;
	bool b = (st/su) >= 1.5;
	bool c = k > 2;
	
	return a && b && c;
}
