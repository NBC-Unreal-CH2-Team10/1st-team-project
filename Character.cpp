#include "Character.h"
#include <iostream>
#include <string>

using namespace std;

Character* Character::instance = nullptr;

Character::Character(string name) :
	name(name),
	level(1),
	health(300),
	maxHealth(300),
	attack(30),
	experience(0),
	gold(0)
{}

void Character :: displayStatus() const
{
	cout << "������������������������������������������������������������������";
	cout << endl;
	cout << "�̸� : " << name << "\n";
	cout << "Lv : " << level << "\n";
	cout << "����ġ : " << experience << "\n";
	cout << "HP : " << health << "/"<<maxHealth<< "\n";
	cout << "���ݷ� : " << attack;
	cout << endl;
	cout << "������������������������������������������������������������������";
}

void Character :: levelUp()
{
		experience -= 100;
		cout << endl;
		cout << "������ �߽��ϴ�!" << endl;
		++level;
		maxHealth += level * 20;
		health = maxHealth;
		cout << "ü���� ��� ȸ���ƽ��ϴ�.\n";
		attack += level * 5;
		cout << "���ݷ��� ����߽��ϴ�.\n";
		cout << "���� Lv : " << level << endl;
		cout << "���� ü�� :" << health << "/" << maxHealth << endl;
		cout << "���� ���ݷ� :" << attack << endl;
}

//void Character::useItem(int index)
//{

//}