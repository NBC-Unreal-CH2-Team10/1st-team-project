#include "Character.h"
#include <iostream>

using namespace std;

int main(void)
{
	string name;
	cout << "���ο� ������ �����մϴ�\n";
	cout << "����Ͻ� �г����� �ۼ����ּ��� : ";
	cin >> name;
	Character::getInstance(name);
	cout << name << "�� ȯ���մϴ�." << endl;
	

	Character::getInstance()->displayStatus();
	Character::getInstance()->levelUp();
	Character::getInstance()->displayStatus();

	return 0;
}