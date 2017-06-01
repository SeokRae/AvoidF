#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

typedef struct MOVEOBJECT {
	int x		// x 좌표
		, y		// y 좌표
		, wait; // 대기시간
}MOVEOBJECT;

// 화면의 특정 위치로 이동해 주는 함수.
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x - 1;
	Pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 키입력 함수
BOOL isKeyState(int Key) {
	// http://seokr.tistory.com/473
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
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
 * 메인 메뉴 화면
 */
void mainMenu() {
	// 100 / 30
	gotoxy(37, 10);
	cout << " - F 학점 피하기 - " << "\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(40, 12);
	cout << " 게 임 시 작 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(40, 14);
	cout << " 게 임 설 명 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(40, 16);
	cout << " 게 임 종 료 " << "\n";
}
/**
 * 게 임 설 명
 */
void description() {

}

/**
* 게임 알고리즘 함수
*/
void game(int stage) {

	// 스테이지별 난이도 조절
	switch (stage) {
	case 2:
		system("mode con: cols=120 lines=30");
		break;
	}

	// 배경색 흰색(F)에 폰트 검은색(0)
	system("Color F0");
	int speed = 100 - stage * 15;
	MOVEOBJECT fallingObject[100];


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x00); // 바닥 검정색 
	printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ");
	printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ");

	// 투사체 F학점 좌표 및 대기 시간 초기화
	for (int i = 0; i < 100; i++) {
		fallingObject[i].x = rand() % 120 + 1;	// x좌표 1 ~ 100 까지 랜덤으로 생성한다.
		fallingObject[i].y = 0;					// y좌표 2에서 생성
		fallingObject[i].wait = rand() % 100;	// 생성 대기시간을 주어 한 줄로 떨어지지 않게 한다.
	}

	while (1) {

		Sleep(speed); // Sleep() 함수를 통해 속도 조절
		system("cls");

		for (int i = 0; i < 100; i++) {
			// 대기 시간
			if (fallingObject[i].wait > 0)
			{
				// 대기시간 동안 아직 똥을 떨어뜨리지 않는다.
				fallingObject[i].wait--;
			}
			else {
				// F 학점을 한칸 아래로 이동한다.
				fallingObject[i].y++;
				// F 학점이 최하단에 도착 했을 때 처리.
				if (fallingObject[i].y >= 28) {
					fallingObject[i].x = rand() % 120 + 1;
					fallingObject[i].y = 3;
				}
				// F 학점 출력
				gotoxy(fallingObject[i].x, fallingObject[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("F");
			}
		}

	}
}
/**
 * 메인 메뉴 선택 함수
 */
void controller() {
	
}


void main() {
	systemSetting(); 
	mainMenu(); // 메인 메뉴
	controller(); // 메뉴 선택 함수
}