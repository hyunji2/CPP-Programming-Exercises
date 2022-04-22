#include "MineSweeper.h"
#define DIM 9   //9X9 ��� 

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };   //Hide,Open,Flag
static int MineMapMask[DIM][DIM];
static int MineMapLabel[DIM][DIM];
static int nx = DIM, ny = DIM;
static int nBomb = DIM;

//�������� ���� �Լ���
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx&& y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y) {          //(x,y)�� �Ĵ�(����)�Լ�
	if (isValid(x, y) && mask(x, y) != Open) {
		mask(x, y) = Open;
		if (label(x, y) == 0) {   //�� ���� ���ڰ� ������ �� ĭ ������ ��� ����ħ
			dig(x - 1, y - 1);
			dig(x - 1, y);
			dig(x - 1, y + 1);
			dig(x, y - 1);
			dig(x, y + 1);
			dig(x + 1, y - 1);
			dig(x + 1, y);
			dig(x + 1, y + 1);
		}
	}
}
static void mark(int x, int y) {               //(x,y)�� ����� �ȴ� �Լ�       
	if (isValid(x, y) && mask(x, y) == Hide)
		mask(x, y) = Flag;
}
static int getBombCount() {                   //����� ���� ����ϴ� �Լ�
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y) == Flag)count++;
	return count;
}




static void print() {                           //���� ���� ȭ�� ��� �Լ�
	system("cls");
	printf("�߰�:%2d ��ü:%2d\n", getBombCount(), nBomb);
	printf("  1 2 3 4 5 6 7 8 9 \n");    //x�� ǥ��
	for (int y = 0; y < ny; y++) {
		printf("%2c", 'A' + y);          //y�� ǥ��
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) == Hide)printf("��"); //���� ���� ��
			else if (mask(x, y) == Flag)printf("��");//���ڿ��� �ڸ�
			else {                             //�� �ڸ�    if mask(x,y)==Open
				if (isBomb(x, y))printf("��"); //9: ����!!
				else if (isEmpty(x, y))printf("  "); //0:��ĭ ǥ��
				else printf("%2d", label(x, y)); //1~8 ���� ǥ��    
			}
		}
		printf("\n");
	}
}
static int countNbrBombs(int x, int y) {//������ ������ �� ��� �Լ�
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy) == Bomb)
				count++;
	return count;
}
static void init(int total = 9) {
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {    //���� ��,����ũ �ʱ�ȭ
			mask(x, y) = Hide;
			label(x, y) = 0;
		}
	nBomb = total;
	for (int i = 0; i < nBomb; i++) {   //���ڸż�(total��)
		int x, y;
		do {
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y) != Empty);
		label(x, y) = Bomb;
	}
	for (int y = 0; y < ny; y++)    //������ ������ �� ���
		for (int x = 0; x < nx; x++)
			if (label(x, y) == Empty)
				label(x, y) = countNbrBombs(x, y);
}
static bool getPos(int& x, int& y) {       //Ű���� ��ǥ �Է� �Լ�
	printf("\n����(P)��(A-I)��(1-9)\n �Է� -->");

	bool isBomb = false;
	y = toupper(_getch()) - 'A';             //'a'->'A' 'A'-->0
	if (y == 'P' - 'A') {
		isBomb = true;
		y = toupper(_getche()) - 'A';         //'a'->'A' 'A'-->0
	}
	x = _getch() - '1';                   //'1'-->1
	return isBomb;
}
static int checkDone() {              //���� ���� �˻� �Լ�
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) != Open) count++;
			else if (isBomb(x, y)) return -1;
		}
	return (count == nBomb) ? 1 : 0;
}
void playMineSweeper(int total) {   //���� ã�� �� �Լ�
	int x, y, status;
	init(total);
	do {
		print();
		bool isBomb = getPos(x, y);
		if (isBomb)mark(x, y);
		else dig(x, y);
		status = checkDone();
	} while (status == 0);
	print();
	if (status < 0)
		printf("\n����: ���� ����!!!\n\n");
	else printf("\n����: Ž�� ����!!!\n\n");
}