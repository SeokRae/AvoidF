#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;
/**
 * 燈紫端税 崇送績聖 淫軒 拝 姥繕端
 */
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
	// 徹左球税 徹亜 喚携澗走 端滴馬澗 敗呪
	// GetAsyncKeyState()澗 搾 疑奄坦軒 敗呪
	// GetAsyncKeyState()澗 徹亜 喚形遭 獣繊拭辞 0x8000 葵聖 軒渡 - 薄仙 徹亜 喚形遭 雌殿
	// 敗呪亜 硲窒鞠醸聖 凶 徹亜 喚形閃 赤醸陥壱 0x0001 葵聖 軒渡 - 走貝腰 硲窒引 戚腰 硲窒 紫戚拭 徹亜 喚形遭 旋戚 赤醸陥澗 妊薄
	// 聡, 舛溌廃 獣繊拭辞 徹喚顕 雌殿研 端滴 馬奄 是背辞 0x8000生稽 AND 尻至聖 背 爽澗 依戚陥.
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
	// 120 / 30
	gotoxy(37, 10);
	cout << " - F 俳繊 杷馬奄 - " << "\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(40, 12);
	cout << " 1. 惟 績 獣 拙 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(40, 14);
	cout << " 2. 惟 績 竺 誤 " << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(40, 16);
	cout << " 3. 惟 績 曽 戟 " << "\n";
}
/**
 * 惟 績 竺 誤
 */
void description() {

}
/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	痕井 鎧遂	|
*		|	2017. 06. 01	|	SeokRae		|	重鋭		|
* @Description
*		惟績 貝戚亀 繕箭 敗呪
*/
void changeStage(int level) {

	// 什砺戚走紺 貝戚亀 繕箭
	switch (level) {
	case 1:
		system("cls");
		system("mode con: cols=100 lines=30");
		gotoxy(37, 10); cout << "F 俳繊聖 杷背虞 !!" << "\n";
		Sleep(1500);
		break;
	case 2:
		system("mode con: cols=120 lines=30");
		gotoxy(37, 10); cout << "D 俳繊聖 杷背虞 !!" << "\n";
		Sleep(1500);
		break;
	case 3:
		system("mode con: cols=140 lines=30");
		gotoxy(37, 10); cout << "C 俳繊聖 杷背虞 !!" << "\n";
		Sleep(1500);
		break;
	case 4:
		system("mode con: cols=160 lines=30");
		gotoxy(37, 10); cout << "B 俳繊聖 杷背虞 !!" << "\n";
		Sleep(1500);
		break;
	case 5:
		system("mode con: cols=180 lines=30");
		gotoxy(37, 10); cout << "A 俳繊聖 杷背虞 !!" << "\n";
		Sleep(1500);
		break;
	default:
		break;
	}
}


/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	痕井 鎧遂	|
*		|	2017. 06. 01	|	SeokRae		|	重鋭		|
* @Description
*		惟績 叔楳 敗呪
*/
void game(int stage) {
	// 壕井事 避事(F)拭 肉闘 伊精事(0)
	system("Color F0");
	int speed = 75 - stage * 15; // 貝戚亀 繕箭

	changeStage(stage); // 貝戚亀拭 魚献 嬬車但 繕箭 敗呪 硲窒
	
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
		system("cls"); // 鉢檎 走酔奄

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
// 収切幻 閤亀系 馬澗 仙瑛敗呪
char isCheckNum() {
	cout << "isCheckNum()" << "\n";
	char checkNum = _getch();
	cout << checkNum << "\n";
	// 五敢税 収切(1 ~ 3)須拭 陥献 収切亜 脊径 吃 井酔 
	// 陥獣 脊径馬惟懐 馬走幻 鉢檎雌 左戚遭 省製
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
 *		|	Date			|	Author		|	痕井 鎧遂	|
 *		|	2017. 06.		|				|	重鋭		|
 * @Description
 *		五昔 五敢 識澱 敗呪
 */
void controller() {
	int level = 1;
	char selectNum = isCheckNum(); // 1 ~ 3 戚須拭 葵聖 閤聖 井酔 仙瑛 廃陥.
	cout << "selectNum : " << selectNum << "\n";
//	selectNum = _getch(); // 徹左球税 徹 葵聖 脊径 閤焼 char 痕呪拭 煽舌
	while (1) {
		switch (selectNum) {
		case '1': // 1. 惟績 獣拙
			selectNum = 0;
			game(level);
			break;
		case '2': // 2. 惟績 竺誤
			description(); // 惟績 竺誤 敗呪 硲窒
			break;
		case '3': // 3. 惟績 曽戟
			break;
		default:
			break;
		}
	}

}

/**
* @author SeokRae
* @History
*		|	Date			|	Author		|	痕井 鎧遂									|
*		|	2017. 06. 01	|	SeokRae		|	systemSetting(), mainMenu(), controller() 	|
*		|	2017. 06. 		|				|	 											|
* @Description
*		五昔 敗呪
*/
void main() {
	systemSetting(); 
	mainMenu(); // 五昔 五敢
	controller(); // 五敢 識澱 敗呪
}