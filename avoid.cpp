#include <iostream>
#include <Windows.h> // ����
#include <conio.h> // _kbhit(), _getch() �Լ�
#include <stdlib.h> // exit() �Լ��� ���
// #include <time.h>  // Srand((unsigned int)time(NULL)) �ϸ� ����ü�� �̻��ϰ� ������
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#define MAP_X 100
#define MAP_Y 30
#define COUNT 100


using namespace std;

int score;
int stage;
int life; //������
int coin;
map<string, int> userList; // Map �ڷ��� ���


template<template <typename> class P = less >
struct compare_pair_second {
	template<class T1, class T2> bool operator()(const pair<T1, T2>&left, const pair<T1, T2>&right) {
		return P<T2>()(left.second, right.second);
	}
};
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
	Pos.X = (short)x;
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
	system("Color 0F");

}

/**
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 02	|	DongGeun	|	�ű�		|
*		|	2017. 06. 08	|	DongGeun	|	������ ����	|
* @Description
*		���ӽ���ȭ��
*/
void opening() { //�ε�ȭ��
	setColor(11); gotoxy(40, 10); printf("������������\n");
	setColor(11); gotoxy(40, 11); printf("������������\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("������������\n");
	setColor(11); gotoxy(40, 11); printf("������������\n");
	gotoxy(40, 12); printf("���\n");
	gotoxy(40, 13); printf("���\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("������������\n");
	setColor(11); gotoxy(40, 11); printf("������������\n");
	setColor(11); gotoxy(40, 12); printf("���\n");
	setColor(11); gotoxy(40, 13); printf("���\n");
	setColor(11); gotoxy(40, 14); printf("����������\n");
	setColor(11); gotoxy(40, 15); printf("����������\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("������������\n");
	setColor(11); gotoxy(40, 11); printf("������������\n");
	setColor(11); gotoxy(40, 12); printf("���\n");
	setColor(11); gotoxy(40, 13); printf("���\n");
	setColor(11); gotoxy(40, 14); printf("����������\n");
	setColor(11); gotoxy(40, 15); printf("����������\n");
	setColor(11); gotoxy(40, 16); printf("���\n");
	setColor(11); gotoxy(40, 17); printf("���\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("������������\n");
	setColor(11); gotoxy(40, 11); printf("������������\n");
	setColor(11); gotoxy(40, 12); printf("���\n");
	setColor(11); gotoxy(40, 13); printf("���\n");
	setColor(11); gotoxy(40, 14); printf("����������\n");
	setColor(11); gotoxy(40, 15); printf("����������\n");
	setColor(11); gotoxy(40, 16); printf("���\n");
	setColor(11); gotoxy(40, 17); printf("���\n");
	setColor(11); gotoxy(40, 18); printf("���\n");
	setColor(11); gotoxy(40, 19); printf("���\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("������������\n");
	setColor(11); gotoxy(40, 11); printf("������������\n");
	setColor(11); gotoxy(40, 12); printf("���\n");
	setColor(11); gotoxy(40, 13); printf("���\n");
	setColor(11); gotoxy(40, 14); printf("����������\n");
	setColor(11); gotoxy(40, 15); printf("����������\n");
	setColor(11); gotoxy(40, 16); printf("���\n");
	setColor(11); gotoxy(40, 17); printf("���\n");
	setColor(11); gotoxy(40, 18); printf("���\n");
	setColor(11); gotoxy(40, 19); printf("���\n");
	setColor(11); gotoxy(40, 20); printf("���\n");
	setColor(11); gotoxy(40, 21); printf("���\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(38, 10); printf("������������\n");
	setColor(11); gotoxy(38, 11); printf("������������\n");
	setColor(11); gotoxy(38, 12); printf("���\n");
	setColor(11); gotoxy(38, 13); printf("���\n");
	setColor(11); gotoxy(38, 14); printf("����������\n");
	setColor(11); gotoxy(38, 15); printf("����������\n");
	setColor(11); gotoxy(38, 16); printf("���\n");
	setColor(11); gotoxy(38, 17); printf("���\n");
	setColor(11); gotoxy(38, 18); printf("���\n");
	setColor(11); gotoxy(38, 19); printf("���\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(35, 10); printf("����������\n");
	setColor(11); gotoxy(35, 11); printf("����������\n");
	setColor(11); gotoxy(35, 12); printf("���\n");
	setColor(11); gotoxy(35, 13); printf("���\n");
	setColor(11); gotoxy(35, 14); printf("��������\n");
	setColor(11); gotoxy(35, 15); printf("��������\n");
	setColor(11); gotoxy(35, 16); printf("���\n");
	setColor(11); gotoxy(35, 17); printf("���\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(32, 11); printf("����������\n");
	setColor(11); gotoxy(32, 12); printf("��\n");
	setColor(11); gotoxy(32, 13); printf("��\n");
	setColor(11); gotoxy(32, 14); printf("��������\n");
	setColor(11); gotoxy(32, 15); printf("��\n");
	setColor(11); gotoxy(32, 16); printf("��\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(30, 11); printf("��������\n");
	setColor(11); gotoxy(30, 12); printf("��\n");
	setColor(11); gotoxy(30, 13); printf("��\n");
	setColor(11); gotoxy(30, 14); printf("������\n");
	setColor(11); gotoxy(30, 15); printf("��\n");
	setColor(11); gotoxy(30, 16); printf("��\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(28, 11); printf("������\n");
	setColor(11); gotoxy(28, 12); printf("��\n");
	setColor(11); gotoxy(28, 13); printf("��\n");
	setColor(11); gotoxy(28, 14); printf("�����\n");
	setColor(11); gotoxy(28, 15); printf("��\n");
	setColor(11); gotoxy(28, 16); printf("��\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(26, 11); printf("������\n");
	setColor(11); gotoxy(26, 12); printf("��\n");
	setColor(11); gotoxy(26, 13); printf("��\n");
	setColor(11); gotoxy(26, 14); printf("�����\n");
	setColor(11); gotoxy(26, 15); printf("��\n");
	setColor(11); gotoxy(26, 16); printf("��\n");
	setColor(1); gotoxy(36, 9);  printf("  ����\n");
	setColor(1); gotoxy(36, 10); printf(" �����  ��\n");
	setColor(1); gotoxy(36, 11); printf("   ���    ��\n");
	setColor(1); gotoxy(36, 12); printf("  ��  ��   ����\n");
	setColor(1); gotoxy(36, 13); printf("   ���    ��\n");
	setColor(1); gotoxy(36, 14); printf("           ��\n");
	setColor(1); gotoxy(36, 15); printf("    �����\n");
	setColor(1); gotoxy(36, 16); printf("          ��\n");
	setColor(1); gotoxy(36, 17); printf("          ��\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(24, 11); printf("������\n");
	setColor(11); gotoxy(24, 12); printf("��\n");
	setColor(11); gotoxy(24, 13); printf("��\n");
	setColor(11); gotoxy(24, 14); printf("�����\n");
	setColor(11); gotoxy(24, 15); printf("��\n");
	setColor(11); gotoxy(24, 16); printf("��\n");
	setColor(9); gotoxy(34, 9);  printf("  ����\n");
	setColor(9); gotoxy(34, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(34, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(34, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(34, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(34, 14); printf("           ��\n");
	setColor(9); gotoxy(34, 15); printf("    �����\n");
	setColor(9); gotoxy(34, 16); printf("          ��\n");
	setColor(9); gotoxy(34, 17); printf("          ��\n");
	setColor(6); gotoxy(47, 14); printf("  �����    ��\n");
	setColor(6); gotoxy(47, 15); printf("       ��     ��\n");
	setColor(6); gotoxy(47, 16); printf("      ��  ����\n");
	setColor(6); gotoxy(47, 17); printf("    ��  ��    ��\n");
	setColor(6); gotoxy(47, 18); printf("  ��     ��   ��\n");
	setColor(6); gotoxy(47, 19); printf("    ������\n");
	setColor(6); gotoxy(47, 20); printf("    ��      ��\n");
	setColor(6); gotoxy(47, 21); printf("    ��      ��\n");
	setColor(6); gotoxy(47, 22); printf("    ������\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(22, 11); printf("������\n");
	setColor(11); gotoxy(22, 12); printf("��\n");
	setColor(11); gotoxy(22, 13); printf("��\n");
	setColor(11); gotoxy(22, 14); printf("�����\n");
	setColor(11); gotoxy(22, 15); printf("��\n");
	setColor(11); gotoxy(22, 16); printf("��\n");
	setColor(9); gotoxy(32, 9);  printf("  ����\n");
	setColor(9); gotoxy(32, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(32, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(32, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(32, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(32, 14); printf("           ��\n");
	setColor(9); gotoxy(32, 15); printf("    �����\n");
	setColor(9); gotoxy(32, 16); printf("          ��\n");
	setColor(9); gotoxy(32, 17); printf("          ��\n");
	setColor(14); gotoxy(45, 14); printf("  �����    ��\n");
	setColor(14); gotoxy(45, 15); printf("       ��     ��\n");
	setColor(14); gotoxy(45, 16); printf("      ��  ����\n");
	setColor(14); gotoxy(45, 17); printf("    ��  ��    ��\n");
	setColor(14); gotoxy(45, 18); printf("  ��     ��   ��\n");
	setColor(14); gotoxy(45, 19); printf("    ������\n");
	setColor(14); gotoxy(45, 20); printf("    ��      ��\n");
	setColor(14); gotoxy(45, 21); printf("    ��      ��\n");
	setColor(14); gotoxy(45, 22); printf("    ������\n");
	setColor(4); gotoxy(55, 8);  printf("             ��\n");
	setColor(4); gotoxy(55, 9);  printf(" ������  ��\n");
	setColor(4); gotoxy(55, 10); printf("   ��  ��    ��\n");
	setColor(4); gotoxy(55, 11); printf("   ��  ��    ��\n");
	setColor(4); gotoxy(55, 12); printf(" ������  ��\n");
	setColor(4); gotoxy(55, 13); printf("             ��\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(20, 11); printf("������\n");
	setColor(11); gotoxy(20, 12); printf("��\n");
	setColor(11); gotoxy(20, 13); printf("��\n");
	setColor(11); gotoxy(20, 14); printf("�����\n");
	setColor(11); gotoxy(20, 15); printf("��\n");
	setColor(11); gotoxy(20, 16); printf("��\n");
	setColor(9); gotoxy(30, 9);  printf("  ����\n");
	setColor(9); gotoxy(30, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(30, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(30, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(30, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(30, 14); printf("           ��\n");
	setColor(9); gotoxy(30, 15); printf("    �����\n");
	setColor(9); gotoxy(30, 16); printf("          ��\n");
	setColor(9); gotoxy(30, 17); printf("          ��\n");
	setColor(14); gotoxy(43, 14); printf("  �����    ��\n");
	setColor(14); gotoxy(43, 15); printf("       ��     ��\n");
	setColor(14); gotoxy(43, 16); printf("      ��  ����\n");
	setColor(14); gotoxy(43, 17); printf("    ��  ��    ��\n");
	setColor(14); gotoxy(43, 18); printf("  ��     ��   ��\n");
	setColor(14); gotoxy(43, 19); printf("    ������\n");
	setColor(14); gotoxy(43, 20); printf("    ��      ��\n");
	setColor(14); gotoxy(43, 21); printf("    ��      ��\n");
	setColor(14); gotoxy(43, 22); printf("    ������\n");
	setColor(12); gotoxy(53, 8);  printf("             ��\n");
	setColor(12); gotoxy(53, 9);  printf(" ������  ��\n");
	setColor(12); gotoxy(53, 10); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(53, 11); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(53, 12); printf(" ������  ��\n");
	setColor(12); gotoxy(53, 13); printf("             ��\n");
	setColor(2); gotoxy(63, 15); printf("  ����   ��\n");
	setColor(2); gotoxy(63, 16); printf(" �����  ��\n");
	setColor(2); gotoxy(63, 17); printf("   ���    ����\n");
	setColor(2); gotoxy(63, 18); printf("  ��  ��   ��\n");
	setColor(2); gotoxy(63, 19); printf("   ���    ��\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("������\n");
	setColor(11); gotoxy(18, 12); printf("��\n");
	setColor(11); gotoxy(18, 13); printf("��\n");
	setColor(11); gotoxy(18, 14); printf("�����\n");
	setColor(11); gotoxy(18, 15); printf("��\n");
	setColor(11); gotoxy(18, 16); printf("��\n");
	setColor(9); gotoxy(28, 9);  printf("  ����\n");
	setColor(9); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 14); printf("           ��\n");
	setColor(9); gotoxy(28, 15); printf("    �����\n");
	setColor(9); gotoxy(28, 16); printf("          ��\n");
	setColor(9); gotoxy(28, 17); printf("          ��\n");
	setColor(14); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(14); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(14); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(14); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(14); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(14); gotoxy(41, 19); printf("    ������\n");
	setColor(14); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 22); printf("    ������\n");
	setColor(12); gotoxy(51, 8);  printf("             ��\n");
	setColor(12); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(12); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(12); gotoxy(51, 13); printf("             ��\n");
	setColor(10); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(10); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(10); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(10); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(10); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(5); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(5); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(5); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(5); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(5); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("������\n");
	setColor(11); gotoxy(18, 12); printf("��\n");
	setColor(11); gotoxy(18, 13); printf("��\n");
	setColor(11); gotoxy(18, 14); printf("�����\n");
	setColor(11); gotoxy(18, 15); printf("��\n");
	setColor(11); gotoxy(18, 16); printf("��\n");
	setColor(9); gotoxy(28, 9);  printf("  ����\n");
	setColor(9); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 14); printf("           ��\n");
	setColor(9); gotoxy(28, 15); printf("    �����\n");
	setColor(9); gotoxy(28, 16); printf("          ��\n");
	setColor(9); gotoxy(28, 17); printf("          ��\n");
	setColor(14); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(14); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(14); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(14); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(14); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(14); gotoxy(41, 19); printf("    ������\n");
	setColor(14); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 22); printf("    ������\n");
	setColor(12); gotoxy(51, 8);  printf("             ��\n");
	setColor(12); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(12); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(12); gotoxy(51, 13); printf("             ��\n");
	setColor(10); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(10); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(10); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(10); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(10); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(13); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(13); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(13); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(13); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(13); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(13); gotoxy(18, 11); printf("������\n");
	setColor(13); gotoxy(18, 12); printf("��\n");
	setColor(13); gotoxy(18, 13); printf("��\n");
	setColor(13); gotoxy(18, 14); printf("�����\n");
	setColor(13); gotoxy(18, 15); printf("��\n");
	setColor(13); gotoxy(18, 16); printf("��\n");
	setColor(11); gotoxy(28, 9);  printf("  ����\n");
	setColor(11); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(11); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(11); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(11); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(11); gotoxy(28, 14); printf("           ��\n");
	setColor(11); gotoxy(28, 15); printf("    �����\n");
	setColor(11); gotoxy(28, 16); printf("          ��\n");
	setColor(11); gotoxy(28, 17); printf("          ��\n");
	setColor(9); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(9); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(9); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(9); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(9); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(9); gotoxy(41, 19); printf("    ������\n");
	setColor(9); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(9); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(9); gotoxy(41, 22); printf("    ������\n");
	setColor(14); gotoxy(51, 8);  printf("             ��\n");
	setColor(14); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(14); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(14); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(14); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(14); gotoxy(51, 13); printf("             ��\n");
	setColor(12); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(12); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(12); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(12); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(12); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(10); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(10); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(10); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(10); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(10); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(10); gotoxy(18, 11); printf("������\n");
	setColor(10); gotoxy(18, 12); printf("��\n");
	setColor(10); gotoxy(18, 13); printf("��\n");
	setColor(10); gotoxy(18, 14); printf("�����\n");
	setColor(10); gotoxy(18, 15); printf("��\n");
	setColor(10); gotoxy(18, 16); printf("��\n");
	setColor(13); gotoxy(28, 9);  printf("  ����\n");
	setColor(13); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(13); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(13); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(13); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(13); gotoxy(28, 14); printf("           ��\n");
	setColor(13); gotoxy(28, 15); printf("    �����\n");
	setColor(13); gotoxy(28, 16); printf("          ��\n");
	setColor(13); gotoxy(28, 17); printf("          ��\n");
	setColor(11); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(11); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(11); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(11); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(11); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(11); gotoxy(41, 19); printf("    ������\n");
	setColor(11); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(11); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(11); gotoxy(41, 22); printf("    ������\n");
	setColor(9); gotoxy(51, 8);  printf("             ��\n");
	setColor(9); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(9); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(9); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(9); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(9); gotoxy(51, 13); printf("             ��\n");
	setColor(14); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(14); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(14); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(14); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(14); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(12); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(12); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(12); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(12); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(12); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(12); gotoxy(18, 11); printf("������\n");
	setColor(12); gotoxy(18, 12); printf("��\n");
	setColor(12); gotoxy(18, 13); printf("��\n");
	setColor(12); gotoxy(18, 14); printf("�����\n");
	setColor(12); gotoxy(18, 15); printf("��\n");
	setColor(12); gotoxy(18, 16); printf("��\n");
	setColor(10); gotoxy(28, 9);  printf("  ����\n");
	setColor(10); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(10); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(10); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(10); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(10); gotoxy(28, 14); printf("           ��\n");
	setColor(10); gotoxy(28, 15); printf("    �����\n");
	setColor(10); gotoxy(28, 16); printf("          ��\n");
	setColor(10); gotoxy(28, 17); printf("          ��\n");
	setColor(13); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(13); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(13); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(13); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(13); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(13); gotoxy(41, 19); printf("    ������\n");
	setColor(13); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(13); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(13); gotoxy(41, 22); printf("    ������\n");
	setColor(11); gotoxy(51, 8);  printf("             ��\n");
	setColor(11); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(11); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(11); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(11); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(11); gotoxy(51, 13); printf("             ��\n");
	setColor(9); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(9); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(9); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(9); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(9); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(14); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(14); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(14); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(14); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(14); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(14); gotoxy(18, 11); printf("������\n");
	setColor(14); gotoxy(18, 12); printf("��\n");
	setColor(14); gotoxy(18, 13); printf("��\n");
	setColor(14); gotoxy(18, 14); printf("�����\n");
	setColor(14); gotoxy(18, 15); printf("��\n");
	setColor(14); gotoxy(18, 16); printf("��\n");
	setColor(12); gotoxy(28, 9);  printf("  ����\n");
	setColor(12); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(12); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(12); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(12); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(12); gotoxy(28, 14); printf("           ��\n");
	setColor(12); gotoxy(28, 15); printf("    �����\n");
	setColor(12); gotoxy(28, 16); printf("          ��\n");
	setColor(12); gotoxy(28, 17); printf("          ��\n");
	setColor(10); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(10); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(10); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(10); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(10); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(10); gotoxy(41, 19); printf("    ������\n");
	setColor(10); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(10); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(10); gotoxy(41, 22); printf("    ������\n");
	setColor(13); gotoxy(51, 8);  printf("             ��\n");
	setColor(13); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(13); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(13); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(13); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(13); gotoxy(51, 13); printf("             ��\n");
	setColor(11); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(11); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(11); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(11); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(11); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(9); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(9); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(9); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(9); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(9); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(9); gotoxy(18, 11); printf("������\n");
	setColor(9); gotoxy(18, 12); printf("��\n");
	setColor(9); gotoxy(18, 13); printf("��\n");
	setColor(9); gotoxy(18, 14); printf("�����\n");
	setColor(9); gotoxy(18, 15); printf("��\n");
	setColor(9); gotoxy(18, 16); printf("��\n");
	setColor(14); gotoxy(28, 9);  printf("  ����\n");
	setColor(14); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(14); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(14); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(14); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(14); gotoxy(28, 14); printf("           ��\n");
	setColor(14); gotoxy(28, 15); printf("    �����\n");
	setColor(14); gotoxy(28, 16); printf("          ��\n");
	setColor(14); gotoxy(28, 17); printf("          ��\n");
	setColor(12); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(12); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(12); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(12); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(12); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(12); gotoxy(41, 19); printf("    ������\n");
	setColor(12); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(12); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(12); gotoxy(41, 22); printf("    ������\n");
	setColor(10); gotoxy(51, 8);  printf("             ��\n");
	setColor(10); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(10); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(10); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(10); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(10); gotoxy(51, 13); printf("             ��\n");
	setColor(13); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(13); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(13); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(13); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(13); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(11); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(11); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(11); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(11); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(11); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("������\n");
	setColor(11); gotoxy(18, 12); printf("��\n");
	setColor(11); gotoxy(18, 13); printf("��\n");
	setColor(11); gotoxy(18, 14); printf("�����\n");
	setColor(11); gotoxy(18, 15); printf("��\n");
	setColor(11); gotoxy(18, 16); printf("��\n");
	setColor(9); gotoxy(28, 9);  printf("  ����\n");
	setColor(9); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 14); printf("           ��\n");
	setColor(9); gotoxy(28, 15); printf("    �����\n");
	setColor(9); gotoxy(28, 16); printf("          ��\n");
	setColor(9); gotoxy(28, 17); printf("          ��\n");
	setColor(14); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(14); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(14); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(14); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(14); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(14); gotoxy(41, 19); printf("    ������\n");
	setColor(14); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 22); printf("    ������\n");
	setColor(12); gotoxy(51, 8);  printf("             ��\n");
	setColor(12); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(12); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(12); gotoxy(51, 13); printf("             ��\n");
	setColor(10); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(10); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(10); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(10); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(10); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(13); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(13); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(13); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(13); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(13); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(3); gotoxy(18, 11); printf("������\n");
	setColor(3); gotoxy(18, 12); printf("��\n");
	setColor(3); gotoxy(18, 13); printf("��\n");
	setColor(3); gotoxy(18, 14); printf("�����\n");
	setColor(3); gotoxy(18, 15); printf("��\n");
	setColor(3); gotoxy(18, 16); printf("��\n");
	setColor(4); gotoxy(28, 9);  printf("  ����\n");
	setColor(4); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(4); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(4); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(4); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(4); gotoxy(28, 14); printf("           ��\n");
	setColor(4); gotoxy(28, 15); printf("    �����\n");
	setColor(4); gotoxy(28, 16); printf("          ��\n");
	setColor(4); gotoxy(28, 17); printf("          ��\n");
	setColor(6); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(6); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(6); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(6); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(6); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(6); gotoxy(41, 19); printf("    ������\n");
	setColor(6); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(6); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(6); gotoxy(41, 22); printf("    ������\n");
	setColor(5); gotoxy(51, 8);  printf("             ��\n");
	setColor(5); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(5); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(5); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(5); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(5); gotoxy(51, 13); printf("             ��\n");
	setColor(2); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(2); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(2); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(2); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(2); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(4); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(4); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(4); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(4); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(4); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("������\n");
	setColor(11); gotoxy(18, 12); printf("��\n");
	setColor(11); gotoxy(18, 13); printf("��\n");
	setColor(11); gotoxy(18, 14); printf("�����\n");
	setColor(11); gotoxy(18, 15); printf("��\n");
	setColor(11); gotoxy(18, 16); printf("��\n");
	setColor(9); gotoxy(28, 9);  printf("  ����\n");
	setColor(9); gotoxy(28, 10); printf(" �����  ��\n");
	setColor(9); gotoxy(28, 11); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 12); printf("  ��  ��   ����\n");
	setColor(9); gotoxy(28, 13); printf("   ���    ��\n");
	setColor(9); gotoxy(28, 14); printf("           ��\n");
	setColor(9); gotoxy(28, 15); printf("    �����\n");
	setColor(9); gotoxy(28, 16); printf("          ��\n");
	setColor(9); gotoxy(28, 17); printf("          ��\n");
	setColor(14); gotoxy(41, 14); printf("  �����    ��\n");
	setColor(14); gotoxy(41, 15); printf("       ��     ��\n");
	setColor(14); gotoxy(41, 16); printf("      ��  ����\n");
	setColor(14); gotoxy(41, 17); printf("    ��  ��    ��\n");
	setColor(14); gotoxy(41, 18); printf("  ��     ��   ��\n");
	setColor(14); gotoxy(41, 19); printf("    ������\n");
	setColor(14); gotoxy(41, 20); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 21); printf("    ��      ��\n");
	setColor(14); gotoxy(41, 22); printf("    ������\n");
	setColor(12); gotoxy(51, 8);  printf("             ��\n");
	setColor(12); gotoxy(51, 9);  printf(" ������  ��\n");
	setColor(12); gotoxy(51, 10); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 11); printf("   ��  ��    ��\n");
	setColor(12); gotoxy(51, 12); printf(" ������  ��\n");
	setColor(12); gotoxy(51, 13); printf("             ��\n");
	setColor(10); gotoxy(61, 15); printf("  ����   ��\n");
	setColor(10); gotoxy(61, 16); printf(" �����  ��\n");
	setColor(10); gotoxy(61, 17); printf("   ���    ����\n");
	setColor(10); gotoxy(61, 18); printf("  ��  ��   ��\n");
	setColor(10); gotoxy(61, 19); printf("   ���    ��\n");
	setColor(13); gotoxy(72, 9);  printf(" �����  ��\n");
	setColor(13); gotoxy(72, 10); printf("      ��   ��\n");
	setColor(13); gotoxy(72, 11); printf("     ��    ��\n");
	setColor(13); gotoxy(72, 12); printf("   ��      ��\n");
	setColor(13); gotoxy(72, 13); printf("  ��       ��\n");
	Sleep(2000);
	system("cls");





}

/**
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
		setColor(12);
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
		setColor(14);
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
		setColor(14);
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
		setColor(9);
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
		setColor(9);
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
		setColor(11);
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
	default:
		break;
	}
}

/**
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
	gotoxy(8, 1);  printf("�������������������������������������������\n");
	gotoxy(8, 2);  printf("�������������������������������������������\n");
	gotoxy(8, 3);  printf("���  ����    ���          ���          ����������      ����������\n");
	gotoxy(8, 4);  printf("���  �������  ����  ���  �������������  ����  �����  ����\n");
	gotoxy(8, 5);  printf("���  �������  ����  ���  �������        ���  ����  �����  ����\n");
	gotoxy(8, 6);  printf("���        ����    ��    ���          ���������   ����   ���  �÷���  ��\n");
	gotoxy(8, 7);  printf("���  �������  �����������  ���        ���  ����  �����  ����\n");
	gotoxy(8, 8);  printf("���  �������  �����������  ���������  ����  �����  ����\n");
	gotoxy(8, 9);  printf("���  �������  �������   �ؾ�   ����������������������\n");
	gotoxy(8, 10); printf("�������������������������������������������\n");
	gotoxy(80, 11); setColor(8);  printf("by. ��������");
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
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 08	|	SeokRae		|	��ŷ ǥ��	|
* @Description
*		map�ڷᱸ���� ����� ���� ����Ʈ�� �ִ� 10�� ����Ѵ�.
*/
void rankList() {
	
	int index = 0;
	
	system("cls");
	gotoxy(MAP_X / 2.4, 10);
	cout << "��ŷ ����";
	gotoxy(MAP_X / 2.6, 11);
	cout << " �� �� " << " :: " << "���̵�" << " :: " << "�� ��";
	
	// ���׸��� pair�� �ϴ� vector�� ����� Map�� ���ۺ��� ������ �ִ´�.
	vector<pair<string, int> > rank(userList.begin(), userList.end());

	// ���� ���̺귯���� ����Ͽ� vector�� ������������ ����
	sort(rank.begin(), rank.end(), compare_pair_second<less>());

	// https://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
	for (int j = rank.size() - 1; j >= 0; j--) {
		gotoxy(MAP_X / 2.2, (12 + index));
		cout << "	" << rank.size() - j << " ::	" << rank[j].first << " ::	" << rank[j].second << '\n';
		index++;
	}
	// ��� ���
	setColor(0);
	system("pause");
}



/**
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 07	|	SeokRae		|	���̵� ��� |
*		|	2017. 06. 09	|	DongGeun		|	���� �׷��� |
* @Description
*		���ھ ���� ���� ��� �Լ�
*/
void login() {

	bool flag = true;

	string name;
	string pwd;

	while (flag) {
		bool next = false;
		while (!next) {
			if (score <= 500) {
				gotoxy(28, 13); cout << "���� : " << life << " " << stage << " ��������   ";
				gotoxy(28, 14);	cout << "���� : " << score << "���� ȹ���ϼ̽��ϴ�.       ";
				gotoxy(28, 15);	cout << "����Ͻ� ���̵� �Է� �� �ּ���.                ";
				// ���̵� �Է�
				gotoxy(40, 16);
				
			}
			if (score > 500) {
				gotoxy(55, 8);  printf(" -----------------------------------");
				gotoxy(55, 9);  printf("/                                  /");
				gotoxy(54, 10); printf("/                                  /");
				gotoxy(53, 11); printf("/          ��      ��              /");
				gotoxy(52, 12); printf("/                                  /");
				gotoxy(51, 13); printf("/                                  /");
				gotoxy(50, 14); printf("/                                  /");
				gotoxy(49, 15); printf("/   �� �л��� ����� ��������      /");
				gotoxy(48, 16); printf("/                                  /");
				gotoxy(47, 17); printf("/  �̹� �б⸦ �� ������ �����Ƿ�  /");
				gotoxy(46, 18); printf("/                                  /");
				gotoxy(45, 19); printf("/     �� ������ �־� Ī����.       /");
				gotoxy(44, 20); printf("/                                  /");
				gotoxy(43, 21); printf("/                                  /");
				gotoxy(42, 22); printf("/                                  /");
				gotoxy(41, 23); printf(" -----------------------------------");
				gotoxy(50, 5); printf("   ���");
				gotoxy(50, 6); printf("  ����");
				gotoxy(50, 7); printf(" ����");
				gotoxy(50, 8); printf("  ���");
				gotoxy(85, 5); printf("     ���");
				gotoxy(85, 6); printf("   ����");
				gotoxy(85, 7); printf("  ����");
				gotoxy(85, 8); printf("���");
				gotoxy(35, 22); printf("   ���");
				gotoxy(35, 23); printf("  ����");
				gotoxy(35, 24); printf(" ����");
				gotoxy(35, 25); printf("  ���");
				gotoxy(75, 22); printf("���");
				gotoxy(73, 23); printf("����");
				gotoxy(72, 24); printf("����");
				gotoxy(70, 25); printf("���");
				gotoxy(68, 13); printf("�̸� : ");

			} // if End
			// ���̵� �Է�
			getline(cin, name);
			// ���� �Է� �� �ٽ� �Է� �ްԲ� �Ѵ�.
			if (name.size() < 1) {
				cout << "���̵�� ������ �� �����ϴ�. �ٽ� �Է� �� �ּ���";
				next = false;
			}
			else {
				next = true;
			}
		}
		pair<string, int> p(name, score); // ��� ����
		if (userList.insert(p).second == false) {
			cout << "�ٸ� ���̵� �Է� �� �ּ���.";
			flag = true;
		}
		else {
			userList.insert(p); // Map�� ����� �߰�
			flag = false;
		}
	} // while End
	// ��������, ������, ���ھ� ���� ������ ������� ����Ϸ� ��
	rankList();
}

/**
* @History
*		|	Date			|	Author		|	���� ����		|
*		|	2017. 06. 01	|	SeokRae		|	�ű�			|
*		|	2017. 06. 05	|	DongGeun	|	������ �߰�		|
* @Description
*		���� ���� �Լ�
*/
void game(int *stage) {
	// loading(*stage);											/* �ε� �׷��� */
	int speed = 75 - *stage * 15; // ���̵� ����


	if (*stage == 2) { score = 101; }							/* �������� �� ���ھ� */
	if (*stage == 3) { score = 201; }
	if (*stage == 4) { score = 301; }


	MOVEOBJECT mObj[100];										/* �������� ���� ����ü */
	USER user = { 60, 25 };										/* ���� ���� ��ġ [�ʱ�ȭ] */

	bool flag = true;											/* ���� �ݺ����� ���� bool ���� ���� */

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
			switch (key) {						/* pause ��� */
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
			case 'q':
				gotoxy(72, 0);
				coin++;
				cout << "���� : " << coin << "\n";
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
					setColor(12);
					cout << "F";
				}
				if (*stage == 2) {
					setColor(14);
					cout << "C";
				}
				if (*stage == 3) {
					setColor(9);
					cout << "B";
				}
				if (*stage == 4) {
					setColor(11);
					cout << "A";
				}
				// ����ü�� ������� �Ӹ� ������ ���밪�� 2 ���� �۰�, y��ǥ���� ���� ��� �浹
				if (abs(mObj[i].x - user.x) < 2 && (mObj[i].y == user.y)) {
					cout << "\a";					/* ������ ���					*/
					life--;							/* �Ӹ��� ������ ������ 1 ����	*/
					if (life <= 0) {				/* �������� 0�� ��				*/
						bool coinFlag = false;			
						if (coin > 0) {				/* ������ ������ ���� ��		*/
							coinFlag = true;
						}
						while (coinFlag) {
							system("cls");
							cout << "�̾ �Ͻðڽ��ϱ�? �����Ͻðڽ��ϱ�? ( Y / N ) : " << endl;
							cout << "���� ����  : " << coin << "��" << endl;
							if (_kbhit()) { // Ű���� ���ȴ��� Ȯ��
								int key = _getch();
								switch (key) {
								case 'y':
									coin--;
									life = 3;
									flag = true;
									coinFlag = false;
									break;

								case 'n':
									flag = false;
									coinFlag = false;
									break;
								}
							}
						} // while End
						flag = false;
						break;
					} // if (life <= 0) End
				} // if ����ü �Ӹ��� ���� ��

			} // if else �� ��
			  // **  �������� �Ѿ�� �ҽ� �ʿ�
			if (score == 100) { (*stage)++; game(stage); }
			if (score == 200) { (*stage)++; game(stage); }
			if (score == 300) { (*stage)++; game(stage); }
		}// for�� ��

	} // while�� ����

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 08	|	DongGeun	|	���� �߰�   |
* @Description
*		�����ڴ� ���������� �����ؼ� �÷���
*/
void adminLogin() {
	setColor(15); 
	gotoxy(40, 11); cout << "������ ���� �Դϴ�." << "\n";
	gotoxy(41, 12); cout << "���������� �Է��ϼ��� : ";
	int sel;
	cin >> sel;
	game(&sel);
}

/**
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
* @History
*		|	Date			|	Author		|	���� ����				|
*		|	2017. 06. 02	|	SeokRae		|	1~3��, F1(������) �Է�	|
*		|	2017. 06. 08	|	SeokRae		|	4�� �߰�				|
*		|	2017. 06. 08	|	Taeen		|	q�� �߰�(����)			|
* @Description
*		���� �޴��� �ش��ϴ� ������ �ޱ� ���� ����ó�� ��� �Լ�
*/
char isCheckNum() {
	char checkNum = _getch(); /* Ű���� ���� �Է� �޾� ������ ���� */
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
	case'q':
		coin++;
		setColor(15);
		gotoxy(2, 28);
		cout << "COIN -> " << coin << "\n";
		setColor(0);
		Sleep(1000);
		break;
	default:
		return isCheckNum();				/* ����Լ� ȣ�� */
	}
	return checkNum;
}

/**
* @History
*		|	Date			|	Author		|	���� ����	|
*		|	2017. 06. 02	|	SeokRae		|	�ű�		|
*		|	2017. 06. 02	|	TaeEn		|	���η���	|
* @Description
*		���� �޴� ���� �Լ�
*/
void start() {
	while (1) {
		// ���� �ʱ�ȭ
		life = 3;							/* ���� 3���� ����		*/
		stage = 1;							/* �������� 1�� ����	*/
		score = 0;							/* ���ھ� 0���� ����	*/	

		mainMenu();							/* ���� ���� �ؽ�Ʈ ȣ��*/
		// ��� �Լ�
		// 1 ~ 3 �̿ܿ� ���� ���� ��� ��� �Ѵ�.
		char selectNum = isCheckNum();

		switch (selectNum) {
		case '1':			// 1. ���� ����
			if (coin <= 0) {
				setColor(15);
				gotoxy(2, 28);
				cout << "INSERT COIN -> " << coin << endl;
				setColor(0);
				Sleep(500);
				break;
			}
			coin--;
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
	//opening();
	start(); // �޴� ���� �Լ�

}