#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

typedef struct MOVEOBJECT {
	int x		// x ��ǥ
		, y		// y ��ǥ
		, wait; // ���ð�
}MOVEOBJECT;

// ȭ���� Ư�� ��ġ�� �̵��� �ִ� �Լ�.
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x - 1;
	Pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Ű�Է� �Լ�
BOOL isKeyState(int Key) {
	// http://seokr.tistory.com/473
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

/**
 * �ܼ� ȭ�� ���� �Լ�
 */
void systemSetting() {

	// 1. �ܼ� ȭ�� ����
	// Colums 100 Lines 30�� �԰����� �ϴ� �ܼ��� �����Ѵ�.
	system("mode con: cols=100 lines=30");

	// 2. Ÿ��Ʋ ����
	system("title F ���� ���ϱ� ���� (������ : ������, �輮��, �ڵ���)");

	// 3. �ܼ� ȭ�� �� �ٲٱ�
	system("Color 0B");

}

/**
 * ���� �޴� ȭ��
 */
void mainMenu() {
	// 100 / 30
	gotoxy(37, 10);
	cout << " - F ���� ���ϱ� - " << "\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(40, 12);
	cout << " �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(40, 14);
	cout << " �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(40, 16);
	cout << " �� �� �� �� " << "\n";
}
/**
 * �� �� �� ��
 */
void description() {

}

/**
* ���� �˰��� �Լ�
*/
void game(int stage) {

	// ���������� ���̵� ����
	switch (stage) {
	case 2:
		system("mode con: cols=120 lines=30");
		break;
	}

	// ���� ���(F)�� ��Ʈ ������(0)
	system("Color F0");
	int speed = 100 - stage * 15;
	MOVEOBJECT fallingObject[100];


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x00); // �ٴ� ������ 
	printf("��������������������������");
	printf("��������������������������");

	// ����ü F���� ��ǥ �� ��� �ð� �ʱ�ȭ
	for (int i = 0; i < 100; i++) {
		fallingObject[i].x = rand() % 120 + 1;	// x��ǥ 1 ~ 100 ���� �������� �����Ѵ�.
		fallingObject[i].y = 0;					// y��ǥ 2���� ����
		fallingObject[i].wait = rand() % 100;	// ���� ���ð��� �־� �� �ٷ� �������� �ʰ� �Ѵ�.
	}

	while (1) {

		Sleep(speed); // Sleep() �Լ��� ���� �ӵ� ����
		system("cls");

		for (int i = 0; i < 100; i++) {
			// ��� �ð�
			if (fallingObject[i].wait > 0)
			{
				// ���ð� ���� ���� ���� ����߸��� �ʴ´�.
				fallingObject[i].wait--;
			}
			else {
				// F ������ ��ĭ �Ʒ��� �̵��Ѵ�.
				fallingObject[i].y++;
				// F ������ ���ϴܿ� ���� ���� �� ó��.
				if (fallingObject[i].y >= 28) {
					fallingObject[i].x = rand() % 120 + 1;
					fallingObject[i].y = 3;
				}
				// F ���� ���
				gotoxy(fallingObject[i].x, fallingObject[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("F");
			}
		}

	}
}
/**
 * ���� �޴� ���� �Լ�
 */
void controller() {
	
}


void main() {
	systemSetting(); 
	mainMenu(); // ���� �޴�
	controller(); // �޴� ���� �Լ�
}