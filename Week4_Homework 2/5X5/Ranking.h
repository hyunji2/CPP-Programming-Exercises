#pragma once

struct PlayInfo {
	char name[200];
	int nMove;
	double tElapsed;
};



extern void loadRanking(const char* filename);
extern void storeRanking(const char* fname);
extern void printRanking();
extern int addRanking(int nMove, double tElap);