#pragma once
#include <string>
#include <iostream>
#include "Monster.h"

using namespace std;

class BossMonster : public Monster {
private:
	string name;
	int health;
	int attack;
	int maxHealth;
	//int exp;
	//int gold;


public:
	BossMonster(int level);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;

	int getMaxHealth() const override;
	int getExp() const override;
	int getGold() const override;

	string getart() const;

	Item* dropItem() override;

private:
	string art = "임시 보스 이미지";
};


