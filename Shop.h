#pragma once
#include <vector>
#include "item.h"

using namespace std;

class Character;

// 상점 클래스 설계
class Shop
{
private:
	vector<Item*> availableItems; // 상점이 판매하는 아이템 목록

	void displayBuyMenu(Character* player);
	void displaySellMenu(Character* player);

public:
	Shop();
	~Shop();

	void enter(Character* player); // 플레이어가 상점에 입장시 호출
};