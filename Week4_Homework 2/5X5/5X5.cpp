#include "Ranking.h"
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#define DIM 5 //5*5퍼즐

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };
static int DirKey[4] = { Left,Right,Up,Down };
static int map[DIM][DIM]; //퍼즐맵
static int x, y;// 빈칸의 위치 (x,y)
static int nMove;
static clock_t tStart;

static void init() {
	for (int i = 0; i < DIM * DIM - 1; i++) {
		map[i / DIM][i % DIM] = i + 1;
	}

	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1; y = DIM - 1; //3,3 고정

	srand(time(NULL)); //난수 발생 시작 설정
	tStart = clock(); //기준 시각 설정
	nMove = 0;  //이동 횟수 초기화 
}

static void display() {
	system("cls");
	printf("5x5 Puzzle\n\t");
	printf("--------------\n\t");
	for (int r = 0; r < DIM; r++) {
		for (int c = 0; c < DIM; c++) {
			if (map[r][c] > 0)
				printf("%3d", map[r][c]);
			else printf(" ");

		}
		printf("\n\t");
	}
	printf("--------------\n\t");
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	printf("\n\t이동 횟수: %6d\n\t소요 시간:%6.1f\n\n", nMove, d);

}

static bool move(int dir) {
	if (dir == Right && x > 0) {
		map[y][x] = map[y][x - 1];
		map[y][--x] = 0;

	}
	else if (dir == Left && x < DIM - 1) {
		map[y][x] = map[y][x + 1];
		map[y][++x] = 0;
	}
	else if (dir == Up && y < DIM - 1) {
		map[y][x] = map[y + 1][x];
		map[++y][x] = 0;

	}
	else if (dir == Down && y > 0) {
		map[y][x] = map[y - 1][x];
		map[--y][x] = 0;

	}
	else return false;

	nMove++;
	return true;
}

static void shuffle(int nshuffle) {
	for (int i = 0; i < nshuffle; i++) {
		int key = DirKey[rand() % 4];
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
	}
}

static bool isDone() {
	for (int r = 0; r < DIM; r++) {
		for (int c = 0; c < DIM; c++) {
			if (map[r][c] != r * DIM + c + 1)
				return (r == DIM - 1) && (c == DIM - 1);
		}
	}
	return true;
}

static int getDirKey() { return _getche() == 224 ? _getche() : 0; }
int play5x5Puzzle() {
	init();
	display();
	printRanking();
	printf("\n퍼즐을 섞어주세요(엔터)...");
	_getche();
	shuffle(100);
	printf("\n게임이 시작됩니다...");
	_getche();

	nMove = 0;
	tStart = clock();
	while (!isDone()) {
		move(getDirKey());
		display();
	}
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	return addRanking(nMove, d);


}