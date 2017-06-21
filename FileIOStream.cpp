#include <iostream>
#include <fstream> // ���� ����� ���
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
		cout << "�Է� ���� ���ڿ� :: " << score << name << endl;
		
	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}
}

void fileOutputStream() {
	string s;
	

	ofstream fout;
	fout.open("rankList.txt");

	if (fout.is_open()) {
		cout << "���� �Է�" << endl;
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