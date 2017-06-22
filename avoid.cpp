#include <iostream>
#include <Windows.h> // 색깔
#include <conio.h> // _kbhit(), _getch() 함수
#include <stdlib.h> // exit() 함수의 헤더
// #include <time.h>  // Srand((unsigned int)time(NULL)) 하면 투사체가 이상하게 떨어짐
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
int life; //라이프
int coin;
map<string, int> userList; // Map 자료형 사용


template<template <typename> class P = less >
struct compare_pair_second {
	template<class T1, class T2> bool operator()(const pair<T1, T2>&left, const pair<T1, T2>&right) {
		return P<T2>()(left.second, right.second);
	}
};
/**
* 투사체의 움직임을 관리할 구조체
*/
struct MOVEOBJECT {
	int x		// x 좌표
		, y		// y 좌표
		, wait; // 대기시간
};
/**
* 사용자 움직임을 관리할 구조체
*/
struct USER {
	int x		// x 좌표
		, y;	// y 좌표
};

// 화면의 특정 위치로 이동해 주는 함수.
void gotoxy(double x, int y) {
	COORD Pos;
	Pos.X = (short)x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 사람 이동 키 입력 함수
BOOL isKeyState(int Key) {
	// http://seokr.tistory.com/473
	// 키보드의 키가 눌렸는지 체크하는 함수
	// GetAsyncKeyState()는 비 동기처리 함수
	// GetAsyncKeyState()는 키가 눌려진 시점에서 0x8000 값을 리턴 - 현재 키가 눌려진 상태
	// 함수가 호출되었을 때 키가 눌려져 있었다고 0x0001 값을 리턴 - 지난번 호출과 이번 호출 사이에 키가 눌려진 적이 있었다는 표현
	// 즉, 정확한 시점에서 키눌림 상태를 체크 하기 위해서 0x8000으로 AND 연산을 해 주는 것이다.
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

// 색깔 입히기
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
* 콘솔 화면 조절 함수
*/
void systemSetting() {
	// 1. 콘솔 화면 조절
	// Colums 100 Lines 30의 규격으로 하는 콘솔을 실행한다.
	system("mode con: cols=100 lines=30");

	// 2. 타이틀 변경
	system("title F 학점 피하기 게임 (제작자 : 김태은, 김석래, 박동근)");

	// 3. 콘솔 화면 색 바꾸기
	system("Color 0F");

}

/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 02	|	DongGeun	|	신규		|
*		|	2017. 06. 08	|	DongGeun	|	오프닝 수정	|
* @Description
*		게임시작화면
*/
void opening() { //로딩화면
	setColor(11); gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	gotoxy(40, 12); printf("■■\n");
	gotoxy(40, 13); printf("■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 12); printf("■■\n");
	setColor(11); gotoxy(40, 13); printf("■■\n");
	setColor(11); gotoxy(40, 14); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 15); printf("■■■■■■■■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 12); printf("■■\n");
	setColor(11); gotoxy(40, 13); printf("■■\n");
	setColor(11); gotoxy(40, 14); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 15); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 16); printf("■■\n");
	setColor(11); gotoxy(40, 17); printf("■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 12); printf("■■\n");
	setColor(11); gotoxy(40, 13); printf("■■\n");
	setColor(11); gotoxy(40, 14); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 15); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 16); printf("■■\n");
	setColor(11); gotoxy(40, 17); printf("■■\n");
	setColor(11); gotoxy(40, 18); printf("■■\n");
	setColor(11); gotoxy(40, 19); printf("■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(40, 12); printf("■■\n");
	setColor(11); gotoxy(40, 13); printf("■■\n");
	setColor(11); gotoxy(40, 14); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 15); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(40, 16); printf("■■\n");
	setColor(11); gotoxy(40, 17); printf("■■\n");
	setColor(11); gotoxy(40, 18); printf("■■\n");
	setColor(11); gotoxy(40, 19); printf("■■\n");
	setColor(11); gotoxy(40, 20); printf("■■\n");
	setColor(11); gotoxy(40, 21); printf("■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(38, 10); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(38, 11); printf("■■■■■■■■■■■\n");
	setColor(11); gotoxy(38, 12); printf("■■\n");
	setColor(11); gotoxy(38, 13); printf("■■\n");
	setColor(11); gotoxy(38, 14); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(38, 15); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(38, 16); printf("■■\n");
	setColor(11); gotoxy(38, 17); printf("■■\n");
	setColor(11); gotoxy(38, 18); printf("■■\n");
	setColor(11); gotoxy(38, 19); printf("■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(35, 10); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(35, 11); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(35, 12); printf("■■\n");
	setColor(11); gotoxy(35, 13); printf("■■\n");
	setColor(11); gotoxy(35, 14); printf("■■■■■■■\n");
	setColor(11); gotoxy(35, 15); printf("■■■■■■■\n");
	setColor(11); gotoxy(35, 16); printf("■■\n");
	setColor(11); gotoxy(35, 17); printf("■■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(32, 11); printf("■■■■■■■■■\n");
	setColor(11); gotoxy(32, 12); printf("■\n");
	setColor(11); gotoxy(32, 13); printf("■\n");
	setColor(11); gotoxy(32, 14); printf("■■■■■■■\n");
	setColor(11); gotoxy(32, 15); printf("■\n");
	setColor(11); gotoxy(32, 16); printf("■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(30, 11); printf("■■■■■■■\n");
	setColor(11); gotoxy(30, 12); printf("■\n");
	setColor(11); gotoxy(30, 13); printf("■\n");
	setColor(11); gotoxy(30, 14); printf("■■■■■\n");
	setColor(11); gotoxy(30, 15); printf("■\n");
	setColor(11); gotoxy(30, 16); printf("■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(28, 11); printf("■■■■■\n");
	setColor(11); gotoxy(28, 12); printf("■\n");
	setColor(11); gotoxy(28, 13); printf("■\n");
	setColor(11); gotoxy(28, 14); printf("■■■■\n");
	setColor(11); gotoxy(28, 15); printf("■\n");
	setColor(11); gotoxy(28, 16); printf("■\n");
	Sleep(300);
	system("cls");
	setColor(11); gotoxy(26, 11); printf("■■■■■\n");
	setColor(11); gotoxy(26, 12); printf("■\n");
	setColor(11); gotoxy(26, 13); printf("■\n");
	setColor(11); gotoxy(26, 14); printf("■■■■\n");
	setColor(11); gotoxy(26, 15); printf("■\n");
	setColor(11); gotoxy(26, 16); printf("■\n");
	setColor(1); gotoxy(36, 9);  printf("  ■■■\n");
	setColor(1); gotoxy(36, 10); printf(" ■■■■  ■\n");
	setColor(1); gotoxy(36, 11); printf("   ■■    ■\n");
	setColor(1); gotoxy(36, 12); printf("  ■  ■   ■■■\n");
	setColor(1); gotoxy(36, 13); printf("   ■■    ■\n");
	setColor(1); gotoxy(36, 14); printf("           ■\n");
	setColor(1); gotoxy(36, 15); printf("    ■■■■\n");
	setColor(1); gotoxy(36, 16); printf("          ■\n");
	setColor(1); gotoxy(36, 17); printf("          ■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(24, 11); printf("■■■■■\n");
	setColor(11); gotoxy(24, 12); printf("■\n");
	setColor(11); gotoxy(24, 13); printf("■\n");
	setColor(11); gotoxy(24, 14); printf("■■■■\n");
	setColor(11); gotoxy(24, 15); printf("■\n");
	setColor(11); gotoxy(24, 16); printf("■\n");
	setColor(9); gotoxy(34, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(34, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(34, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(34, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(34, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(34, 14); printf("           ■\n");
	setColor(9); gotoxy(34, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(34, 16); printf("          ■\n");
	setColor(9); gotoxy(34, 17); printf("          ■\n");
	setColor(6); gotoxy(47, 14); printf("  ■■■■    ■\n");
	setColor(6); gotoxy(47, 15); printf("       ■     ■\n");
	setColor(6); gotoxy(47, 16); printf("      ■  ■■■\n");
	setColor(6); gotoxy(47, 17); printf("    ■  ■    ■\n");
	setColor(6); gotoxy(47, 18); printf("  ■     ■   ■\n");
	setColor(6); gotoxy(47, 19); printf("    ■■■■■\n");
	setColor(6); gotoxy(47, 20); printf("    ■      ■\n");
	setColor(6); gotoxy(47, 21); printf("    ■      ■\n");
	setColor(6); gotoxy(47, 22); printf("    ■■■■■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(22, 11); printf("■■■■■\n");
	setColor(11); gotoxy(22, 12); printf("■\n");
	setColor(11); gotoxy(22, 13); printf("■\n");
	setColor(11); gotoxy(22, 14); printf("■■■■\n");
	setColor(11); gotoxy(22, 15); printf("■\n");
	setColor(11); gotoxy(22, 16); printf("■\n");
	setColor(9); gotoxy(32, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(32, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(32, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(32, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(32, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(32, 14); printf("           ■\n");
	setColor(9); gotoxy(32, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(32, 16); printf("          ■\n");
	setColor(9); gotoxy(32, 17); printf("          ■\n");
	setColor(14); gotoxy(45, 14); printf("  ■■■■    ■\n");
	setColor(14); gotoxy(45, 15); printf("       ■     ■\n");
	setColor(14); gotoxy(45, 16); printf("      ■  ■■■\n");
	setColor(14); gotoxy(45, 17); printf("    ■  ■    ■\n");
	setColor(14); gotoxy(45, 18); printf("  ■     ■   ■\n");
	setColor(14); gotoxy(45, 19); printf("    ■■■■■\n");
	setColor(14); gotoxy(45, 20); printf("    ■      ■\n");
	setColor(14); gotoxy(45, 21); printf("    ■      ■\n");
	setColor(14); gotoxy(45, 22); printf("    ■■■■■\n");
	setColor(4); gotoxy(55, 8);  printf("             ■\n");
	setColor(4); gotoxy(55, 9);  printf(" ■■■■■  ■\n");
	setColor(4); gotoxy(55, 10); printf("   ■  ■    ■\n");
	setColor(4); gotoxy(55, 11); printf("   ■  ■    ■\n");
	setColor(4); gotoxy(55, 12); printf(" ■■■■■  ■\n");
	setColor(4); gotoxy(55, 13); printf("             ■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(20, 11); printf("■■■■■\n");
	setColor(11); gotoxy(20, 12); printf("■\n");
	setColor(11); gotoxy(20, 13); printf("■\n");
	setColor(11); gotoxy(20, 14); printf("■■■■\n");
	setColor(11); gotoxy(20, 15); printf("■\n");
	setColor(11); gotoxy(20, 16); printf("■\n");
	setColor(9); gotoxy(30, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(30, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(30, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(30, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(30, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(30, 14); printf("           ■\n");
	setColor(9); gotoxy(30, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(30, 16); printf("          ■\n");
	setColor(9); gotoxy(30, 17); printf("          ■\n");
	setColor(14); gotoxy(43, 14); printf("  ■■■■    ■\n");
	setColor(14); gotoxy(43, 15); printf("       ■     ■\n");
	setColor(14); gotoxy(43, 16); printf("      ■  ■■■\n");
	setColor(14); gotoxy(43, 17); printf("    ■  ■    ■\n");
	setColor(14); gotoxy(43, 18); printf("  ■     ■   ■\n");
	setColor(14); gotoxy(43, 19); printf("    ■■■■■\n");
	setColor(14); gotoxy(43, 20); printf("    ■      ■\n");
	setColor(14); gotoxy(43, 21); printf("    ■      ■\n");
	setColor(14); gotoxy(43, 22); printf("    ■■■■■\n");
	setColor(12); gotoxy(53, 8);  printf("             ■\n");
	setColor(12); gotoxy(53, 9);  printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(53, 10); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(53, 11); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(53, 12); printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(53, 13); printf("             ■\n");
	setColor(2); gotoxy(63, 15); printf("  ■■■   ■\n");
	setColor(2); gotoxy(63, 16); printf(" ■■■■  ■\n");
	setColor(2); gotoxy(63, 17); printf("   ■■    ■■■\n");
	setColor(2); gotoxy(63, 18); printf("  ■  ■   ■\n");
	setColor(2); gotoxy(63, 19); printf("   ■■    ■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("■■■■■\n");
	setColor(11); gotoxy(18, 12); printf("■\n");
	setColor(11); gotoxy(18, 13); printf("■\n");
	setColor(11); gotoxy(18, 14); printf("■■■■\n");
	setColor(11); gotoxy(18, 15); printf("■\n");
	setColor(11); gotoxy(18, 16); printf("■\n");
	setColor(9); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 14); printf("           ■\n");
	setColor(9); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(28, 16); printf("          ■\n");
	setColor(9); gotoxy(28, 17); printf("          ■\n");
	setColor(14); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(14); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(14); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(14); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(14); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(14); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(14); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(12); gotoxy(51, 8);  printf("             ■\n");
	setColor(12); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 13); printf("             ■\n");
	setColor(10); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(10); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(10); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(10); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(10); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(5); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(5); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(5); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(5); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(5); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("■■■■■\n");
	setColor(11); gotoxy(18, 12); printf("■\n");
	setColor(11); gotoxy(18, 13); printf("■\n");
	setColor(11); gotoxy(18, 14); printf("■■■■\n");
	setColor(11); gotoxy(18, 15); printf("■\n");
	setColor(11); gotoxy(18, 16); printf("■\n");
	setColor(9); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 14); printf("           ■\n");
	setColor(9); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(28, 16); printf("          ■\n");
	setColor(9); gotoxy(28, 17); printf("          ■\n");
	setColor(14); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(14); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(14); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(14); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(14); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(14); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(14); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(12); gotoxy(51, 8);  printf("             ■\n");
	setColor(12); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 13); printf("             ■\n");
	setColor(10); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(10); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(10); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(10); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(10); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(13); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(13); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(13); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(13); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(13); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(13); gotoxy(18, 11); printf("■■■■■\n");
	setColor(13); gotoxy(18, 12); printf("■\n");
	setColor(13); gotoxy(18, 13); printf("■\n");
	setColor(13); gotoxy(18, 14); printf("■■■■\n");
	setColor(13); gotoxy(18, 15); printf("■\n");
	setColor(13); gotoxy(18, 16); printf("■\n");
	setColor(11); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(11); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(11); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(11); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(11); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(11); gotoxy(28, 14); printf("           ■\n");
	setColor(11); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(11); gotoxy(28, 16); printf("          ■\n");
	setColor(11); gotoxy(28, 17); printf("          ■\n");
	setColor(9); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(9); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(9); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(9); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(9); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(9); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(9); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(9); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(9); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(14); gotoxy(51, 8);  printf("             ■\n");
	setColor(14); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(14); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(14); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(14); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(14); gotoxy(51, 13); printf("             ■\n");
	setColor(12); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(12); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(12); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(12); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(12); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(10); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(10); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(10); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(10); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(10); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(10); gotoxy(18, 11); printf("■■■■■\n");
	setColor(10); gotoxy(18, 12); printf("■\n");
	setColor(10); gotoxy(18, 13); printf("■\n");
	setColor(10); gotoxy(18, 14); printf("■■■■\n");
	setColor(10); gotoxy(18, 15); printf("■\n");
	setColor(10); gotoxy(18, 16); printf("■\n");
	setColor(13); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(13); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(13); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(13); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(13); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(13); gotoxy(28, 14); printf("           ■\n");
	setColor(13); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(13); gotoxy(28, 16); printf("          ■\n");
	setColor(13); gotoxy(28, 17); printf("          ■\n");
	setColor(11); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(11); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(11); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(11); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(11); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(11); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(11); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(11); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(11); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(9); gotoxy(51, 8);  printf("             ■\n");
	setColor(9); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(9); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(9); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(9); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(9); gotoxy(51, 13); printf("             ■\n");
	setColor(14); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(14); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(14); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(14); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(14); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(12); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(12); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(12); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(12); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(12); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(12); gotoxy(18, 11); printf("■■■■■\n");
	setColor(12); gotoxy(18, 12); printf("■\n");
	setColor(12); gotoxy(18, 13); printf("■\n");
	setColor(12); gotoxy(18, 14); printf("■■■■\n");
	setColor(12); gotoxy(18, 15); printf("■\n");
	setColor(12); gotoxy(18, 16); printf("■\n");
	setColor(10); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(10); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(10); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(10); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(10); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(10); gotoxy(28, 14); printf("           ■\n");
	setColor(10); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(10); gotoxy(28, 16); printf("          ■\n");
	setColor(10); gotoxy(28, 17); printf("          ■\n");
	setColor(13); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(13); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(13); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(13); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(13); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(13); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(13); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(13); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(13); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(11); gotoxy(51, 8);  printf("             ■\n");
	setColor(11); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(11); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(11); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(11); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(11); gotoxy(51, 13); printf("             ■\n");
	setColor(9); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(9); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(9); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(9); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(14); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(14); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(14); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(14); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(14); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(14); gotoxy(18, 11); printf("■■■■■\n");
	setColor(14); gotoxy(18, 12); printf("■\n");
	setColor(14); gotoxy(18, 13); printf("■\n");
	setColor(14); gotoxy(18, 14); printf("■■■■\n");
	setColor(14); gotoxy(18, 15); printf("■\n");
	setColor(14); gotoxy(18, 16); printf("■\n");
	setColor(12); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(12); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(12); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(12); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(12); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(12); gotoxy(28, 14); printf("           ■\n");
	setColor(12); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(12); gotoxy(28, 16); printf("          ■\n");
	setColor(12); gotoxy(28, 17); printf("          ■\n");
	setColor(10); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(10); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(10); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(10); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(10); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(10); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(10); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(10); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(10); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(13); gotoxy(51, 8);  printf("             ■\n");
	setColor(13); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(13); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(13); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(13); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(13); gotoxy(51, 13); printf("             ■\n");
	setColor(11); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(11); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(11); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(11); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(11); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(9); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(9); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(9); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(9); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(9); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(9); gotoxy(18, 11); printf("■■■■■\n");
	setColor(9); gotoxy(18, 12); printf("■\n");
	setColor(9); gotoxy(18, 13); printf("■\n");
	setColor(9); gotoxy(18, 14); printf("■■■■\n");
	setColor(9); gotoxy(18, 15); printf("■\n");
	setColor(9); gotoxy(18, 16); printf("■\n");
	setColor(14); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(14); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(14); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(14); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(14); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(14); gotoxy(28, 14); printf("           ■\n");
	setColor(14); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(14); gotoxy(28, 16); printf("          ■\n");
	setColor(14); gotoxy(28, 17); printf("          ■\n");
	setColor(12); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(12); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(12); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(12); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(12); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(12); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(12); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(12); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(12); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(10); gotoxy(51, 8);  printf("             ■\n");
	setColor(10); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(10); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(10); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(10); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(10); gotoxy(51, 13); printf("             ■\n");
	setColor(13); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(13); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(13); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(13); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(13); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(11); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(11); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(11); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(11); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(11); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("■■■■■\n");
	setColor(11); gotoxy(18, 12); printf("■\n");
	setColor(11); gotoxy(18, 13); printf("■\n");
	setColor(11); gotoxy(18, 14); printf("■■■■\n");
	setColor(11); gotoxy(18, 15); printf("■\n");
	setColor(11); gotoxy(18, 16); printf("■\n");
	setColor(9); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 14); printf("           ■\n");
	setColor(9); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(28, 16); printf("          ■\n");
	setColor(9); gotoxy(28, 17); printf("          ■\n");
	setColor(14); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(14); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(14); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(14); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(14); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(14); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(14); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(12); gotoxy(51, 8);  printf("             ■\n");
	setColor(12); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 13); printf("             ■\n");
	setColor(10); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(10); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(10); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(10); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(10); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(13); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(13); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(13); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(13); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(13); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(3); gotoxy(18, 11); printf("■■■■■\n");
	setColor(3); gotoxy(18, 12); printf("■\n");
	setColor(3); gotoxy(18, 13); printf("■\n");
	setColor(3); gotoxy(18, 14); printf("■■■■\n");
	setColor(3); gotoxy(18, 15); printf("■\n");
	setColor(3); gotoxy(18, 16); printf("■\n");
	setColor(4); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(4); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(4); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(4); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(4); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(4); gotoxy(28, 14); printf("           ■\n");
	setColor(4); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(4); gotoxy(28, 16); printf("          ■\n");
	setColor(4); gotoxy(28, 17); printf("          ■\n");
	setColor(6); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(6); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(6); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(6); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(6); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(6); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(6); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(6); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(6); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(5); gotoxy(51, 8);  printf("             ■\n");
	setColor(5); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(5); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(5); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(5); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(5); gotoxy(51, 13); printf("             ■\n");
	setColor(2); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(2); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(2); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(2); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(2); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(4); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(4); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(4); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(4); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(4); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(700);
	system("cls");
	setColor(11); gotoxy(18, 11); printf("■■■■■\n");
	setColor(11); gotoxy(18, 12); printf("■\n");
	setColor(11); gotoxy(18, 13); printf("■\n");
	setColor(11); gotoxy(18, 14); printf("■■■■\n");
	setColor(11); gotoxy(18, 15); printf("■\n");
	setColor(11); gotoxy(18, 16); printf("■\n");
	setColor(9); gotoxy(28, 9);  printf("  ■■■\n");
	setColor(9); gotoxy(28, 10); printf(" ■■■■  ■\n");
	setColor(9); gotoxy(28, 11); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 12); printf("  ■  ■   ■■■\n");
	setColor(9); gotoxy(28, 13); printf("   ■■    ■\n");
	setColor(9); gotoxy(28, 14); printf("           ■\n");
	setColor(9); gotoxy(28, 15); printf("    ■■■■\n");
	setColor(9); gotoxy(28, 16); printf("          ■\n");
	setColor(9); gotoxy(28, 17); printf("          ■\n");
	setColor(14); gotoxy(41, 14); printf("  ■■■■    ■\n");
	setColor(14); gotoxy(41, 15); printf("       ■     ■\n");
	setColor(14); gotoxy(41, 16); printf("      ■  ■■■\n");
	setColor(14); gotoxy(41, 17); printf("    ■  ■    ■\n");
	setColor(14); gotoxy(41, 18); printf("  ■     ■   ■\n");
	setColor(14); gotoxy(41, 19); printf("    ■■■■■\n");
	setColor(14); gotoxy(41, 20); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 21); printf("    ■      ■\n");
	setColor(14); gotoxy(41, 22); printf("    ■■■■■\n");
	setColor(12); gotoxy(51, 8);  printf("             ■\n");
	setColor(12); gotoxy(51, 9);  printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 10); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 11); printf("   ■  ■    ■\n");
	setColor(12); gotoxy(51, 12); printf(" ■■■■■  ■\n");
	setColor(12); gotoxy(51, 13); printf("             ■\n");
	setColor(10); gotoxy(61, 15); printf("  ■■■   ■\n");
	setColor(10); gotoxy(61, 16); printf(" ■■■■  ■\n");
	setColor(10); gotoxy(61, 17); printf("   ■■    ■■■\n");
	setColor(10); gotoxy(61, 18); printf("  ■  ■   ■\n");
	setColor(10); gotoxy(61, 19); printf("   ■■    ■\n");
	setColor(13); gotoxy(72, 9);  printf(" ■■■■  ■\n");
	setColor(13); gotoxy(72, 10); printf("      ■   ■\n");
	setColor(13); gotoxy(72, 11); printf("     ■    ■\n");
	setColor(13); gotoxy(72, 12); printf("   ■      ■\n");
	setColor(13); gotoxy(72, 13); printf("  ■       ■\n");
	Sleep(2000);
	system("cls");





}

/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 03	|	DongGeun	|	신규(1교시)	|
*		|	2017. 06. 07	|	SeokRae		|	2 ~ 4교시	|
* @Description
*		게임로딩화면
*/
void loading(int stage) {

	switch (stage) {

	case 2:
		setColor(12);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■    ■■■■            ■■■■■■■■  ■■■■■■  ■■■■\n");
		gotoxy(11, 22); printf("■■■■■      ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■\n");
		gotoxy(11, 23); printf("■■■■■■    ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■\n");
		gotoxy(11, 26); printf("■■■■■■    ■■■                  ■■■■■■■■■■■■■  ■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■    ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■\n");
		gotoxy(11, 22); printf("■■■      ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■\n");
		gotoxy(11, 24); printf("■■■■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■\n");
		gotoxy(11, 25); printf("■■■■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■\n");
		gotoxy(11, 26); printf("■■■■    ■■■                  ■■■■■■■■■■■■■  ■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■    ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■\n");
		gotoxy(11, 22); printf("      ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■\n");
		gotoxy(11, 23); printf("■    ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■\n");
		gotoxy(11, 24); printf("■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■\n");
		gotoxy(11, 25); printf("■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■\n");
		gotoxy(11, 26); printf("■    ■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("        ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("            ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("  ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("      ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		setColor(14);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		break;

	case 3:
		system("cls");
		setColor(14);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■\n");
		gotoxy(11, 23); printf("■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 25); printf("■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■\n");
		gotoxy(11, 23); printf("          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 25); printf("          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("        ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("            ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("  ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("      ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		setColor(9);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		break;
	case 4:
		system("cls");
		setColor(9);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■\n");
		gotoxy(11, 23); printf("■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 25); printf("■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■\n");
		gotoxy(11, 23); printf("          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 25); printf("          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("        ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("            ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("  ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("      ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		setColor(11);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■  ■■■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■  ■■■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■  ■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■  ■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■  ■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		Sleep(150);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■■■  ■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■  ■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		break;
	default:
		break;
	}
}

/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 01	|	SeokRae		|	신규		|
*		|	2017. 06. 07	|	SeokRae		|	타이틀 넣기	|
* @Description
*		게임 메인 메뉴
*/
void mainMenu() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(MAP_X / 2.7, 10);
	gotoxy(8, 1);  printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(8, 2);  printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(8, 3);  printf("■■  에프    ■■          ■■          ■■■■■■■■■      ■■■■■■■■■\n");
	gotoxy(8, 4);  printf("■■  ■■■■■■  ■■■  ■■  ■■■■■■■■■■■■  ■■■  ■■■■  ■■■\n");
	gotoxy(8, 5);  printf("■■  ■■■■■■  ■■■  ■■  ■■■■■■        ■■  ■■■  ■■■■  ■■■\n");
	gotoxy(8, 6);  printf("■■        ■■■    피    ■■          ■■■■■■■■   에이   ■■  플러스  ■\n");
	gotoxy(8, 7);  printf("■■  ■■■■■■  ■■■■■■■■■■  ■■        ■■  ■■■  ■■■■  ■■■\n");
	gotoxy(8, 8);  printf("■■  ■■■■■■  ■■■■■■■■■■  ■■■■■■■■  ■■■  ■■■■  ■■■\n");
	gotoxy(8, 9);  printf("■■  ■■■■■■  ■■■■■■   해쓰   ■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(8, 10); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(80, 11); setColor(8);  printf("by. 종모지리");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(MAP_X / 2.6, 20);
	cout << " 1. 게 임 시 작 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(MAP_X / 2.6, 22);
	cout << " 2. 게 임 설 명 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(MAP_X / 2.6, 24);
	cout << " 3. 순 위 정 보 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(MAP_X / 2.6, 26);
	cout << " 4. 게 임 종 료 " << "\n";
}

/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 08	|	SeokRae		|	랭킹 표시	|
* @Description
*		map자료구조에 저장된 유저 리스트를 최대 10명 출력한다.
*/
void rankList() {
	
	int index = 0;
	
	system("cls");
	gotoxy(MAP_X / 2.4, 10);
	cout << "랭킹 정보";
	gotoxy(MAP_X / 2.6, 11);
	cout << " 순 위 " << " :: " << "아이디" << " :: " << "점 수";
	
	// 제네릭을 pair로 하는 vector를 만들어 Map의 시작부터 끝까지 넣는다.
	vector<pair<string, int> > rank(userList.begin(), userList.end());

	// 정렬 라이브러리를 사용하여 vector를 오름차순으로 정렬
	sort(rank.begin(), rank.end(), compare_pair_second<less>());

	// https://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
	for (int j = rank.size() - 1; j >= 0; j--) {
		gotoxy(MAP_X / 2.2, (12 + index));
		cout << "	" << rank.size() - j << " ::	" << rank[j].first << " ::	" << rank[j].second << '\n';
		index++;
	}
	// 잠시 대기
	setColor(0);
	system("pause");
}



/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 07	|	SeokRae		|	아이디 등록 |
*		|	2017. 06. 09	|	DongGeun		|	상장 그래픽 |
* @Description
*		스코어에 따라 학점 출력 함수
*/
void login() {

	bool flag = true;

	string name;
	string pwd;

	while (flag) {
		bool next = false;
		while (!next) {
			if (score <= 500) {
				gotoxy(28, 13); cout << "생명 : " << life << " " << stage << " 스테이지   ";
				gotoxy(28, 14);	cout << "총점 : " << score << "점을 획득하셨습니다.       ";
				gotoxy(28, 15);	cout << "등록하실 아이디를 입력 해 주세요.                ";
				// 아이디 입력
				gotoxy(40, 16);
				
			}
			if (score > 500) {
				gotoxy(55, 8);  printf(" -----------------------------------");
				gotoxy(55, 9);  printf("/                                  /");
				gotoxy(54, 10); printf("/                                  /");
				gotoxy(53, 11); printf("/          상      장              /");
				gotoxy(52, 12); printf("/                                  /");
				gotoxy(51, 13); printf("/                                  /");
				gotoxy(50, 14); printf("/                                  /");
				gotoxy(49, 15); printf("/   위 학생은 우수한 성적으로      /");
				gotoxy(48, 16); printf("/                                  /");
				gotoxy(47, 17); printf("/  이번 학기를 잘 마무리 했으므로  /");
				gotoxy(46, 18); printf("/                                  /");
				gotoxy(45, 19); printf("/     이 상장을 주어 칭찬함.       /");
				gotoxy(44, 20); printf("/                                  /");
				gotoxy(43, 21); printf("/                                  /");
				gotoxy(42, 22); printf("/                                  /");
				gotoxy(41, 23); printf(" -----------------------------------");
				gotoxy(50, 5); printf("   ■■");
				gotoxy(50, 6); printf("  ■■■");
				gotoxy(50, 7); printf(" ■■■");
				gotoxy(50, 8); printf("  ■■");
				gotoxy(85, 5); printf("     ■■");
				gotoxy(85, 6); printf("   ■■■");
				gotoxy(85, 7); printf("  ■■■");
				gotoxy(85, 8); printf("■■");
				gotoxy(35, 22); printf("   ■■");
				gotoxy(35, 23); printf("  ■■■");
				gotoxy(35, 24); printf(" ■■■");
				gotoxy(35, 25); printf("  ■■");
				gotoxy(75, 22); printf("■■");
				gotoxy(73, 23); printf("■■■");
				gotoxy(72, 24); printf("■■■");
				gotoxy(70, 25); printf("■■");
				gotoxy(68, 13); printf("이름 : ");

			} // if End
			// 아이디 입력
			getline(cin, name);
			// 공백 입력 시 다시 입력 받게끔 한다.
			if (name.size() < 1) {
				cout << "아이디는 공백일 수 없습니다. 다시 입력 해 주세요";
				next = false;
			}
			else {
				next = true;
			}
		}
		pair<string, int> p(name, score); // 페어 설정
		if (userList.insert(p).second == false) {
			cout << "다른 아이디를 입력 해 주세요.";
			flag = true;
		}
		else {
			userList.insert(p); // Map에 사용자 추가
			flag = false;
		}
	} // while End
	// 스테이지, 라이프, 스코어 값을 가지고 결과물을 출력하러 감
	rankList();
}

/**
* @History
*		|	Date			|	Author		|	변경 내용		|
*		|	2017. 06. 01	|	SeokRae		|	신규			|
*		|	2017. 06. 05	|	DongGeun	|	라이프 추가		|
* @Description
*		게임 실행 함수
*/
void game(int *stage) {
	// loading(*stage);											/* 로딩 그래픽 */
	int speed = 75 - *stage * 15; // 난이도 조절


	if (*stage == 2) { score = 101; }							/* 스테이지 별 스코어 */
	if (*stage == 3) { score = 201; }
	if (*stage == 4) { score = 301; }


	MOVEOBJECT mObj[100];										/* 떨어지는 학점 구조체 */
	USER user = { 60, 25 };										/* 유저 시작 위치 [초기화] */

	bool flag = true;											/* 게임 반복문에 대한 bool 변수 선언 */

	// [초기화] 투사체 F학점 개수, 좌표, 대기 시간
	for (int i = 0; i < 100; i++) {
		mObj[i].x = rand() % 100 + 1;	// x좌표 1 ~ 100 까지 랜덤으로 생성한다.
		mObj[i].y = 3;					// y좌표 2에서 생성
		mObj[i].wait = rand() % 20;	// 생성 대기시간을 주어 한 줄로 떨어지지 않게 한다.
	}

	/*
	* 게임 움직임 부분
	*/
	while (flag) {

		Sleep(speed); // Sleep() 함수를 통해 속도 조절
		system("cls"); // 화면 지우기

		gotoxy(5, 2);
		cout << "Stage : " << (*stage);
		gotoxy(70, 2);
		cout << "Score : " << score;

		switch (life) { //라이프 출력
		case 3:
			gotoxy(90, 2);
			cout << "♥ ♥ ♥";
			break;
		case 2:
			gotoxy(90, 2);
			cout << "♥ ♥ ♡";
			break;
		case 1:
			gotoxy(90, 2);
			cout << "♥ ♡ ♡";
			break;
		default:
			gotoxy(90, 2);
			cout << "♡ ♡ ♡";
			flag = false;

		}
		// 일시정지 기능 조건문
		if (_kbhit()) { // 키보드 눌렸는지 확인
			int key = _getch();
			switch (key) {						/* pause 기능 */
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
				cout << "코인 : " << coin << "\n";
				break;
			}

		}


		// 사람 움직임 처리
		if (isKeyState(VK_LEFT)) {
			if (user.x > 1) {
				user.x -= 2;
			}
		}
		if (isKeyState(VK_RIGHT)) {
			if (user.x <= 100) {
				user.x += 2;
			}
		} // 사람 움직임 처리 끝

		  // 사람 출력
		gotoxy(user.x, user.y);
		setColor(FOREGROUND_INTENSITY);
		cout << "ㅇ" << "\n";
		gotoxy(user.x, user.y + 1);
		cout << "■" << "\n";
		gotoxy(user.x, user.y + 2);
		cout << "||" << "\n";


		for (int i = 0; i < 100; i++) { // * 50 투사체 개수 난이도에 따라 바꿔야 함
										// 투사체가 떨어지기 전 (대기 시간을 주어 일렬로 떨어지지 않게 함 
			if (mObj[i].wait > 0) {
				// 대기 시간을 주어 한 줄로 투사체가 떨어지지 않도록 한다.
				mObj[i].wait--;
			}
			else {
				// 투사체를 한칸 아래로 이동한다.
				mObj[i].y++;
				// F 학점이 최하단에 도착 했을 때 처리.
				if (mObj[i].y >= 27) {
					mObj[i].x = rand() % 100 + 1;
					mObj[i].y = 5;
					score++;
				}
				// F 학점 출력
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
				// 투사체와 사용자의 머리 사이의 절대값이 2 보다 작고, y좌표값이 같을 경우 충돌
				if (abs(mObj[i].x - user.x) < 2 && (mObj[i].y == user.y)) {
					cout << "\a";					/* 비프음 출력					*/
					life--;							/* 머리에 맞으면 라이프 1 감소	*/
					if (life <= 0) {				/* 라이프가 0일 때				*/
						bool coinFlag = false;			
						if (coin > 0) {				/* 코인을 가지고 있을 때		*/
							coinFlag = true;
						}
						while (coinFlag) {
							system("cls");
							cout << "이어서 하시겠습니까? 종료하시겠습니까? ( Y / N ) : " << endl;
							cout << "현재 코인  : " << coin << "개" << endl;
							if (_kbhit()) { // 키보드 눌렸는지 확인
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
				} // if 투사체 머리에 맞을 때

			} // if else 문 끝
			  // **  스테이지 넘어가는 소스 필요
			if (score == 100) { (*stage)++; game(stage); }
			if (score == 200) { (*stage)++; game(stage); }
			if (score == 300) { (*stage)++; game(stage); }
		}// for문 끝

	} // while문 종료

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 08	|	DongGeun	|	내용 추가   |
* @Description
*		관리자는 스테이지를 선택해서 플레이
*/
void adminLogin() {
	setColor(15); 
	gotoxy(40, 11); cout << "관리자 버전 입니다." << "\n";
	gotoxy(41, 12); cout << "스테이지를 입력하세요 : ";
	int sel;
	cin >> sel;
	game(&sel);
}

/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 01	|	SeokRae		|	신규		|
*		|	2017. 06. 05	|	DongGeun	|	라이프 추가 |
* @Description
*		게임 설명
*/
void description() {

}



/**
* @History
*		|	Date			|	Author		|	변경 내용				|
*		|	2017. 06. 02	|	SeokRae		|	1~3번, F1(관리자) 입력	|
*		|	2017. 06. 08	|	SeokRae		|	4번 추가				|
*		|	2017. 06. 08	|	Taeen		|	q번 추가(코인)			|
* @Description
*		메인 메뉴에 해당하는 값만을 받기 위한 예외처리 재귀 함수
*/
char isCheckNum() {
	char checkNum = _getch(); /* 키보드 값을 입력 받아 변수에 저장 */
	// 메뉴의 숫자(1 ~ 3)외에 다른 숫자가 입력 될 경우 
	// 다시 입력하게끔 하지만 화면상 보이진 않음
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
		return isCheckNum();				/* 재귀함수 호출 */
	}
	return checkNum;
}

/**
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 02	|	SeokRae		|	신규		|
*		|	2017. 06. 02	|	TaeEn		|	코인로직	|
* @Description
*		메인 메뉴 선택 함수
*/
void start() {
	while (1) {
		// 변수 초기화
		life = 3;							/* 생명 3으로 시작		*/
		stage = 1;							/* 스테이지 1로 시작	*/
		score = 0;							/* 스코어 0으로 시작	*/	

		mainMenu();							/* 메인 선택 텍스트 호출*/
		// 재귀 함수
		// 1 ~ 3 이외에 값을 받을 경우 재귀 한다.
		char selectNum = isCheckNum();

		switch (selectNum) {
		case '1':			// 1. 게임 시작
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
		case '2': // 2. 게임 설명
			description(); // 게임 설명 함수 호출
			break;
		case '3': // 3. 게임 종료
			rankList(); // 게임 설명 함수 호출
			break;
		case '4': // 2. 게임 설명
			exit(0); // 시스템 종료 함수 호출
			break;

		default:
			break;
		}
	}
}

/**
* @History
*		|	Date			|	Author		|	변경 내용									|
*		|	2017. 06. 01	|	SeokRae		|	systemSetting(), mainMenu()					|
*		|	2017. 06. 02	|	DongGeun	|	opening(), loading()						|
*		|	2017. 06. 02	|	SeokRae		|	start()										|
* @Description
*		메인 함수
*/
void main() {
	systemSetting();
	//opening();
	start(); // 메뉴 선택 함수

}