#include "Hangman.h"
#include "MyDic.h"

void main()
{
	Hangman	game;
	MyDic words;
	words.load("Word.txt");
	srand((unsigned int)time(NULL));
	int i = rand() % MAXWORDS;
	//game.play("galaxy");
	game.play(words.getEng(i), words.getKor(i));
}