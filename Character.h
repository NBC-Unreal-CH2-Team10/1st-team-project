#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Character
{
private:
	static Character* instance;
	Character(std::string name);
	std::string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int gold;
	int killcount;
	std::vector <Item*> inventory;

public:
	static Character* getInstance(std::string name = "")
	{
		if (instance == nullptr)
		{
			instance = new Character(name);
		}
		return instance;
	}

	void displayStatus() const;
	void levelUp();
	// Attack
	int getAttack();
	void setAttack(int buffAttack);

	// Health
	int getHealth();
	void setHealth(int a);

	// MaxHealth
	int getMaxHealth();

	// Gold
	void setGold(int a);
	int getGold();

	// Exp
	int getExp();
	void setExp(int a);

	// Item
	void useItem(int index);

	// inventory
	void addInventory(Item* item);		// inventory ∫§≈Õø° »πµÊ æ∆¿Ã≈€ ≥÷±‚

	vector<Item*> getInventory();

	// monster
	void takeDamage(int a);
	int getKillcount();
	void setKillcount(int a);

	// Level
	int getLevel();

	// Name
	std::string getName();

};
