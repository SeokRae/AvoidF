#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;
/**
 * ����ü�� �������� ���� �� ����ü
 */
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
*		���� ���̵� ���� �Լ�
*/
void changeStage(int level) {

	// ���������� ���̵� ����
	switch (level) {
	case 1:
		system("cls");
		system("mode con: cols=100 lines=30");
		gotoxy(37, 10); cout << "F ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 2:
		system("mode con: cols=120 lines=30");
		gotoxy(37, 10); cout << "D ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 3:
		system("mode con: cols=140 lines=30");
		gotoxy(37, 10); cout << "C ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 4:
		system("mode con: cols=160 lines=30");
		gotoxy(37, 10); cout << "B ������ ���ض� !!" << "\n";
		Sleep(1500);
		break;
	case 5:
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
	// ���� ���(F)�� ��Ʈ ������(0)
	system("Color F0");
	int speed = 75 - stage * 15; // ���̵� ����

	changeStage(stage); // ���̵��� ���� �ܼ�â ���� �Լ� ȣ��
	
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
		system("cls"); // ȭ�� �����

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
// ���ڸ� �޵��� �ϴ� ����Լ�
char isCheckNum() {
	cout << "isCheckNum()" << "\n";
	char checkNum = _getch();
	cout << checkNum << "\n";
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
 *		|	2017. 06.		|				|	�ű�		|
 * @Description
 *		���� �޴� ���� �Լ�
 */
void controller() {
	int level = 1;
	char selectNum = isCheckNum(); // 1 ~ 3 �̿ܿ� ���� ���� ��� ��� �Ѵ�.
	cout << "selectNum : " << selectNum << "\n";
//	selectNum = _getch(); // Ű������ Ű ���� �Է� �޾� char ������ ����
	while (1) {
		switch (selectNum) {
		case '1': // 1. ���� ����
			selectNum = 0;
			game(level);
			break;
		case '2': // 2. ���� ����
			description(); // ���� ���� �Լ� ȣ��
			break;
		case '3': // 3. ���� ����
			break;
		default:
			break;
		}
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
	mainMenu(); // ���� �޴�
	controller(); // �޴� ���� �Լ�
}