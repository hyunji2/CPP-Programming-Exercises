#include <iostream>
#include <fstream>
#define MAXWORDS 7
using namespace std;

struct WordPair {
	string eng;
	string kor;
};

class MyDic {
	WordPair words[MAXWORDS];
	int nWords = MAXWORDS;
public:
	void add(string eng, string kor) {
		ofstream fs("Words.txt", ios::app);
		fs << eng << " " << kor << endl;
		fs.close();
	}
	void load(string filename) {
		ifstream fs(filename);
		for (int i = 0; i < nWords; i++)
			fs >> words[i].eng >> words[i].kor;
		fs.close();
	}
	void store(string filename) {
		ofstream fs(filename);
		fs << nWords << endl;
		for (int i = 0; i < nWords; i++)
			fs << words[i].eng << " " << words[i].kor << endl;
		fs.close();
	}
	void print() {
		cout << "\n<Words.txt>\n";
		for (int i = 0; i < nWords; i++)
			cout << words[i].eng << " " << words[i].kor << endl;
	}
	string getEng(int id) {
		return words[id].eng;
	}
	string getKor(int id) {
		return words[id].kor;
	}
};