#pragma once
#include <string>
#include <vector>


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
	//std::vector <Item*> inventory;

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

	//void useItem(int index);

};
