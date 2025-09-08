#pragma once
#include <string>
#include <iostream>
#include "Monster.h"

using namespace std;

class Troll : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Troll(int level);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	DropAll* dropAll() override;
};

