#include <iostream>
#include <Windows.h> // ����
#include <conio.h> // _kbhit(), _getch() �Լ�
#include <stdlib.h> // exit() �Լ��� ���
// #include <time.h>  // Srand((unsigned int)time(NULL)) �ϸ� ����ü�� �̻��ϰ� ������

using namespace std;
/**
 * ����ü�� �������� ���� �� ����ü
 */
typedef struct {
	int x		// x ��ǥ
		, y		// y ��ǥ
		, wait; // ���ð�
}MOVEOBJECT;

// ȭ���� Ư�� ��ġ�� �̵��� �ִ� �Լ�.
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// ��� �̵� Ű �Է� �Լ�
BOOL isKeyState(int Key) {
	// http://seokr.tistory.com/473
	// Ű������ Ű�� ���ȴ��� üũ�ϴ� �Լ�
	// GetAsyncKeyState()�� �� ����ó�� �Լ�
	// GetAsyncKeyState()�� Ű�� ������ �������� 0x8000 ���� ���� - ���� Ű�� ������ ����
	// �Լ��� ȣ��Ǿ��� �� Ű�� ������ �־��ٰ� 0x0001 ���� ���� - ������ ȣ��� �̹� ȣ�� ���̿� Ű�� ������ ���� �־��ٴ� ǥ��
	// ��, ��Ȯ�� �������� Ű���� ���¸� üũ �ϱ� ���ؼ� 0x8000���� AND ������ �� �ִ� ���̴�.
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
	// 120 / 30
	gotoxy(37, 10);
	cout << " - F ���� ���ϱ� - " << "\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(40, 12);
	cout << " 1. �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(40, 14);
	cout << " 2. �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(40, 16);
	cout << " 3. �� �� �� �� " << "\n";
}

/**
 * ���ھ ���� ���� ��� �Լ�
 */
void result() {
	
}

/**
 * �� �� �� ��
 */
