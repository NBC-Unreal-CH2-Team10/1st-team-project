#pragma once

class Character;
class Shop;

#include "Monster.h"   //몬스터 클래스
#include "Goblin.h"
#include "BossMonster.h"
#include "Orc.h"
#include "Troll.h"
#include "MainArt.h"

class GameManager
{
public:
	Monster* generateMonster(int level);							//캐릭터 레벨을 받아서 몬스터의 레벨 설정
	Monster* generateBossMonster(int level);



	void battle(Character* player, Monster* monster);				//캐릭터 선공, 몬스터 후공으로 한번씩 공격
	void visitShop();			// 상점을 방문합니다.
	void manageInventory();			// 인벤토리를 확인하고 아이템을 사용합니다.
	void drawHealthbar(int hp, int maxHp, int barWidth);


	void playerUI(Character* player);
	void battleUI(Character* player, Monster* monster, int line);
	void setCursor(int x, int y);
	void drawMonsterArt(Monster* monster, int line);
	void drawShopArt(Shop* shop, int line);
	void drawDefeat(Character* player, int line);
	void drawMainArt(MainArt* mainart, int line);
	void printLog(const string& msg, int line);

	Character* player;
	Shop* shop;
};

