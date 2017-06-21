#include <iostream>
#include <Windows.h> // PlaySound();
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib");

#define sunsine "C:\\Users\\SeokRae\\Desktop\\Sunshine.wav"

using namespace std;

void sunshine() {
	// 사운드 파일 위치, SND_ASYNC, SND_LOOP
	// SND_ASYNC : 재생하면서 다음 코드 실행 (비동기 모드)
	// SND_LOOP : 반복재생
	PlaySound(TEXT(sunsine), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// http://hbesthee.tistory.com/76
void main() {
	
	// 음악실행
	sunshine();

	while (1) {
		int a; 
		printf("종료");
		cin >> a;

		if (a == 0) {
			// 음악 끄기
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("노래를 종료 했습니다. 함수도 종료");
			return;
		}
	}
}