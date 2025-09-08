#pragma once
#include <string>
#include <iostream>
#include "Monster.h"

using namespace std;

class Orc : public Monster {
private:
	string name;
	int health;
	int attack;
	int maxHealth;
	int exp;
	int gold;

public:
	Orc(int level);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	
	int getMaxHealth() const override;
	int getExp() const override;
	int getGold() const override;

	DropItem* dropItem() override;
};

