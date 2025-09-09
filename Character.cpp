#include "Character.h"
#include <iostream>
#include <string>

Character* Character::instance = nullptr;

Character::Character(std::string name) :
	name(name),
	level(1),
	
	health(100),
	maxHealth(100),
	attack(5),
	experience(0),
	gold(0),
	killcount(0)

{
	inventory = new Inventory();
}

Character::~Character()
{
	delete inventory;
	inventory = nullptr;
}

void Character :: displayStatus() const
{
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
	std::cout << std::endl;
	std::cout << "이름 : " << name << "\n";
	std::cout << "Lv : " << level << "\n";
	std::cout << "경험치 : " << experience << "\n";
	std::cout << "HP : " << health << "/"<<maxHealth<< "\n";
	std::cout << "공격력 : " << attack;
	std::cout << std::endl;
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
}

void Character :: levelUp()
{
		experience -= 100;
		std::cout << std::endl;
		std::cout << "레벨업 했습니다!" << std::endl;
		++level;
		maxHealth += level * 20;
		health = maxHealth;
		std::cout << "체력이 모두 회복됐습니다.\n";
		attack += level * 5;
		std::cout << "공격력이 상승했습니다.\n";
		std::cout << "현재 Lv : " << level << std::endl;
		std::cout << "현재 체력 :" << health << "/" << maxHealth << std::endl;
		std::cout << "현재 공격력 :" << attack << std::endl;
}

int Character::getAttack()
{
	return attack;
}

void Character::setAttack(int buffAttack)
{
	attack = buffAttack;
	return ;
}

int Character::getHealth()
{
	return health;
}

void Character::setHealth(int a)
{
	health = a;
	return ;
}

int Character::getMaxHealth()
{
	return maxHealth;
}

void Character::setGold(int a)
{
	gold = a;
	return;
}

int Character::getExp()
{
	return experience;
}

void Character::setExp(int a)
{
	experience = a;
	return;
}

void Character::useItem(int index)
{

	return;
}

void Character::addInventory(Item* item)
{
    inventory->addItem(item);
}

void Character::takeDamage(int a)
{
	health -= a;
	return;
}

int Character::getGold()
{
	return gold;
}

int Character::getLevel()
{
	return level;
}

std::string Character::getName()
{
	return name;
}

int Character :: getKillcount()
{
	return killcount;
}

void Character::setKillcount(int a)
{
	killcount = a;
	return ;
}

std::string Character::getart() { return art; }