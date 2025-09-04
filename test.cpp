#include "Character.h"
#include <iostream>

using namespace std;

int main(void)
{
	string name;
	cout << "새로운 게임을 시작합니다\n";
	cout << "사용하실 닉네임을 작성해주세요 : ";
	cin >> name;
	Character::getInstance(name);
	cout << name << "님 환영합니다." << endl;
	

	Character::getInstance()->displayStatus();
	Character::getInstance()->levelUp();
	Character::getInstance()->displayStatus();

	return 0;
}