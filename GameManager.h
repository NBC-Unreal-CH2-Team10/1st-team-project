#pragma once

#include "Character.h" //캐릭터 클래스
#include "Shop.h"      //상점 클래스
#include "Monster.h"   //몬스터 클래스

class GameManager
{
public:
	Monster* generateMonster(int level);							//캐릭터 레벨을 받아서 몬스터의 레벨 설정
	Monster* generateBossMonster();

	void battle(Character* player, Monster* monster);				//캐릭터 선공, 몬스터 후공으로 한번씩 공격
	void visitShop(Character* player);								//캐릭터가 상점 방문
	void displayInventory(Character* player);						//캐릭터 인벤토리 확인
};

