#pragma once
#include <string>
#include <iostream>

using namespace std;

class DropItem {

private:
	string name;

public:
	//생성자
	DropItem(string& name) : name(name) {}

	string getName() const
	{
		return name;
	}
};

//몬스터 처치 보상 묶음
struct DropAll {
	DropItem* dropItem;
	int gold;
	int exp;

	DropAll(DropItem* dropItem, int gold, int exp)
		:dropItem(dropItem), gold(gold), exp(exp){}
};