#include "GameManager.h"
#include "Shop.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>
#include <sstream>

Monster* GameManager::generateMonster(int level)
{
	std::vector<Monster*> Monsterlist = { new Goblin(level), new Orc(level), new Troll(level) }; //한번에 다 받는 방법?
	
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution<int> dis(0, 2);	// 0 ~ 2 사이에서 랜덤하게 숫자를 선택하고 몬스터리스트에 인덱스로 넣음

	return Monsterlist[dis(gen)];
}

Monster* GameManager::generateBossMonster(int level)
{
	return new BossMonster(level);
}

void GameManager::battle(Character* player, Monster* monster)  // 캐릭터/몬스터 순서로 한번씩 공격하고 둘 중 하나가 죽으면 break
{
	int curAttack = player->getAttack();	//현재 공격력
	std::vector<Item*> inventory;
	for (const auto& slot : player->getInventory()->getSlots())
	{
		inventory.push_back(slot.item);
	}

	std::string find = "AttackBoost";

	auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // 공격력 증가 포션이 존재하는지 확인

	if (it != inventory.end()) 
	{
		std::string choice;

		while (true)
		{
			std::cout << "공격력 강화 포션을 사용하시겠습니까? (Y/N)\n" << std::endl;
			std::cin >> choice;

			if (std::cin.fail()) //잘 못된 타입이 입력되면 true 반환
			{
				std::cin.clear(); // 오류 상태 초기화
				std::cin.ignore(1000, '\n'); // 잘못된 입력 버리기
				std::cout << "잘못된 입력입니다. 다시 입력해주세요.\n" << std::endl;
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

	std::cout << "전투를 시작합니다!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //1초 딜레이


	int logline = 45; 
	int battlelog = logline + 10;
	int delay = 500; 

	system("cls");
	
	while (true) // attack 

	{
		playerUI(player);  //커서 맨위로 이동 후 1줄짜리 UI 출력


		drawMonsterArt(monster, 5); 


		printLog(monster->getName() + "이(가) 나타났습니다!", logline);
		
		battleUI(player, monster, logline + 4);

		monster->takeDamage(player->getAttack());				//몬스터가 먼저 공격 받음
		playerUI(player);

		battleUI(player, monster, logline + 4);
		printLog("모험가가"+ std::to_string(player->getAttack()) + "의 피해를 입혔습니다.", battlelog);
		++battlelog;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		if (player->getHealth() == 0 || monster->getHealth() == 0)
		{
			break;
		}

		player->takeDamage(monster->getAttack());				
		playerUI(player);
		battleUI(player, monster, logline + 4);
		printLog("몬스터가 " + std::to_string(monster->getAttack()) + "의 피해를 입혔습니다.", battlelog);

		++battlelog;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		if(player->getHealth() == 0 || monster->getHealth() == 0)
		{
			break;
		}

		if (player->getHealth() < (player->getMaxHealth() / 2)) //최대 체력의 50% 아래로 내려갈 경우 자동 사용
		{
			std::string find = "체력 물약";

			auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // 체력 포션이 존재하는지 확인

			if (it != inventory.end())
			{
				//체력 포션 사용
				inventory[it - inventory.begin()]->use(player);
				playerUI(player);
				battleUI(player, monster, logline);
				printLog("체력 포션을 사용하여 50의 체력을 회복했습니다!", battlelog);
				++battlelog;
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
		}
		++battlelog;
	}

	if (player->getHealth() == 0)
	{
		throw std::runtime_error("모험가가 사망했습니다.");
	}

	player->setAttack(curAttack); //공격력 원상 복구

	player->setKillcount(player->getKillcount() + 1);  //몬스터 킬수 +1
	player->setGold(monster->getGold() + player->getGold());

	playerUI(player);
	battleUI(player, monster, logline);
	printLog("몬스터를 처치했습니다!", logline + 10);

	//몬스터 처치 -> 경험치와 골드 아이템 획득

	//골드 획득
	//몬스터마다 골드 다르게 하고 dropGold 같은 함수로 드랍 골드 확인
	//플레이어에 addGold 함수로 골드 추가, 골드 획득 문구 출력

	std::cout << monster->getGold() << "골드를 획득했습니다." << std::endl;

	player->addInventory(monster->dropItem());

	//드랍 아이템이 있는지 확인하고 있으면 인벤에 추가 없으면 넘어가기

	delete monster;
}

void GameManager::visitShop()
{

	Shop* shop = new Shop();

	int logline = 20; 

	while (true)
	{
		system("cls"); 

		playerUI(player);

		drawShopArt(shop, 2);

		int choice;
		
		printLog("==================", logline);
		printLog("1. 구매", logline + 1);
		printLog("2. 판매", logline + 2);
		printLog("3. 상점 나가기", logline + 3);
		printLog("==================", logline + 4);
		
		std::cout << "번호를 입력하세요: ";

		std::cin >> choice;
		std::cin.ignore(1000, '\n');

		if (std::cin.fail()) 
		{
			std::cin.clear(); 
			std::cin.ignore(1000, '\n'); 
			std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
			continue;
		}

		if (choice == 1) 
		{
			while (true) {
				system("cls");

				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->buyLoop(player);

				if (choice == 0) break;       
				if (choice == -1) 
				{
					printLog("잘못된 선택입니다. 다시 선택해세요.", logline + 10);									
					std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
					continue;
				}

				
				setCursor(0, logline + 10);
				shop->buyItem(choice - 1, player);
			}
		}
		else if (choice == 2) 
		{
			while (true)
			{
				system("cls");

				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->sellLoop(player);

				if (choice == 0) break;       
				if (choice == -1)
				{
					printLog("잘못된 선택입니다. 다시 입력해주세요.", logline + 10);									
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					continue;
				}
				else if (choice == -2)
				{
					printLog("판매할 아이템이 없습니다.", logline + 10);
					break;
				}



				shop->sellItem(choice - 1, player);
				printLog("아이템을 판매했습니다.", logline + 10);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
			}
		}
		else if (choice == 3)
		{
			std::string answer;

			std::cout << "상점을 나가시겠습니까? (Y/N)" << std::endl;
			std::cin >> answer;
			std::cin.ignore(1000, '\n');

			if (std::cin.fail()) //잘 못된 타입이 입력되면 true 반환
			{
				std::cin.clear(); // 오류 상태 초기화
				std::cin.ignore(1000, '\n'); // 잘못된 입력 버리기
				std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
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
			std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
			continue;
		}
	}
	delete shop;
}

void GameManager::manageInventory()
{
	player->getInventory()->manage(player);
}

void GameManager::drawHealthbar(int hp, int maxHp, int barWidth = 10)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	double ratio = (double)hp / maxHp;
	int filled = (int)(ratio * barWidth);

	std::cout << "[";

	for (int i = 0; i < barWidth; i++)
	{
		if (i < filled) {
			SetConsoleTextAttribute(hConsole, 10); // 10 = 초록색
			std::cout << u8"■";
		}
		else {
			SetConsoleTextAttribute(hConsole, 7); // 12 = 빨간색
			std::cout << u8"-";  // 빈 칸도 □ 대신 색칠된 ■로 통일 가능
		}
	}

	SetConsoleTextAttribute(hConsole, 7); // 기본 색상으로 복구
	std::cout << "] ";

	SetConsoleOutputCP(oldCP);
}

void GameManager::playerUI(Character* player) // 콘솔창 상단 고정
{
	setCursor(0, 0);
	std::cout << "닉네임: " << player->getName() << " | 체력: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth());
	std::cout << " " << player->getHealth() << "/" << player->getMaxHealth();
	std::cout << " | 레벨: " << player->getLevel();
	std::cout << " | 경험치: " << player->getExp() << "/100";
	std::cout << " | 골드: " << player->getGold() << " G";
	std::cout << " | 처치한 몬스터 수: " << player->getKillcount() << "마리\n" << std::endl;
}

void GameManager::battleUI(Character* player, Monster* monster, int line)
{
	setCursor(0, line); // 커서 이동
	std::cout << "========== 전투 상태 ==========\n";
	std::cout << "모험가 체력: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth(), 20);
	std::cout << "  " << player->getHealth() << "/" << player->getMaxHealth() << "  공격력: " << player->getAttack() << "\n";
	std::cout << "몬스터 체력: ";
	drawHealthbar(monster->getHealth(), monster->getMaxHealth(), 20);
	std::cout << "  " << monster->getHealth() << "/" << monster->getMaxHealth() << "  공격력: " << monster->getAttack() << "\n";
	std::cout << "===============================\n";
}

void GameManager::setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameManager::drawMonsterArt(Monster* monster, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	UINT oldInputCP = GetConsoleCP();
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::string art = monster->getart();
	std::istringstream iss(art);
	std::string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		std::cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
	SetConsoleCP(oldInputCP);
}

void GameManager::drawShopArt(Shop* shop, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	UINT oldInputCP = GetConsoleCP();
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::string art = shop->getart();
	std::istringstream iss(art);
	std::string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		std::cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
	SetConsoleCP(oldInputCP);
}

void GameManager::drawDefeat(Character* player, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	UINT oldInputCP = GetConsoleCP();
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::string art = player->getart();
	std::istringstream iss(art);
	std::string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		std::cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
	SetConsoleCP(oldInputCP);
}

void GameManager::drawMainArt(MainArt* mainart, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	UINT oldInputCP = GetConsoleCP();
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::string art = mainart->getart();
	std::istringstream iss(art);
	std::string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		std::cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
	SetConsoleCP(oldInputCP);
}

void GameManager::printLog(const std::string& msg, int line)
{
	setCursor(0, line);
	std::cout << msg << "                         \n"; // 공백으로 이전 텍스트 지우기
}