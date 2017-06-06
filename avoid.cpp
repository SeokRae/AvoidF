#include <iostream>
#include <Windows.h> // 색깔
#include <conio.h> // _kbhit(), _getch() 함수
#include <stdlib.h> // exit() 함수의 헤더
// #include <time.h>  // Srand((unsigned int)time(NULL)) 하면 투사체가 이상하게 떨어짐

using namespace std;
/**
* 투사체의 움직임을 관리 할 구조체
*/
struct MOVEOBJECT {
	int x		// x 좌표
		, y		// y 좌표
		, wait; // 대기시간
};

struct USER {
	int x		// x 좌표
		, y;	// y 좌표
};

// 화면의 특정 위치로 이동해 주는 함수.
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
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
	system("Color 0B");

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 02	|	DongGeun	|	신규		|
* @Description
*		게임시작화면
*/
void opening() { //로딩화면
	gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	gotoxy(40, 12); printf("■■\n");
	gotoxy(40, 13); printf("■■\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	gotoxy(40, 12); printf("■■\n");
	gotoxy(40, 13); printf("■■\n");
	gotoxy(40, 14); printf("■■■■■■■■■\n");
	gotoxy(40, 15); printf("■■■■■■■■■\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	gotoxy(40, 12); printf("■■\n");
	gotoxy(40, 13); printf("■■\n");
	gotoxy(40, 14); printf("■■■■■■■■■\n");
	gotoxy(40, 15); printf("■■■■■■■■■\n");
	gotoxy(40, 16); printf("■■\n");
	gotoxy(40, 17); printf("■■\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	gotoxy(40, 12); printf("■■\n");
	gotoxy(40, 13); printf("■■\n");
	gotoxy(40, 14); printf("■■■■■■■■■\n");
	gotoxy(40, 15); printf("■■■■■■■■■\n");
	gotoxy(40, 16); printf("■■\n");
	gotoxy(40, 17); printf("■■\n");
	gotoxy(40, 18); printf("■■\n");
	gotoxy(40, 19); printf("■■\n");
	Sleep(300);
	system("cls");
	gotoxy(40, 10); printf("■■■■■■■■■■■\n");
	gotoxy(40, 11); printf("■■■■■■■■■■■\n");
	gotoxy(40, 12); printf("■■\n");
	gotoxy(40, 13); printf("■■\n");
	gotoxy(40, 14); printf("■■■■■■■■■\n");
	gotoxy(40, 15); printf("■■■■■■■■■\n");
	gotoxy(40, 16); printf("■■\n");
	gotoxy(40, 17); printf("■■\n");
	gotoxy(40, 18); printf("■■\n");
	gotoxy(40, 19); printf("■■\n");
	gotoxy(40, 20); printf("■■\n");
	gotoxy(40, 21); printf("■■\n");
	Sleep(300);
	system("cls");
	gotoxy(38, 10); printf("■■■■■■■■■■■\n");
	gotoxy(38, 11); printf("■■■■■■■■■■■\n");
	gotoxy(38, 12); printf("■■\n");
	gotoxy(38, 13); printf("■■\n");
	gotoxy(38, 14); printf("■■■■■■■■■\n");
	gotoxy(38, 15); printf("■■■■■■■■■\n");
	gotoxy(38, 16); printf("■■\n");
	gotoxy(38, 17); printf("■■\n");
	gotoxy(38, 18); printf("■■\n");
	gotoxy(38, 19); printf("■■\n");
	Sleep(300);
	system("cls");
	gotoxy(35, 10); printf("■■■■■■■■■\n");
	gotoxy(35, 11); printf("■■■■■■■■■\n");
	gotoxy(35, 12); printf("■■\n");
	gotoxy(35, 13); printf("■■\n");
	gotoxy(35, 14); printf("■■■■■■■\n");
	gotoxy(35, 15); printf("■■■■■■■\n");
	gotoxy(35, 16); printf("■■\n");
	gotoxy(35, 17); printf("■■\n");
	Sleep(300);
	system("cls");
	gotoxy(32, 11); printf("■■■■■■■■■\n");
	gotoxy(32, 12); printf("■\n");
	gotoxy(32, 13); printf("■\n");
	gotoxy(32, 14); printf("■■■■■■■\n");
	gotoxy(32, 15); printf("■\n");
	gotoxy(32, 16); printf("■\n");
	Sleep(300);
	system("cls");
	gotoxy(30, 11); printf("■■■■■■■\n");
	gotoxy(30, 12); printf("■\n");
	gotoxy(30, 13); printf("■\n");
	gotoxy(30, 14); printf("■■■■■\n");
	gotoxy(30, 15); printf("■\n");
	gotoxy(30, 16); printf("■\n");
	Sleep(300);
	system("cls");
	gotoxy(28, 11); printf("■■■■■\n");
	gotoxy(28, 12); printf("■\n");
	gotoxy(28, 13); printf("■\n");
	gotoxy(28, 14); printf("■■■■\n");
	gotoxy(28, 15); printf("■\n");
	gotoxy(28, 16); printf("■\n");
	Sleep(300);
	system("cls");
	gotoxy(26, 11); printf("■■■■■\n");
	gotoxy(26, 12); printf("■\n");
	gotoxy(26, 13); printf("■\n");
	gotoxy(26, 14); printf("■■■■\n");
	gotoxy(26, 15); printf("■\n");
	gotoxy(26, 16); printf("■\n");
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
	gotoxy(24, 11); printf("■■■■■\n");
	gotoxy(24, 12); printf("■\n");
	gotoxy(24, 13); printf("■\n");
	gotoxy(24, 14); printf("■■■■\n");
	gotoxy(24, 15); printf("■\n");
	gotoxy(24, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 17); printf("   /   ＼  |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 18); printf("    ------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 19); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 20); printf("   |      |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(44, 21); printf("    ------\n");
	Sleep(700);
	system("cls");
	gotoxy(22, 11); printf("■■■■■\n");
	gotoxy(22, 12); printf("■\n");
	gotoxy(22, 13); printf("■\n");
	gotoxy(22, 14); printf("■■■■\n");
	gotoxy(22, 15); printf("■\n");
	gotoxy(22, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(42, 17); printf("   /   ＼  |\n");
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
	gotoxy(20, 11); printf("■■■■■\n");
	gotoxy(20, 12); printf("■\n");
	gotoxy(20, 13); printf("■\n");
	gotoxy(20, 14); printf("■■■■\n");
	gotoxy(20, 15); printf("■\n");
	gotoxy(20, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(40, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); gotoxy(38, 17); printf("   /   ＼  |\n");
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
	gotoxy(18, 11); printf("■■■■■\n");
	gotoxy(18, 12); printf("■\n");
	gotoxy(18, 13); printf("■\n");
	gotoxy(18, 14); printf("■■■■\n");
	gotoxy(18, 15); printf("■\n");
	gotoxy(18, 16); printf("■\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 16); printf("    /＼    |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); gotoxy(38, 17); printf("   /   ＼  |\n");
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
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 03	|	DongGeun	|	신규(1교시)	|
*		|	2017. 06. 07	|	SeokRae		|	2 ~ 4교시	|
* @Description
*		게임로딩화면
*/
void loading(int stage) {

	switch (stage) {

	case 2:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■    ■■■■            ■■■■■■■■  ■■■■■■  ■■■■\n");
		gotoxy(11, 22); printf("■■■■■      ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■\n");
		gotoxy(11, 23); printf("■■■■■■    ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■\n");
		gotoxy(11, 26); printf("■■■■■■    ■■■                  ■■■■■■■■■■■■■  ■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
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
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("        ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("            ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("  ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("      ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		break;

	case 3:
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■\n");
		gotoxy(11, 23); printf("■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 25); printf("■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■\n");
		gotoxy(11, 23); printf("          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 25); printf("          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("        ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("            ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("  ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("      ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		break;
	case 4:
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■\n");
		gotoxy(11, 23); printf("■■          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 25); printf("■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("          ■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■  ■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■\n");
		gotoxy(11, 23); printf("          ■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■  ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 25); printf("          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■                  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■            ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("                  ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("        ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■  ■■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("            ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("  ■■■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("  ■■■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("      ■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■    ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■  ■  ■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("    ■    ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("  ■■■    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("  ■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("    ■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 27); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 24); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 25); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■  ■■■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■  ■■■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 23); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■  ■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		Sleep(300);
		system("cls");
		gotoxy(11, 20); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(11, 22); printf("■■■■  ■■■■■■■■            ■■■■■■■■  ■■■■■■  ■■■\n");
		gotoxy(11, 23); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■■  ■  ■■■■■  ■■■\n");
		gotoxy(11, 24); printf("■■■■  ■  ■■■■■■■■■■■  ■■■■■■    ■    ■■■■  ■■■\n");
		gotoxy(11, 25); printf("■■■■          ■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 26); printf("■■■■■■  ■■■■■■■  ■  ■■■■■■■    ■■■    ■■■  ■■■\n");
		gotoxy(11, 27); printf("■■■■■■  ■■■■■                  ■■■■■■■■■■■■■■■■■\n");
		Sleep(300);
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
	default :
		break;
	}
}
void mainMenu() {
	// 120 / 30
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(37, 10);
	cout << " - F 학점 피하기 - " << "\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(40, 12);
	cout << " 1. 게 임 시 작 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(40, 14);
	cout << " 2. 게 임 설 명 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(40, 16);
	cout << " 3. 게 임 종 료 " << "\n";
}

/**
* 스코어에 따라 학점 출력 함수
*/
void result() {

}

/**
* 게 임 설 명
*/
void description() {

}

static int score;
/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 01	|	SeokRae		|	신규		|
*		|	2017. 06. 05	|	DongGeun	|	라이프 추가 |
* @Description
*		게임 실행 함수
*/
void game(int stage) {
	//stageSetting(stage); // 난이도에 따른 콘솔창 조절 함수 호출
	loading(stage);
	int speed = 75 - stage * 15; // 난이도 조절

	int life = 3; //라이프
	
	if (stage == 2) { score = 101; }
	if (stage == 3) { score = 201; }
	if (stage == 4) { score = 301; }
	

	MOVEOBJECT mObj[100]; // 투사체와 사용자 구조체

	bool flag = true; // 게임 반복문에 대한 bool 변수

					  // [초기화] 유저 시작 위치 
	USER user = { 60, 25 };

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

					   // 일시정지
		if (_kbhit()) { // 키보드 눌렸는지 확인
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
		}
		// 사람 출력
		gotoxy(user.x, user.y);
		setColor(FOREGROUND_INTENSITY);
		cout << "ㅇ" << "\n";
		gotoxy(user.x, user.y + 1);
		cout << "■" << "\n";
		gotoxy(user.x, user.y + 2);
		cout << "||" << "\n";
		gotoxy(70, 2);
		cout << score;

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
				if (stage == 1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << "F";
				}
				if (stage == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "C";
				}
				if (stage == 3) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "B";
				}
				if (stage == 4) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "A";
				}
				// 투사체와 사용자의 머리 사이의 절대값이 2 보다 작고, y좌표값이 같을 경우 충돌
				if (abs(mObj[i].x - user.x) < 2 && (mObj[i].y == user.y)) {
					// 비프음 출력.
					cout << "\a";
					life--;
					if (life == 0) { //라이프가 0일때 게임종료
						gotoxy(90, 2);
						cout << "♡ ♡ ♡";
						flag = false;
					}

				}
				// **  스테이지 넘어가는 소스 필요

			} // if else 문 끝
			if (score == 100) { game(2); }
			if (score == 200) { game(3); }
			if (score == 300) { game(4); }
		}// for문 끝


	}
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 02	|	SeokRae		|	신규		|
* @Description
*		메인 메뉴에 해당하는 값만을 받기 위한 예외처리 함수
*/
char isCheckNum() {
	// cout << "isCheckNum()" << "\n";
	char checkNum = _getch();
	// cout << checkNum << "\n";
	// 메뉴의 숫자(1 ~ 3)외에 다른 숫자가 입력 될 경우 
	// 다시 입력하게끔 하지만 화면상 보이진 않음
	switch (checkNum) {
	case '1':
	case '2':
	case '3':
		return checkNum;
	default:
		return isCheckNum();
	}
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 02	|	SeokRae		|	신규		|
* @Description
*		메인 메뉴 선택 함수
*/
void controller() {
	int level = 1;

	char selectNum = isCheckNum(); // 1 ~ 3 이외에 값을 받을 경우 재귀 한다.
								   // selectNum = _getch(); // 키보드의 키 값을 입력 받아 char 변수에 저장
	switch (selectNum) {
	case '1': // 1. 게임 시작
		game(level);
		break;
	case '2': // 2. 게임 설명
		description(); // 게임 설명 함수 호출
		break;
	case '3': // 3. 게임 종료
		exit(0); // 시스템 종료 함수 호출
		break;
	default:
		break;
	}
}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용									|
*		|	2017. 06. 01	|	SeokRae		|	systemSetting(), mainMenu(), controller() 	|
*		|	2017. 06. 02	|	DongGeun	|	opening(), loading()						|
* @Description
*		메인 함수
*/
void main() {
	systemSetting();
	while (1) {
		//opening(); //오프닝화면
		//loading(); //로딩화면
		mainMenu(); // 메인 메뉴
		controller(); // 메뉴 선택 함수
	}
}