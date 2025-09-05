#include "GameManager.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

Monster* GameManager::generateMonster(int level)
{
	vector<Monster*> Monsterlist = { new Goblin(level), new Orc(level), new Troll(level) };
	
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<int> dis(0, 2);	// 0 ~ 2 사이에서 랜덤하게 숫자를 선택하고 몬스터리스트에 인덱스로 넣음

	return Monsterlist[dis(gen)];
}

Monster* GameManager::generateBossMonster(int level)
{
	return new BossMonster(level);
}

void GameManager::battle(Character* player, Monster* monster)  // 캐릭터/몬스터 순서로 한번씩 공격하고 둘 중 하나가 죽으면 break
{
	int curAttack = player->getAttack();	//현재 공격력
	int buffAttack = player->getAttack();	//포션 사용 후 공격력
	if (true) // 공격력 증가 포션의 개수 확인
	{
		string choice;
		cout << "공격력 강화 포션을 사용하시겠습니까? (Y/N)" << endl;
		cin >> choice;

		if (choice == "Y" || choice == "y")
		{
			buffAttack += 10; //공격력 강화 수치
			player->setAttack(buffAttack);
		}
	}
	while (player->getHealth() != 0 && monster->getHealth != 0) // attack 함수 제작?
	{
		cout << "전투를 시작합니다." << endl;
		
		monster->takeDamage(player->getAttack());				//몬스터가 먼저 공격 받음
		player->takeDamage(monster->getAttack());				//플레이어가 공격 받음

		if (player->getHealth() < (player->getMaxHealth() / 2))
		{
			//체력 포션 사용
			//체력 포션의 인덱스 필요
			int index = 0; 
			player->useItem(index);
		}
	}

	if (player->getHealth() == 0)
	{
		throw runtime_error("모험가가 사망했습니다.");
	}

	player->setAttack(curAttack); //공격력 원상 복구

	cout << "몬스터를 처치했습니다!" << endl;

	delete monster;
}

void GameManager::visitShop(Character* player)
{
	Shop* shop = new Shop();

	while (true)
	{
		int choice;
		//구매 혹은 판매 선택지 출력

		cout << "==================" << endl;
		cout << "1. 구매" << endl;
		cout << "2. 판매" << endl;
		cout << "3. 상점 나가기" << endl;
		cout << "==================" << endl;
		
		cin >> choice;

		if (choice == 1) //구매
		{
			int Itemchoice;
			cout << "상점 아이템 목록" << endl;

			shop.displayitems(); // 상점 아이템 리스트 출력

			cout << "어떤 아이템을 구매하시겠습니까?" << endl;

			cin >> Itemchoice;

			switch (Itemchoice)
			{
			case 1:
				shop->buyItem(0, player);
				break;
			case 2:
				shop->buyItem(1, player);
				break;
			case 3:
				shop->buyItem(2, player);
				break;
			default:
				break;
			}
		}
		else if (choice == 2) //판매
		{
			int Itemchoice;

			displayInventory(player);

			cout << "어떤 아이템을 판매하시겠습니까?" << endl;

			cin >> Itemchoice;  //인벤에 있는 아이템 개수를 어떻게 특정할 건지

			switch (Itemchoice)
			{
			case 1:
				shop->sellItem(0, player);
				break;
			case 2:
				shop->sellItem(1, player);
				break;
			default:
				break;
			}
		}
		else if (choice == 3)
		{
			string answer;

			cout << "상점을 나가시겠습니까? (Y/N)" << endl;
			cin >> answer;

			if (answer == "Y" || answer == "y")
			{
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	}

	delete shop;
}

void GameManager::displayInventory(Character* player)
{
	//캐릭터 클래스에서 getInventory 함수 필요
	// 아이템의 종류 뿐만 아니라 개수도 필요함 -> map 자료형 활용

	Item* item = player->getInventory();

	for (int i = 1; i <= player->getInventory().size(); ++i)
	{
		cout << i << ". " << item->first << ": " << item->second << endl;
	}
}
