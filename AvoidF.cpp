#include <iostream>
#include <Windows.h> // 색깔
#include <conio.h> // _kbhit(), _getch() 함수
#include <stdlib.h> // exit() 함수의 헤더
// #include <time.h>  // Srand((unsigned int)time(NULL)) 하면 투사체가 이상하게 떨어짐

using namespace std;
/**
 * 투사체의 움직임을 관리 할 구조체
 */
typedef struct {
	int x		// x 좌표
		, y		// y 좌표
		, wait; // 대기시간
}MOVEOBJECT;

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
	// 120 / 30
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

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 01	|	SeokRae		|	신규		|
* @Description
*		게임 난이도에 따른 Console Setting
*		level 1 ~ 5 까지 설정
*/
void stageSetting(int level) {

	// 스테이지별 난이도 조절
	switch (level) {
	case 1:
		system("cls");
		system("mode con: cols=100 lines=30");
		system("Color 04");
		gotoxy(37, 10); cout << "F 학점을 피해라 !!" << "\n";
		Sleep(1500);
		break;
	case 2:
		system("cls");
		system("mode con: cols=120 lines=30");
		gotoxy(37, 10); cout << "D 학점을 피해라 !!" << "\n";
		Sleep(1500);
		break;
	case 3:
		system("cls");
		system("mode con: cols=140 lines=30");
		gotoxy(37, 10); cout << "C 학점을 피해라 !!" << "\n";
		Sleep(1500);
		break;
	case 4:
		system("cls");
		system("mode con: cols=160 lines=30");
		gotoxy(37, 10); cout << "B 학점을 피해라 !!" << "\n";
		Sleep(1500);
		break;
	case 5:
		system("cls");
		system("mode con: cols=180 lines=30");
		gotoxy(37, 10); cout << "A 학점을 피해라 !!" << "\n";
		Sleep(1500);
		break;
	default:
		break;
	}
}


/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	변경 내용	|
*		|	2017. 06. 01	|	SeokRae		|	신규		|
* @Description
*		게임 실행 함수
*/
void game(int stage) {
	stageSetting(stage); // 난이도에 따른 콘솔창 조절 함수 호출
	int life = 100; // 전체 라이프

	int speed = 75 - stage * 15; // 난이도 조절

	MOVEOBJECT mObj[100], user; // 투사체와 사용자 구조체
	
	bool flag = true; // 게임 반복문에 대한 bool 변수
	
	// 투사체 F학점 개수, 좌표, 대기 시간 [초기화]
	for (int i = 0; i < 50; i++) {
		mObj[i].x = rand() % 100 + 1;	// x좌표 1 ~ 100 까지 랜덤으로 생성한다.
		mObj[i].y = 0;					// y좌표 2에서 생성
		mObj[i].wait = rand() % 100;	// 생성 대기시간을 주어 한 줄로 떨어지지 않게 한다.
	}

	// 유저 시작 위치 [초기화]
	user.x = 60;
	user.y = 25;

	
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
		// 사람 움직임 처리
		if (isKeyState(VK_LEFT)) {
			if (user.x > 1)	{
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("ㅇ");
		gotoxy(user.x, user.y + 1);
		printf("ㅅ");
		gotoxy(user.x, user.y + 2);
		printf("ㅅ");


		for (int i = 0; i < 50; i++) { // * 50 투사체 개수 난이도에 따라 바꿔야 함
			// 대기 시간
			if (mObj[i].wait > 0) {
				// 대기 시간을 주어 한 줄로 투사체가 떨어지지 않도록 한다.
				mObj[i].wait--;
			} else {
				// 투사체를 한칸 아래로 이동한다.
				mObj[i].y++;
				// F 학점이 최하단에 도착 했을 때 처리.
				if (mObj[i].y >= 28) {
					mObj[i].x = rand() % 100 + 1;
					mObj[i].y = 3;
				}
				// F 학점 출력
				gotoxy(mObj[i].x, mObj[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				printf("F");

				// 투사체와 사용자의 머리 사이의 절대값이 2 보다 작고, y좌표값이 같을 경우 충돌
				if (abs(mObj[i].x - user.x) < 2 && mObj[i].y == user.y) {
					// 비프음 출력.
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
	default :
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
*		|	2017. 06. 		|				|	 											|
* @Description
*		메인 함수
*/
void main() {
	systemSetting(); 
	while (1) {
		mainMenu(); // 메인 메뉴
		controller(); // 메뉴 선택 함수
	}
}