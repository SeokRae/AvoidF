#include <iostream>
#include <fstream> // 파일 입출력 헤더
#include <string>
#include <Map>

using namespace std;

map<string, string> rankList;
map<string, string>::iterator i;


void fileInputStream() {
	string score;
	string name;
	ifstream in("rankList.txt");
	if (in.is_open()) {
		in >> score >> name;
		cout << "입력 받은 문자열 :: " << score << name << endl;
		
	}
	else {
		cout << "파일을 찾을 수 없습니다!" << endl;
	}
}

void fileOutputStream() {
	string s;
	

	ofstream fout;
	fout.open("rankList.txt");

	if (fout.is_open()) {
		cout << "파일 입력" << endl;
		for (i = rankList.begin(); i != rankList.end(); i++) {
			fout << i->first << " " << i->second << "\n";
			cout << i->first << " " << i->second << "\n";
		}
	}
	
}

void main() {
	string name;
	string score;
	
	getline(cin, score);
	getline(cin, name);

	pair<string, string> p(score, name);

	rankList.insert(p);
	
	fileOutputStream();

	fileInputStream();


}