#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

typedef struct MOVEOBJECT {
	int x		// x 疎妊
		, y		// y 疎妊
		, wait; // 企奄獣娃
}MOVEOBJECT;

// 鉢檎税 働舛 是帖稽 戚疑背 爽澗 敗呪.
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x - 1;
	Pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 徹脊径 敗呪
BOOL isKeyState(int Key) {
	// http://seokr.tistory.com/473
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

/**
 * 嬬車 鉢檎 繕箭 敗呪
 */
void systemSetting() {

	// 1. 嬬車 鉢檎 繕箭
	// Colums 100 Lines 30税 鋭維生稽 馬澗 嬬車聖 叔楳廃陥.
	system("mode con: cols=100 lines=30");

	// 2. 展戚堂 痕井
	system("title F 俳繊 杷馬奄 惟績 (薦拙切 : 沿殿精, 沿汐掘, 酵疑悦)");

	// 3. 嬬車 鉢檎 事 郊荷奄
	system("Color 0B");

}

/**
 * 五昔 五敢 鉢檎
 */
void mainMenu() {
	// 100 / 30
	gotoxy(37, 10);
	cout << " - F 俳繊 杷馬奄 - " << "\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(40, 12);
	cout << " 惟 績 獣 拙 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(40, 14);
	cout << " 惟 績 竺 誤 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(40, 16);
	cout << " 惟 績 曽 戟 " << "\n";
}
/**
 * 惟 績 竺 誤
 */
void description() {

}

/**
* 惟績 硝壱軒葬 敗呪
*/
void game(int stage) {

	// 什砺戚走紺 貝戚亀 繕箭
	switch (stage) {
	case 2:
		system("mode con: cols=120 lines=30");
		break;
	}

	// 壕井事 避事(F)拭 肉闘 伊精事(0)
	system("Color F0");
	int speed = 100 - stage * 15;
	MOVEOBJECT fallingObject[100];


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x00); // 郊韓 伊舛事 
	printf("けけけけけけけけけけけけけ");
	printf("けけけけけけけけけけけけけ");

	// 燈紫端 F俳繊 疎妊 貢 企奄 獣娃 段奄鉢
	for (int i = 0; i < 100; i++) {
		fallingObject[i].x = rand() % 120 + 1;	// x疎妊 1 ~ 100 猿走 沓棋生稽 持失廃陥.
		fallingObject[i].y = 0;					// y疎妊 2拭辞 持失
		fallingObject[i].wait = rand() % 100;	// 持失 企奄獣娃聖 爽嬢 廃 匝稽 恭嬢走走 省惟 廃陥.
	}

	while (1) {

		Sleep(speed); // Sleep() 敗呪研 搭背 紗亀 繕箭
		system("cls");

		for (int i = 0; i < 100; i++) {
			// 企奄 獣娃
			if (fallingObject[i].wait > 0)
			{
				// 企奄獣娃 疑照 焼送 極聖 恭嬢襟軒走 省澗陥.
				fallingObject[i].wait--;
			}
			else {
				// F 俳繊聖 廃牒 焼掘稽 戚疑廃陥.
				fallingObject[i].y++;
				// F 俳繊戚 置馬舘拭 亀鐸 梅聖 凶 坦軒.
				if (fallingObject[i].y >= 28) {
					fallingObject[i].x = rand() % 120 + 1;
					fallingObject[i].y = 3;
				}
				// F 俳繊 窒径
				gotoxy(fallingObject[i].x, fallingObject[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("F");
			}
		}

	}
}
/**
 * 五昔 五敢 識澱 敗呪
 */
void controller() {
	
}


void main() {
	systemSetting(); 
	mainMenu(); // 五昔 五敢
	controller(); // 五敢 識澱 敗呪
}