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

	vector<string> art;

public:
	BossMonster(int level);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;

	int getMaxHealth() const override;
	int getExp() const override;
	int getGold() const override;

	vector<string>& getArt();

	Item* dropItem() override;
};


