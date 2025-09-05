#include "GameManager.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
using std::cout;

Monster* GameManager::generateMonster(int level)
{
	vector<Monster*> Monsterlist = { new Goblin(level), new Orc(level), new Troll(level) }; //한번에 다 받는 방법?
	
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
	vector<Item*> inventory = player->getInventory();

	string find = "AttackBoost";

	auto it = inventory.find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // 공격력 증가 포션이 존재하는지 확인

	if (it != inventory.end()) 
	{
		string choice;

		while (true)
		{
			cout << "공격력 강화 포션을 사용하시겠습니까? (Y/N)\n" << endl;
			cin >> choice;

			if (cin.fail()) //잘 못된 타입이 입력되면 true 반환
			{
				cin.clear(); // 오류 상태 초기화
				cin.ignore(1000, '\n'); // 잘못된 입력 버리기
				cout << "잘못된 입력입니다. 다시 입력해주세요.\n" << endl;
				continue;
			}

			if (choice == "Y" || choice == "y")
			{
				inventory[it - inventory.begin()]->use(player);
				break;
			}
			else
			{
				break;
			}
		}
	}
	while (player->getHealth() != 0 && monster->getHealth != 0) // attack 함수 제작?
	{
		cout << "전투를 시작합니다.\n" << endl;
		
		monster->takeDamage(player->getAttack());				//몬스터가 먼저 공격 받음
		player->takeDamage(monster->getAttack());				//플레이어가 공격 받음

		string find = "HealthPotion";

		auto it = inventory.find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // 체력 포션이 존재하는지 확인

		if (it != inventory.end())
		{
			if (player->getHealth() < (player->getMaxHealth() / 2)) //최대 체력의 50% 아래로 내려갈 경우 자동 사용
			{
				//체력 포션 사용
				inventory[it - inventory.begin()]->useItem(player);
			}
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
		system("clear"); //콘솔 화면 지우기

		int choice;
		//구매 혹은 판매 선택지 출력

		cout << "==================" << endl;
		cout << "1. 구매" << endl;
		cout << "2. 판매" << endl;
		cout << "3. 상점 나가기" << endl;
		cout << "==================\n" << endl;
		
		cin >> choice;

		if (choice == 1) //구매
		{
			while (true)
			{
				int Itemchoice;

				cout << "===상점 아이템 목록===" << endl;

				vector<Item*> shoplist = shop.displayitems(); //vector<Item*>을 받기
															  //구매 창에서 상점 초기 화면으로 나가기 위해 0번으로 뒤로가기 item* 추가

				cout << "0" << ". " << shoplist[0]->getName() << endl;  //뒤로가기 출력

				for (int i = 1; i <= shoplist.size(); ++i)	//상점 아이템 리스트 출력, displayitems에서 구현하는 것이 좋아보임
				{
					cout << i << ". " << shoplist[i]->getName() << ": " << shoplist[i]->getPrice() << "골드" << endl;
				}

				cout << "어떤 아이템을 구매하시겠습니까?" << endl;

				cin >> Itemchoice; //숫자로 받기 혹은 string으로 아이템 이름으로 받기

				if (cin.fail()) //잘 못된 타입이 입력되면 true 반환
				{
					cin.clear(); // 오류 상태 초기화
					cin.ignore(1000, '\n'); // 잘못된 입력 버리기
					cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
					continue; 
				}

				if (Itemchoice != 0)
				{
					shop->buyItem(Itemchoice, player); //Itemchoice로 상점에 있는 아이템 vector의 인덱스로 구매
					continue;
				}
				else
				{
					break; //0번 뒤로가기 선택시 상점 초기화면으로 돌아가기
				}
			}
		}
		else if (choice == 2) //판매
		{
			while (true)
			{
				int Itemchoice;

				displayInventory(player);

				cout << "어떤 아이템을 판매하시겠습니까?" << endl;

				cin >> Itemchoice;

				if (cin.fail()) //잘 못된 타입이 입력되면 true 반환
				{
					cin.clear(); // 오류 상태 초기화
					cin.ignore(1000, '\n'); // 잘못된 입력 버리기
					cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
					continue;
				}

				if (Itemchoice != 0)
				{
					shop->sellItem(Itemchoice, player); //Itemchoice로 인벤에 있는 아이템 vector의 인덱스로 판매
					continue;
				}
				else
				{
					break; //0번 뒤로가기 선택시 상점 초기화면으로 돌아가기
				}
			}
		}
		else if (choice == 3)
		{
			string answer;

			cout << "상점을 나가시겠습니까? (Y/N)" << endl;
			cin >> answer;

			if (cin.fail()) //잘 못된 타입이 입력되면 true 반환
			{
				cin.clear(); // 오류 상태 초기화
				cin.ignore(1000, '\n'); // 잘못된 입력 버리기
				cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
				continue;
			}

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
			cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
			continue;
		}
	}
	delete shop;
}

void GameManager::displayInventory(Character* player)
{
	//캐릭터 클래스에서 getInventory 함수 필요
	// 아이템의 종류 뿐만 아니라 개수도 필요함 -> map 자료형 활용

	vector<Item*> item = player->getInventory(); //캐릭터 인벤에도 0번으로 뒤로가기 넣기

	cout << "0" << ". " << item[0]->getName() << endl;  //뒤로가기 출력
	
	for (int i = 1; i <= item.size(); ++i)
	{
		cout << i << ". " << item[i]->getName() << ": " << item[i]->getPrice() << "골드" << endl; //여기서 price는 상점에서 판매시 가격
	}
}

void GameManager::drawHealthbar(int hp, int maxHp, int barWidth = 10) 
{
	// 체력 비율 계산
	double ratio = (double)hp / maxHp;
	int filled = (int)(ratio * barWidth);

	cout << "[";
	for (int i = 0; i < barWidth; i++) {
		if (i < filled) cout << "*";  // 체력이 있는 부분
		else cout << " ";             // 체력이 없는 부분
	}
	cout << "] ";
}
