#include <iostream>
#include <Windows.h> // PlaySound();
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib");

#define sunsine "C:\\Users\\SeokRae\\Desktop\\Sunshine.wav"

using namespace std;

void sunshine() {
	// ���� ���� ��ġ, SND_ASYNC, SND_LOOP
	// SND_ASYNC : ����ϸ鼭 ���� �ڵ� ���� (�񵿱� ���)
	// SND_LOOP : �ݺ����
	PlaySound(TEXT(sunsine), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// http://hbesthee.tistory.com/76
void main() {
	
	// ���ǽ���
	sunshine();

	while (1) {
		int a; 
		printf("����");
		cin >> a;

		if (a == 0) {
			// ���� ����
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("�뷡�� ���� �߽��ϴ�. �Լ��� ����");
			return;
		}
	}
}