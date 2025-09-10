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
	int maxHealth;
	int exp;
	int gold;

public:
	Troll(int level);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	
	int getExp() const override;
	int getMaxHealth() const override;
	int getGold() const override;

	vector<string>& getArt();
	
	Item* dropItem() override;

	string getart() const;

private:
	string art = /*u8R"(⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡔⢖⢒⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⢊⠖⣃⠖⣏⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠔⡪⠁⢤⣞⣶⡿⡟⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡠⢀⣀⢤⢊⢍⣬⡾⠟⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠤⢂⠊⢢⣠⣷⡿⠿⠛⠉⠀⢠⠒⠈⠉⠉⡐⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣀⣺⣜⢈⣵⢾⣥⢼⠀⠀⢀⡤⣴⠏⡐⠌⠐⠐⠠⣿⡟⣣⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠸⣠⣠⣾⣿⣿⣋⡥⠏⠀⡰⠘⢡⡯⣄⣠⢆⣥⣶⠆⣿⡼⣻⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠈⣸⡻⢿⣿⡏⠀⢀⣸⣅⢀⢨⣧⡜⡃⢩⠜⠂⢲⢿⣧⣿⣇⡀⠙⠒⢤⠀⠀⠀⠀⠀⠀⠀
⠀⢀⡗⠁⠈⡇⣻⡔⠁⠁⠈⣾⠈⣿⣖⢯⣷⣽⢧⡳⣺⣿⡯⠊⠈⠠⠁⠈⣷⠀⠀⠀⠀⠀⠀
⠀⠨⣇⡀⠄⢀⢪⡧⣀⣨⣴⣿⡇⢛⣯⠽⠜⠮⢬⣸⣿⡏⢳⠄⢀⠄⠀⢡⣺⣅⠀⠀⠀⠀⠀
⠀⠀⢹⠷⣤⣴⡿⣝⣽⣽⠿⠋⢳⡀⠸⢷⣾⣾⣿⡏⠃⠑⡢⢭⣦⣶⣔⣑⡾⠉⢣⠀⠀⠀⠀
⠀⠀⠀⠛⠛⠛⠙⠁⠀⠀⠀⠀⠸⡛⠓⠛⠻⠿⢥⣀⣤⣵⢾⣿⣿⣆⠀⠀⢡⢠⠘⢧⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠃⠈⠀⠀⠐⠀⢠⢀⠄⢞⢽⣿⡟⠷⣔⣾⠃⠀⣸⣟⡆⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣜⠄⣨⡀⠀⠂⡀⠄⣤⣱⣯⣿⣷⠀⢸⢫⠀⠂⡱⢹⣧⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣨⣷⢹⢷⣮⣍⣠⣄⣖⡿⡟⣻⢭⣽⣿⡗⠘⢾⡊⠀⢀⣧⡇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠞⠁⠈⢿⡹⣮⣿⣽⢾⢗⣿⡫⠁⠀⢙⣿⡧⢀⡸⠄⠐⢔⡿⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢠⡏⢀⠂⠀⢽⣧⡣⡓⠶⢫⢱⡏⡂⠀⠠⡰⠛⣁⣅⠆⠜⡤⡈⣿⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⣆⣠⣼⣿⠟⠧⡂⡐⢼⣾⣷⡄⡂⣎⢠⣿⠈⡹⢀⢼⡆⢸⠸⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠘⣷⣿⣿⣿⣿⡇⠀⢹⢄⡿⠙⠀⢻⣦⣔⣾⣿⣷⡣⡸⠉⡇⢸⢧⡵⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣿⣇⠀⠀⠈⠇⠀⠀⠘⣿⣻⣿⣿⣿⠊⠀⡮⣴⢓⠟⠁⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠞⡿⢿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⢙⣿⣿⣿⡇⠈⠈⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⡴⡏⡧⠒⢀⣠⡿⠟⠛⠋⠀⠀⠀⠀⠀⠀⠀⢈⠟⠟⠫⠻⣆⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠙⠸⠚⠞⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀  ⠀⠀⠀⣿⠐⢱⣅⢵⢸⣸⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀      ⠀⠀⠈⠛⠀⠘⠊⠙⠀⠀⠀⠀⠀⠀⠀⠀
)";*/ u8R"(troll)";
};

