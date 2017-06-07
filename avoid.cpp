#include <iostream>
#include <Windows.h> // ����
#include <conio.h> // _kbhit(), _getch() �Լ�
#include <stdlib.h> // exit() �Լ��� ���
// #include <time.h>  // Srand((unsigned int)time(NULL)) �ϸ� ����ü�� �̻��ϰ� ������
#include <map>
#include <string>


#define MAP_X 100
#define MAP_Y 30
#define COUNT 100

using namespace std;

int score;
int stage;
int life; //������
map<string, int> userList; // Map �ڷ��� ���

/**
* ����ü�� �������� ������ ����ü
*/
struct MOVEOBJECT {
	int x		// x ��ǥ
		, y		// y ��ǥ
		, wait; // ���ð�
};
/**
 * ����� �������� ������ ����ü
 */
struct USER {
	int x		// x ��ǥ
		, y;	// y ��ǥ
};

// ȭ���� Ư�� ��ġ�� �̵��� �ִ� �Լ�.
void gotoxy(double x, int y) {
	COORD Pos;
	Pos.X = (short) x;
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

// ���� ������
int setColor(const int n) {
	if (n >= 0 && n <= 255) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
		return 0;
	}
	else {
		return 1;
	}
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
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 02	|	DongGeun	|	�ű�		|
* @Description
*		���ӽ���ȭ��
*/
void opening() { //�ε�ȭ��
	gotoxy(40, 10); printf("������������\n");
	gotoxy(40, 11); printf("������������\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("������������\n");
	gotoxy(40, 11); printf("������������\n");
	gotoxy(40, 12); printf("���\n");
	gotoxy(40, 13); printf("���\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("������������\n");
	gotoxy(40, 11); printf("������������\n");
	gotoxy(40, 12); printf("���\n");
	gotoxy(40, 13); printf("���\n");
	gotoxy(40, 14); printf("����������\n");
	gotoxy(40, 15); printf("����������\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("������������\n");
	gotoxy(40, 11); printf("������������\n");
	gotoxy(40, 12); printf("���\n");
	gotoxy(40, 13); printf("���\n");
	gotoxy(40, 14); printf("����������\n");
	gotoxy(40, 15); printf("����������\n");
	gotoxy(40, 16); printf("���\n");
	gotoxy(40, 17); printf("���\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("������������\n");
	gotoxy(40, 11); printf("������������\n");
	gotoxy(40, 12); printf("���\n");
	gotoxy(40, 13); printf("���\n");
	gotoxy(40, 14); printf("����������\n");
	gotoxy(40, 15); printf("����������\n");
	gotoxy(40, 16); printf("���\n");
	gotoxy(40, 17); printf("���\n");
	gotoxy(40, 18); printf("���\n");
	gotoxy(40, 19); printf("���\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("������������\n");
	gotoxy(40, 11); printf("������������\n");
	gotoxy(40, 12); printf("���\n");
	gotoxy(40, 13); printf("���\n");
	gotoxy(40, 14); printf("����������\n");
	gotoxy(40, 15); printf("����������\n");
	gotoxy(40, 16); printf("���\n");
	gotoxy(40, 17); printf("���\n");
	gotoxy(40, 18); printf("���\n");
	gotoxy(40, 19); printf("���\n");
	gotoxy(40, 20); printf("���\n");
	gotoxy(40, 21); printf("���\n");
	Sleep(300);
	system("cls");
	gotoxy(38, 10); printf("������������\n");
	gotoxy(38, 11); printf("������������\n");
	gotoxy(38, 12); printf("���\n");
	gotoxy(38, 13); printf("���\n");
	gotoxy(38, 14); printf("����������\n");
	gotoxy(38, 15); printf("����������\n");
	gotoxy(38, 16); printf("���\n");
	gotoxy(38, 17); printf("���\n");
	gotoxy(38, 18); printf("���\n");
	gotoxy(38, 19); printf("���\n");
	Sleep(300);
	system("cls");
	gotoxy(35, 10); printf("����������\n");
	gotoxy(35, 11); printf("����������\n");
	gotoxy(35, 12); printf("���\n");
	gotoxy(35, 13); printf("���\n");
	gotoxy(35, 14); printf("��������\n");
	gotoxy(35, 15); printf("��������\n");
	gotoxy(35, 16); printf("���\n");
	gotoxy(35, 17); printf("���\n");
	Sleep(300);
	system("cls");
	gotoxy(32, 11); printf("����������\n");
	gotoxy(32, 12); printf("��\n");
	gotoxy(32, 13); printf("��\n");
	gotoxy(32, 14); printf("��������\n");
	gotoxy(32, 15); printf("��\n");
	gotoxy(32, 16); printf("��\n");
	Sleep(300);
	system("cls");
	gotoxy(30, 11); printf("��������\n");
	gotoxy(30, 12); printf("��\n");
	gotoxy(30, 13); printf("��\n");
	gotoxy(30, 14); printf("������\n");
	gotoxy(30, 15); printf("��\n");
	gotoxy(30, 16); printf("��\n");
	Sleep(300);
	system("cls");
	gotoxy(28, 11); printf("������\n");
	gotoxy(28, 12); printf("��\n");
	gotoxy(28, 13); printf("��\n");
	gotoxy(28, 14); printf("�����\n");
	gotoxy(28, 15); printf("��\n");
	gotoxy(28, 16); printf("��\n");
	Sleep(300);
	system("cls");
	gotoxy(26, 11); printf("������\n");
	gotoxy(26, 12); printf("��\n");
	gotoxy(26, 13); printf("��\n");
	gotoxy(26, 14); printf("�����\n");
	gotoxy(26, 15); printf("��\n");
	gotoxy(26, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 12); printf("  |    |  |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); gotoxy(36, 16); printf("        |\n");
	Sleep(700);
	system("cls");
	gotoxy(24, 11); printf("������\n");
	gotoxy(24, 12); printf("��\n");
	gotoxy(24, 13); printf("��\n");
	gotoxy(24, 14); printf("�����\n");
	gotoxy(24, 15); printf("��\n");
	gotoxy(24, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 12); printf("  |    |  |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(34, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 21); printf("    ------\n");
	Sleep(700);
	system("cls");
	gotoxy(22, 11); printf("������\n");
	gotoxy(22, 12); printf("��\n");
	gotoxy(22, 13); printf("��\n");
	gotoxy(22, 14); printf("�����\n");
	gotoxy(22, 15); printf("��\n");
	gotoxy(22, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 12); printf("  |    |  |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(32, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(51, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(52, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(52, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(52, 12); printf(" ------  |\n");
	Sleep(700);
	system("cls");
	gotoxy(20, 11); printf("������\n");
	gotoxy(20, 12); printf("��\n");
	gotoxy(20, 13); printf("��\n");
	gotoxy(20, 14); printf("�����\n");
	gotoxy(20, 15); printf("��\n");
	gotoxy(20, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(30, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(49, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(50, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(50, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(50, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); gotoxy(59, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); gotoxy(59, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); gotoxy(59, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); gotoxy(59, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); gotoxy(59, 17); printf("   ---    |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); gotoxy(67, 13); printf("    /     |\n");
	Sleep(700);
	system("cls");
	gotoxy(18, 11); printf("������\n");
	gotoxy(18, 12); printf("��\n");
	gotoxy(18, 13); printf("��\n");
	gotoxy(18, 14); printf("�����\n");
	gotoxy(18, 15); printf("��\n");
	gotoxy(18, 16); printf("��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 9); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 10); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 11); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 12); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 13); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 14); printf("  ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 15); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(28, 16); printf("        |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 13); printf("  ------   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 14); printf("      /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 15); printf("     /   --|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /��    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ��  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 21); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(47, 9); printf("  ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 10); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 11); printf("  |  |   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(48, 12); printf(" ------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 13); printf("  -----\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 14); printf(" -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 15); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 16); printf("  |   |   |--\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(57, 17); printf("   ---    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(66, 9); printf("  -------  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 10); printf("       /  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 11); printf("      /   |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 12); printf("     /    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(67, 13); printf("    /     |\n");
	Sleep(2000);
	system("cls");





}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 03	|	DongGeun	|	�ű�(1����)	|
*		|	2017. 06. 07	|	SeokRae		|	2 ~ 4����	|
* @Description
*		���ӷε�ȭ��
*/
void loading(int stage) {

	switch (stage) {

	case 2:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�������    �����            ���������  �������  �����\n");
		gotoxy(11, 22); printf("������      ����������  ��������  ��  ������  �����\n");
		gotoxy(11, 23); printf("�������    ����������  �������    ��    �����  �����\n");
		gotoxy(11, 24); printf("�������    ������  ��  ��������    ����    ����  �����\n");
		gotoxy(11, 25); printf("�������    ������  ��  ��������    ����    ����  �����\n");
		gotoxy(11, 26); printf("�������    ����                  ��������������  �����\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����    �����            ���������  �������  �������\n");
		gotoxy(11, 22); printf("����      ����������  ��������  ��  ������  �������\n");
		gotoxy(11, 23); printf("�����    ����������  �������    ��    �����  �������\n");
		gotoxy(11, 24); printf("�����    ������  ��  ��������    ����    ����  �������\n");
		gotoxy(11, 25); printf("�����    ������  ��  ��������    ����    ����  �������\n");
		gotoxy(11, 26); printf("�����    ����                  ��������������  �������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("��    �����            ���������  �������  ����������\n");
		gotoxy(11, 22); printf("      ����������  ��������  ��  ������  ����������\n");
		gotoxy(11, 23); printf("��    ����������  �������    ��    �����  ����������\n");
		gotoxy(11, 24); printf("��    ������  ��  ��������    ����    ����  ����������\n");
		gotoxy(11, 25); printf("��    ������  ��  ��������    ����    ����  ����������\n");
		gotoxy(11, 26); printf("��    ����                  ��������������  ����������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����            ���������  �������  �������������\n");
		gotoxy(11, 22); printf("����������  ��������  ��  ������  �������������\n");
		gotoxy(11, 23); printf("����������  �������    ��    �����  �������������\n");
		gotoxy(11, 24); printf("������  ��  ��������    ����    ����  �������������\n");
		gotoxy(11, 25); printf("������  ��  ��������    ����    ����  �������������\n");
		gotoxy(11, 26); printf("����                  ��������������  �������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("��            ���������  �������  ����������������\n");
		gotoxy(11, 22); printf("�������  ��������  ��  ������  ����������������\n");
		gotoxy(11, 23); printf("�������  �������    ��    �����  ����������������\n");
		gotoxy(11, 24); printf("���  ��  ��������    ����    ����  ����������������\n");
		gotoxy(11, 25); printf("���  ��  ��������    ����    ����  ����������������\n");
		gotoxy(11, 26); printf("                  ��������������  ����������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("        ���������  �������  �������������������\n");
		gotoxy(11, 22); printf("����  ��������  ��  ������  �������������������\n");
		gotoxy(11, 23); printf("����  �������    ��    �����  �������������������\n");
		gotoxy(11, 24); printf("��  ��������    ����    ����  �������������������\n");
		gotoxy(11, 25); printf("��  ��������    ����    ����  �������������������\n");
		gotoxy(11, 26); printf("            ��������������  �������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("  ���������  �������  ����������������������\n");
		gotoxy(11, 22); printf("  ��������  ��  ������  ����������������������\n");
		gotoxy(11, 23); printf("  �������    ��    �����  ����������������������\n");
		gotoxy(11, 24); printf("�������    ����    ����  ����������������������\n");
		gotoxy(11, 25); printf("�������    ����    ����  ����������������������\n");
		gotoxy(11, 26); printf("      ��������������  ����������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�������  �������  �������������������������\n");
		gotoxy(11, 22); printf("������  ��  ������  �������������������������\n");
		gotoxy(11, 23); printf("�����    ��    �����  �������������������������\n");
		gotoxy(11, 24); printf("����    ����    ����  �������������������������\n");
		gotoxy(11, 25); printf("����    ����    ����  �������������������������\n");
		gotoxy(11, 26); printf("��������������  �������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���  �������  �����������������������������\n");
		gotoxy(11, 22); printf("��  ��  ������  �����������������������������\n");
		gotoxy(11, 23); printf("    ��    �����  �����������������������������\n");
		gotoxy(11, 24); printf("  ����    ����  �����������������������������\n");
		gotoxy(11, 25); printf("  ����    ����  �����������������������������\n");
		gotoxy(11, 26); printf("����������  �����������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("������  ���������������������������������\n");
		gotoxy(11, 22); printf("������  ���������������������������������\n");
		gotoxy(11, 23); printf("  �����  ���������������������������������\n");
		gotoxy(11, 24); printf("    ����  ���������������������������������\n");
		gotoxy(11, 25); printf("    ����  ���������������������������������\n");
		gotoxy(11, 26); printf("������  ���������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���  ������������������������������������\n");
		gotoxy(11, 22); printf("���  ������������������������������������\n");
		gotoxy(11, 23); printf("���  ������������������������������������\n");
		gotoxy(11, 24); printf("���  ������������������������������������\n");
		gotoxy(11, 25); printf("���  ������������������������������������\n");
		gotoxy(11, 26); printf("���  ������������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("���������������������������������������\n");
		gotoxy(11, 26); printf("���������������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("���������������������������������������\n");
		gotoxy(11, 26); printf("���������������������������������������\n");
		gotoxy(11, 27); printf("�����          �����            ���������  �������  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 26); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 27); printf("�����          ����������  �������    ��    �����  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 24); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 25); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 26); printf("�����  ����������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 27); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 23); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 24); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 25); printf("�����  ����������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 27); printf("�������������                  ������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 22); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 23); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 24); printf("�����  ����������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 25); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�������������                  ������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		break;

	case 3:
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 22); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 23); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 24); printf("�����  ����������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 25); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�������������                  ������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���          �����            ���������  �������  ������\n");
		gotoxy(11, 22); printf("�������  ����������  ��������  ��  ������  ������\n");
		gotoxy(11, 23); printf("���          ����������  �������    ��    �����  ������\n");
		gotoxy(11, 24); printf("���  ����������  ��  ��������    ����    ����  ������\n");
		gotoxy(11, 25); printf("���          ������  ��  ��������    ����    ����  ������\n");
		gotoxy(11, 26); printf("�����������                  ��������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("          �����            ���������  �������  ��������\n");
		gotoxy(11, 22); printf("�����  ����������  ��������  ��  ������  ��������\n");
		gotoxy(11, 23); printf("          ����������  �������    ��    �����  ��������\n");
		gotoxy(11, 24); printf("  ����������  ��  ��������    ����    ����  ��������\n");
		gotoxy(11, 25); printf("          ������  ��  ��������    ����    ����  ��������\n");
		gotoxy(11, 26); printf("���������                  ����������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����            ���������  �������  �������������\n");
		gotoxy(11, 22); printf("����������  ��������  ��  ������  �������������\n");
		gotoxy(11, 23); printf("����������  �������    ��    �����  �������������\n");
		gotoxy(11, 24); printf("������  ��  ��������    ����    ����  �������������\n");
		gotoxy(11, 25); printf("������  ��  ��������    ����    ����  �������������\n");
		gotoxy(11, 26); printf("����                  ��������������  �������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("��            ���������  �������  ����������������\n");
		gotoxy(11, 22); printf("�������  ��������  ��  ������  ����������������\n");
		gotoxy(11, 23); printf("�������  �������    ��    �����  ����������������\n");
		gotoxy(11, 24); printf("���  ��  ��������    ����    ����  ����������������\n");
		gotoxy(11, 25); printf("���  ��  ��������    ����    ����  ����������������\n");
		gotoxy(11, 26); printf("                  ��������������  ����������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("        ���������  �������  �������������������\n");
		gotoxy(11, 22); printf("����  ��������  ��  ������  �������������������\n");
		gotoxy(11, 23); printf("����  �������    ��    �����  �������������������\n");
		gotoxy(11, 24); printf("��  ��������    ����    ����  �������������������\n");
		gotoxy(11, 25); printf("��  ��������    ����    ����  �������������������\n");
		gotoxy(11, 26); printf("            ��������������  �������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("  ���������  �������  ����������������������\n");
		gotoxy(11, 22); printf("  ��������  ��  ������  ����������������������\n");
		gotoxy(11, 23); printf("  �������    ��    �����  ����������������������\n");
		gotoxy(11, 24); printf("�������    ����    ����  ����������������������\n");
		gotoxy(11, 25); printf("�������    ����    ����  ����������������������\n");
		gotoxy(11, 26); printf("      ��������������  ����������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�������  �������  �������������������������\n");
		gotoxy(11, 22); printf("������  ��  ������  �������������������������\n");
		gotoxy(11, 23); printf("�����    ��    �����  �������������������������\n");
		gotoxy(11, 24); printf("����    ����    ����  �������������������������\n");
		gotoxy(11, 25); printf("����    ����    ����  �������������������������\n");
		gotoxy(11, 26); printf("��������������  �������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���  �������  �����������������������������\n");
		gotoxy(11, 22); printf("��  ��  ������  �����������������������������\n");
		gotoxy(11, 23); printf("    ��    �����  �����������������������������\n");
		gotoxy(11, 24); printf("  ����    ����  �����������������������������\n");
		gotoxy(11, 25); printf("  ����    ����  �����������������������������\n");
		gotoxy(11, 26); printf("����������  �����������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("������  ���������������������������������\n");
		gotoxy(11, 22); printf("������  ���������������������������������\n");
		gotoxy(11, 23); printf("  �����  ���������������������������������\n");
		gotoxy(11, 24); printf("    ����  ���������������������������������\n");
		gotoxy(11, 25); printf("    ����  ���������������������������������\n");
		gotoxy(11, 26); printf("������  ���������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���  ������������������������������������\n");
		gotoxy(11, 22); printf("���  ������������������������������������\n");
		gotoxy(11, 23); printf("���  ������������������������������������\n");
		gotoxy(11, 24); printf("���  ������������������������������������\n");
		gotoxy(11, 25); printf("���  ������������������������������������\n");
		gotoxy(11, 26); printf("���  ������������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("���������������������������������������\n");
		gotoxy(11, 26); printf("���������������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("���������������������������������������\n");
		gotoxy(11, 26); printf("���������������������������������������\n");
		gotoxy(11, 27); printf("�����          �����            ���������  �������  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 26); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 27); printf("�����          ����������  �������    ��    �����  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 24); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 25); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 26); printf("���������  ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 27); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 23); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 24); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 25); printf("���������  ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 27); printf("�������������                  ������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 22); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 23); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 24); printf("���������  ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 25); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�������������                  ������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		break;
	case 4:
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����          �����            ���������  �������  ����\n");
		gotoxy(11, 22); printf("���������  ����������  ��������  ��  ������  ����\n");
		gotoxy(11, 23); printf("�����          ����������  �������    ��    �����  ����\n");
		gotoxy(11, 24); printf("���������  ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 25); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�������������                  ������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���          �����            ���������  �������  ������\n");
		gotoxy(11, 22); printf("�������  ����������  ��������  ��  ������  ������\n");
		gotoxy(11, 23); printf("���          ����������  �������    ��    �����  ������\n");
		gotoxy(11, 24); printf("�������  ������  ��  ��������    ����    ����  ������\n");
		gotoxy(11, 25); printf("���          ������  ��  ��������    ����    ����  ������\n");
		gotoxy(11, 26); printf("�����������                  ��������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("          �����            ���������  �������  ��������\n");
		gotoxy(11, 22); printf("�����  ����������  ��������  ��  ������  ��������\n");
		gotoxy(11, 23); printf("          ����������  �������    ��    �����  ��������\n");
		gotoxy(11, 24); printf("�����  ������  ��  ��������    ����    ����  ��������\n");
		gotoxy(11, 25); printf("          ������  ��  ��������    ����    ����  ��������\n");
		gotoxy(11, 26); printf("���������                  ����������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����            ���������  �������  �������������\n");
		gotoxy(11, 22); printf("����������  ��������  ��  ������  �������������\n");
		gotoxy(11, 23); printf("����������  �������    ��    �����  �������������\n");
		gotoxy(11, 24); printf("������  ��  ��������    ����    ����  �������������\n");
		gotoxy(11, 25); printf("������  ��  ��������    ����    ����  �������������\n");
		gotoxy(11, 26); printf("����                  ��������������  �������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("��            ���������  �������  ����������������\n");
		gotoxy(11, 22); printf("�������  ��������  ��  ������  ����������������\n");
		gotoxy(11, 23); printf("�������  �������    ��    �����  ����������������\n");
		gotoxy(11, 24); printf("���  ��  ��������    ����    ����  ����������������\n");
		gotoxy(11, 25); printf("���  ��  ��������    ����    ����  ����������������\n");
		gotoxy(11, 26); printf("                  ��������������  ����������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("        ���������  �������  �������������������\n");
		gotoxy(11, 22); printf("����  ��������  ��  ������  �������������������\n");
		gotoxy(11, 23); printf("����  �������    ��    �����  �������������������\n");
		gotoxy(11, 24); printf("��  ��������    ����    ����  �������������������\n");
		gotoxy(11, 25); printf("��  ��������    ����    ����  �������������������\n");
		gotoxy(11, 26); printf("            ��������������  �������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("  ���������  �������  ����������������������\n");
		gotoxy(11, 22); printf("  ��������  ��  ������  ����������������������\n");
		gotoxy(11, 23); printf("  �������    ��    �����  ����������������������\n");
		gotoxy(11, 24); printf("�������    ����    ����  ����������������������\n");
		gotoxy(11, 25); printf("�������    ����    ����  ����������������������\n");
		gotoxy(11, 26); printf("      ��������������  ����������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�������  �������  �������������������������\n");
		gotoxy(11, 22); printf("������  ��  ������  �������������������������\n");
		gotoxy(11, 23); printf("�����    ��    �����  �������������������������\n");
		gotoxy(11, 24); printf("����    ����    ����  �������������������������\n");
		gotoxy(11, 25); printf("����    ����    ����  �������������������������\n");
		gotoxy(11, 26); printf("��������������  �������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���  �������  �����������������������������\n");
		gotoxy(11, 22); printf("��  ��  ������  �����������������������������\n");
		gotoxy(11, 23); printf("    ��    �����  �����������������������������\n");
		gotoxy(11, 24); printf("  ����    ����  �����������������������������\n");
		gotoxy(11, 25); printf("  ����    ����  �����������������������������\n");
		gotoxy(11, 26); printf("����������  �����������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("������  ���������������������������������\n");
		gotoxy(11, 22); printf("������  ���������������������������������\n");
		gotoxy(11, 23); printf("  �����  ���������������������������������\n");
		gotoxy(11, 24); printf("    ����  ���������������������������������\n");
		gotoxy(11, 25); printf("    ����  ���������������������������������\n");
		gotoxy(11, 26); printf("������  ���������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���  ������������������������������������\n");
		gotoxy(11, 22); printf("���  ������������������������������������\n");
		gotoxy(11, 23); printf("���  ������������������������������������\n");
		gotoxy(11, 24); printf("���  ������������������������������������\n");
		gotoxy(11, 25); printf("���  ������������������������������������\n");
		gotoxy(11, 26); printf("���  ������������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("���������������������������������������\n");
		gotoxy(11, 26); printf("���������������������������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		Sleep(150);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("���������������������������������������\n");
		gotoxy(11, 26); printf("���������������������������������������\n");
		gotoxy(11, 27); printf("�����  ���������            ���������  �������  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("���������������������������������������\n");
		gotoxy(11, 24); printf("���������������������������������������\n");
		gotoxy(11, 25); printf("�����  ���������            ���������  �������  ����\n");
		gotoxy(11, 26); printf("�����  ��������������  ��������  ��  ������  ����\n");
		gotoxy(11, 27); printf("�����  ��������������  �������    ��    �����  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("���������������������������������������\n");
		gotoxy(11, 23); printf("�����  ���������            ���������  �������  ����\n");
		gotoxy(11, 24); printf("�����  ��  ������������  ��������  ��  ������  ����\n");
		gotoxy(11, 25); printf("�����  ��  ������������  �������    ��    �����  ����\n");
		gotoxy(11, 26); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 27); printf("�������  ��������  ��  ��������    ����    ����  ����\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("���������������������������������������\n");
		gotoxy(11, 22); printf("�����  ���������            ���������  �������  ����\n");
		gotoxy(11, 23); printf("�����  ��  ������������  ��������  ��  ������  ����\n");
		gotoxy(11, 24); printf("�����  ��  ������������  �������    ��    �����  ����\n");
		gotoxy(11, 25); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�������  ��������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 27); printf("�������  ������                  ������������������\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("���������������������������������������\n");
		gotoxy(11, 21); printf("�����  ���������            ���������  �������  ����\n");
		gotoxy(11, 22); printf("�����  ��  ������������  ��������  ��  ������  ����\n");
		gotoxy(11, 23); printf("�����  ��  ������������  �������    ��    �����  ����\n");
		gotoxy(11, 24); printf("�����          ������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 25); printf("�������  ��������  ��  ��������    ����    ����  ����\n");
		gotoxy(11, 26); printf("�������  ������                  ������������������\n");
		gotoxy(11, 27); printf("���������������������������������������\n");
		break;
	default :
		break;
	}
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 01	|	SeokRae		|	�ű�		|
*		|	2017. 06. 07	|	SeokRae		|	Ÿ��Ʋ �ֱ�	|
* @Description
*		���� ���� �޴�
*/
void mainMenu() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(MAP_X / 2.7, 10);
	gotoxy(12, 1); printf("��������    ��������������������������    ���\n");
	gotoxy(12, 2); printf("�������    ��  ������������    �����������    ��  ��\n");
	gotoxy(12, 3); printf("������    ���    ����������    ��  ���������    ���    \n");
	gotoxy(12, 4); printf("���������  ���  ��������    ���    �����������  ���\n");
	gotoxy(12, 5); printf("�������������  ����������  ���  �������������\n");
	gotoxy(12, 6); printf("  ��������������������������  ������������\n");
	gotoxy(12, 7); printf("��  ������������������    ������������������\n");
	gotoxy(12, 8); printf("���  ����������������    ��  �����������    �����\n");
	gotoxy(12, 9); printf("��������    ���������    ���    ���������    ��  ����\n");
	gotoxy(12, 10); printf("������    ��  ������������  ��  ��������    ���    ���\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(MAP_X / 2.6, 20);
	cout << " 1. �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(MAP_X / 2.6, 22);
	cout << " 2. �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(MAP_X / 2.6, 24);
	cout << " 3. �� �� �� �� " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(MAP_X / 2.6, 26);
	cout << " 4. �� �� �� �� " << "\n";
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 08	|	SeokRae		|	��ŷ ǥ��	|
* @Description
*		map�ڷᱸ���� ����� ���� ����Ʈ�� �ִ� 10�� ����Ѵ�.
*/
void rankList() {
	system("cls");
	gotoxy(MAP_X / 2.2, 10);
	cout << "��ŷ ����";
	gotoxy(MAP_X / 2.5, 11);
	cout << " �� �� " << " :: " << "���̵�" << " :: " << "�� ��";
	map<string, int>::iterator i; // ����� ���ؼ� iterator ����
	int index = 0; 
	for (i = userList.begin(); i != userList.end(); i++) {
		gotoxy(MAP_X / 2.5, (12 + index));
		cout << i->first << "	 ::		" << i->second << '\n';
		index++;
	}
	
	system("pause");
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 07	|	SeokRae		|	�ű�		|
* @Description
*		���ھ ���� ���� ��� �Լ�
*/
void result(int *stage, int *life, int *score) {
	system("cls");
	gotoxy(MAP_X / 2.7, MAP_Y /2);
	switch (*stage) {
	case 1: // �������� 1���� �׾��� ��� F �������� ��������
		cout << "������Դϴ�." << "\n";
		break;
	case 2: // �������� 2���� �׾��� ��� C �������� ��������
		switch (*life) {
		case 3:
			cout << "C+" << "\n";
			break;
		case 2:
			cout << "C" << "\n";
			break;
		case 1:
			cout << "C-" << "\n";
			break;
		}
		break;
	case 3: // �������� 1���� �׾��� ��� B �������� ��������
		switch (*life) {
		case 3:
			cout << "B+" << "\n";
			break;
		case 2:
			cout << "B" << "\n";
			break;
		case 1:
			cout << "B-" << "\n";
			break;
		}
	case 4: // �������� 1���� �׾��� ��� A �������� ��������
		switch (*life) {
		case 3:
			cout << "A+" << "\n";
			break;
		case 2:
			cout << "A" << "\n";
			break;
		case 1:
			cout << "A-" << "\n";
			break;
		}
		break;
	}
	Sleep(300);
	rankList();
}


/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 07	|	SeokRae		|	���̵� ��� |
* @Description
*		���ھ ���� ���� ��� �Լ�
*/
void login() {
	string name;
	string pwd;

	bool flag = true;

	
	while (flag) {
		gotoxy(28, 12); printf("**************************************************");
		gotoxy(28, 13); cout << "���� : " << life << " " << stage << " ��������   ";
		gotoxy(28, 14);	cout << "���� : " << score << "���� ȹ���ϼ̽��ϴ�.       ";
		gotoxy(28, 15);	cout << "����Ͻ� ���̵� �Է� �� �ּ���.                ";
		// ���̵� �Է�
		gotoxy(40, 16); getline(cin, name); 
		gotoxy(28, 17); printf("**************************************************");
		// insert() �Լ��� ���ϰ��� 
		// pair<iterator it, bool bState> �ε�, it�� �߰��� �׸��� ����Ű�� iterator�̰�
		// bool�� ���� �׸� �߰��� ���� ���������� ��Ÿ���� ������ false�̸� �߰����� ���ߴٴ� ���� �ǹ�
		// �׷��Ƿ� �Ʒ��� ���� key���� �ߺ����� �ʰ� ���� ���� �� �ִ�.
		pair<string, int> p(name, score); // ��� ����
		if (userList.insert(p).second == false) {
			cout << "�ٸ� ���̵� �Է� �� �ּ���.";
			flag = true;
		} else {
			userList.insert(p); // Map�� ����� �߰�
			flag = false;
		}
	}

	result(&stage, &life, &score);
}

void adminLogin() {
	cout << "������ ������ �Դϴ�." << "\n";

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 01	|	SeokRae		|	�ű�		|
*		|	2017. 06. 05	|	DongGeun	|	������ �߰� |
* @Description
*		���� ����
*/
void description() {

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����		|
*		|	2017. 06. 01	|	SeokRae		|	�ű�			|
*		|	2017. 06. 05	|	DongGeun	|	������ �߰�		|
* @Description
*		���� ���� �Լ�
*/
void game(int *stage) {
	loading(*stage);
	int speed = 75 - *stage * 15; // ���̵� ����

	
	if (*stage == 2) { score = 101; }
	if (*stage == 3) { score = 201; }
	if (*stage == 4) { score = 301; }
	

	MOVEOBJECT mObj[100]; // ����ü�� ����� ����ü

	bool flag = true; // ���� �ݺ����� ���� bool ����

	// [�ʱ�ȭ] ���� ���� ��ġ 
	USER user = { 60, 25 };

	// [�ʱ�ȭ] ����ü F���� ����, ��ǥ, ��� �ð�
	for (int i = 0; i < 100; i++) {
		mObj[i].x = rand() % 100 + 1;	// x��ǥ 1 ~ 100 ���� �������� �����Ѵ�.
		mObj[i].y = 3;					// y��ǥ 2���� ����
		mObj[i].wait = rand() % 20;	// ���� ���ð��� �־� �� �ٷ� �������� �ʰ� �Ѵ�.
	}

	/*
	* ���� ������ �κ�
	*/
	while (flag) {

		Sleep(speed); // Sleep() �Լ��� ���� �ӵ� ����
		system("cls"); // ȭ�� �����
		gotoxy(5, 2);
		cout << "Stage : " << (*stage);
		gotoxy(70, 2);
		cout << "Score : " << score;
		
		switch (life) { //������ ���
		case 3:
			gotoxy(90, 2);
			cout << "�� �� ��";
			break;
		case 2:
			gotoxy(90, 2);
			cout << "�� �� ��";
			break;
		case 1:
			gotoxy(90, 2);
			cout << "�� �� ��";
			break;
		default:
			gotoxy(90, 2);
			cout << "�� �� ��";
			flag = false;
		}
		// �Ͻ����� ��� ���ǹ�
		if (_kbhit()) { // Ű���� ���ȴ��� Ȯ��
			int key = _getch();
			switch (key) {
			case 'c':
				gotoxy(72, 0);
				cout << "PAUSE" << "\n";
				while (1)
				{
					key = _getch();
					if (key == 'c')
						break;
				}
				gotoxy(72, 0);
				cout << "    " << "\n";
				break;
			}
		}


		// ��� ������ ó��
		if (isKeyState(VK_LEFT)) {
			if (user.x > 1) {
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
		setColor(FOREGROUND_INTENSITY);
		cout << "��" << "\n";
		gotoxy(user.x, user.y + 1);
		cout << "��" << "\n";
		gotoxy(user.x, user.y + 2);
		cout << "||" << "\n";
		

		for (int i = 0; i < 100; i++) { // * 50 ����ü ���� ���̵��� ���� �ٲ�� ��
										// ����ü�� �������� �� (��� �ð��� �־� �Ϸķ� �������� �ʰ� �� 
			if (mObj[i].wait > 0) {
				// ��� �ð��� �־� �� �ٷ� ����ü�� �������� �ʵ��� �Ѵ�.
				mObj[i].wait--;
			}
			else {
				// ����ü�� ��ĭ �Ʒ��� �̵��Ѵ�.
				mObj[i].y++;
				// F ������ ���ϴܿ� ���� ���� �� ó��.
				if (mObj[i].y >= 27) {
					mObj[i].x = rand() % 100 + 1;
					mObj[i].y = 5;
					score++;
				}
				// F ���� ���
				gotoxy(mObj[i].x, mObj[i].y);
				if (*stage == 1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << "F";
				}
				if (*stage == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "C";
				}
				if (*stage == 3) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "B";
				}
				if (*stage == 4) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "A";
				}
				// ����ü�� ������� �Ӹ� ������ ���밪�� 2 ���� �۰�, y��ǥ���� ���� ��� �浹
				if (abs(mObj[i].x - user.x) < 2 && (mObj[i].y == user.y)) {
					// ������ ���.
					cout << "\a";
					life--;
					if (life == 0) {
						flag = false;
					}
				}
				// **  �������� �Ѿ�� �ҽ� �ʿ�
				if (score == 100) { (*stage)++; game(stage); }
				if (score == 200) { (*stage)++; game(stage); }
				if (score == 300) { (*stage)++; game(stage); }
			} // if else �� ��
		}// for�� ��
	} // while�� ����
	
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����		|
*		|	2017. 06. 02	|	SeokRae		|	1~3��, F1 �Է�	|
*		|	2017. 06. 08	|	SeokRae		|	4�� �߰�		|
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
	case '4':
		break;
	case 59:
		adminLogin();
		break;
	default:
		return isCheckNum();
	}
	return checkNum;
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 02	|	SeokRae		|	�ű�		|
* @Description
*		���� �޴� ���� �Լ�
*/
void start() {
	while (1) {
		// �ʱ�ȭ
		// ���� �ٽ� �������� �� ó�� ���·� ���ư��� ����
		life = 3;
		stage = 1;
		score = 0;
		// �޴� ���� �ؽ�Ʈ ȣ��
		mainMenu();
		// ���� �Է� ���� �Լ� ȣ��
		// ��� �Լ�
		// 1 ~ 3 �̿ܿ� ���� ���� ��� ��� �Ѵ�.
		char selectNum = isCheckNum(); 

		switch (selectNum) {
		case '1': // 1. ���� ����
			game(&stage);
			login();
			break;
		case '2': // 2. ���� ����
			description(); // ���� ���� �Լ� ȣ��
			break;
		case '3': // 3. ���� ����
			rankList(); // ���� ���� �Լ� ȣ��
			break;
		case '4': // 2. ���� ����
			exit(0); // �ý��� ���� �Լ� ȣ��
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
*		|	2017. 06. 01	|	SeokRae		|	systemSetting(), mainMenu()					|
*		|	2017. 06. 02	|	DongGeun	|	opening(), loading()						|
*		|	2017. 06. 02	|	SeokRae		|	start()										|
* @Description
*		���� �Լ�
*/
void main() {
	systemSetting();

	start(); // �޴� ���� �Լ�
	
}