void description() {

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 01	|	SeokRae		|	�ű�		|
* @Description
*		���� ���̵��� ���� Console Setting
*		level 1 ~ 5 ���� ����
*/
void stageSetting(int level) {

	// ���������� ���̵� ����
	switch (level) {
	case 1:
		system("cls");
		system("mode con: cols=100 lines=30");
		system("Color 04");
		gotoxy(37, 10); cout << "F ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 2:
		system("cls");
		system("mode con: cols=120 lines=30");
		gotoxy(37, 10); cout << "D ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 3:
		system("cls");
		system("mode con: cols=140 lines=30");
		gotoxy(37, 10); cout << "C ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 4:
		system("cls");
		system("mode con: cols=160 lines=30");
		gotoxy(37, 10); cout << "B ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 5:
		system("cls");
		system("mode con: cols=180 lines=30");
		gotoxy(37, 10); cout << "A ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	default:
		break;
	}
}


/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 01	|	SeokRae		|	�ű�		|
* @Description
*		���� ���� �Լ�
*/
void game(int stage) {
	stageSetting(stage); // ���̵��� ���� �ܼ�â ���� �Լ� ȣ��
	int life = 100; // ��ü ������

	int speed = 75 - stage * 15; // ���̵� ����

	MOVEOBJECT mObj[100], user; // ����ü�� ����� ����ü
	
	bool flag = true; // ���� �ݺ����� ���� bool ����
	
	// ����ü F���� ����, ��ǥ, ��� �ð� [�ʱ�ȭ]
	for (int i = 0; i < 50; i++) {
		mObj[i].x = rand() % 100 + 1;	// x��ǥ 1 ~ 100 ���� �������� �����Ѵ�.
		mObj[i].y = 0;					// y��ǥ 2���� ����
		mObj[i].wait = rand() % 100;	// ���� ���ð��� �־� �� �ٷ� �������� �ʰ� �Ѵ�.
	}

	// ���� ���� ��ġ [�ʱ�ȭ]
	user.x = 60;
	user.y = 25;

	
	/*
	* ���� ������ �κ�
	*/
	while (flag) {
		Sleep(speed); // Sleep() �Լ��� ���� �ӵ� ����
		system("cls"); // ȭ�� �����
	
		// �Ͻ�����
		if (_kbhit()) { // Ű���� ���ȴ��� Ȯ��
			int key = _getch();
			switch (key) {
			case 'c':
				gotoxy(72, 0);
				printf("PAUSE");
				while (1)
				{
					key = _getch();
					if (key == 'c')
						break;
				}
				gotoxy(72, 0);
				printf("    ");
				break;
			}
		}
		// ��� ������ ó��
		if (isKeyState(VK_LEFT)) {
			if (user.x > 1)	{
				user.x -= 2;
			}
		}
		if (isKeyState(VK_RIGHT)) {
			if (user.x <= 100) {
				user.x += 2;
			}
		} // ��� ������ ó�� ��

		// ��� ���
		gotoxy(user.x, user.y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("��");
		gotoxy(user.x, user.y + 1);
		printf("��");
		gotoxy(user.x, user.y + 2);
		printf("��");


		for (int i = 0; i < 50; i++) { // * 50 ����ü ���� ���̵��� ���� �ٲ�� ��
			// ��� �ð�
			if (mObj[i].wait > 0) {
				// ��� �ð��� �־� �� �ٷ� ����ü�� �������� �ʵ��� �Ѵ�.
				mObj[i].wait--;
			} else {
				// ����ü�� ��ĭ �Ʒ��� �̵��Ѵ�.
				mObj[i].y++;
				// F ������ ���ϴܿ� ���� ���� �� ó��.
				if (mObj[i].y >= 28) {
					mObj[i].x = rand() % 100 + 1;
					mObj[i].y = 3;
				}
				// F ���� ���
				gotoxy(mObj[i].x, mObj[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				printf("F");

				// ����ü�� ������� �Ӹ� ������ ���밪�� 2 ���� �۰�, y��ǥ���� ���� ��� �浹
				if (abs(mObj[i].x - user.x) < 2 && mObj[i].y == user.y) {
					// ������ ���.
					printf("\a");
					flag = false;
				}
			}
		}
	}
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 02	|	SeokRae		|	�ű�		|
* @Description
*		���� �޴��� �ش��ϴ� ������ �ޱ� ���� ����ó�� �Լ�
*/
char isCheckNum() {
	// cout << "isCheckNum()" << "\n";
	char checkNum = _getch();
	// cout << checkNum << "\n";
	// �޴��� ����(1 ~ 3)�ܿ� �ٸ� ���ڰ� �Է� �� ��� 
	// �ٽ� �Է��ϰԲ� ������ ȭ��� ������ ����
	switch (checkNum) {
	case '1':
	case '2':
	case '3':
		return checkNum;
	default :
		return isCheckNum();
	}
}

/**
 * @author SeokRae
 * @History
 *		|	Date			|	Author		|	���� ����	|
 *		|	2017. 06. 02	|	SeokRae		|	�ű�		|
 * @Description
 *		���� �޴� ���� �Լ�
 */
void controller() {
	int level = 1;
	
	char selectNum = isCheckNum(); // 1 ~ 3 �̿ܿ� ���� ���� ��� ��� �Ѵ�.
	// selectNum = _getch(); // Ű������ Ű ���� �Է� �޾� char ������ ����
	switch (selectNum) {
	case '1': // 1. ���� ����
		game(level);
		break;
	case '2': // 2. ���� ����
		description(); // ���� ���� �Լ� ȣ��
		break;
	case '3': // 3. ���� ����
		exit(0); // �ý��� ���� �Լ� ȣ��
		break;
	default:
		break;
	}
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����									|
*		|	2017. 06. 01	|	SeokRae		|	systemSetting(), mainMenu(), controller() 	|
*		|	2017. 06. 		|				|	 											|
* @Description
*		���� �Լ�
*/
void main() {
	systemSetting(); 
	while (1) {
		mainMenu(); // ���� �޴�
		controller(); // �޴� ���� �Լ�
	}
}