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
#include <cctype>

using namespace std;

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

    int logCount = 0;
    string invchoice;

	setCursor(0, 4);
	while (true)
	{
		cout << "인벤토리를 확인하시겠습니까? (Y/N) : ";
		cin >> invchoice;

        // 입력 오류 처리
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            invchoice = -1;
            cout << "\n잘못된 입력입니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            continue;
        }
        
        if (invchoice == "Y" || invchoice == "y")
        {
            player->getInventory()->manage(player);
        }
        else if (invchoice == "N" || invchoice == "n")
        {
            break;
        }
    }
    
    std::cout << "전투를 시작합니다!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //1초 딜레이
    
    int logline = 30;
    int battlelog = logline + 6;
    int delay = 500;

	system("cls");
	
	playerUI(player);  //커서 맨위로 이동 후 1줄짜리 UI 출력

	drawMonsterArt(monster, 2); 

	battleUI(player, monster, logline);

	printLog(monster->getName() + "이(가) 나타났습니다!", battlelog, logCount);
	this_thread::sleep_for(chrono::milliseconds(1000));
	
	string playermsg = "용사가" + to_string(player->getAttack()) + "의 피해를 입혔습니다.";
	string monstermsg = "몬스터가 " + to_string(monster->getAttack()) + "의 피해를 입혔습니다.";

	while (player->getHealth() > 0 && monster->getHealth() > 0) // attack 
	{
		monster->takeDamage(player->getAttack());				//몬스터가 먼저 공격 받음

		battleUI(player, monster, logline);
		printLog(playermsg, battlelog, logCount);
		this_thread::sleep_for(chrono::milliseconds(delay));

		if (player->getHealth() == 0 || monster->getHealth() == 0) break;

		player->takeDamage(monster->getAttack());				
		playerUI(player);

		battleUI(player, monster, logline);
		printLog(monstermsg, battlelog, logCount);
		this_thread::sleep_for(chrono::milliseconds(delay));

		if (player->getHealth() == 0 || monster->getHealth() == 0) break;

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

				printLog("체력 포션을 사용하여 50의 체력을 회복했습니다!", battlelog, logCount);
				
				this_thread::sleep_for(chrono::milliseconds(1200));
			}
		}
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
	printLog("몬스터를 처치했습니다!", battlelog, logCount);
	this_thread::sleep_for(chrono::milliseconds(1000));

	//몬스터 처치 -> 경험치와 골드 아이템 획득

	//골드 획득
	//몬스터마다 골드 다르게 하고 dropGold 같은 함수로 드랍 골드 확인
	//플레이어에 addGold 함수로 골드 추가, 골드 획득 문구 출력

	string goldmsg = to_string(monster->getGold()) + "골드를 획득했습니다.";
	printLog(goldmsg, battlelog, logCount);

	player->addInventory(monster->dropItem());
	this_thread::sleep_for(chrono::milliseconds(1000));
	//드랍 아이템이 있는지 확인하고 있으면 인벤에 추가 없으면 넘어가기

	delete monster;
}

void GameManager::visitShop()
{

	Shop* shop = new Shop();

	int logline = 20;
	int logCount = 0;

	while (true)
	{
		system("cls"); 

		playerUI(player);

		drawShopArt(shop, 2);

		int choice;
		
		printLog("==================", logline, logCount);
		printLog("1. 구매", logline + 1, logCount);
		printLog("2. 판매", logline + 2, logCount);
		printLog("3. 상점 나가기", logline + 3, logCount);
		printLog("==================", logline + 4, logCount);
		
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

					printLog("잘못된 입력입니다. 다시 입력하세요.", logline + 10, logCount);
					this_thread::sleep_for(chrono::milliseconds(1000)); 

					continue;
				}
				else if (choice == -2)
				{
					printLog("잘못된 아이템 번호입니다.", logline + 10, logCount);
					this_thread::sleep_for(chrono::milliseconds(1000));
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

					printLog("잘못된 선택입니다. 다시 입력해주세요.", logline + 10, logCount);
					this_thread::sleep_for(chrono::milliseconds(1000));

					continue;
				}
				else if (choice == -2)
				{
					printLog("판매할 아이템이 없습니다.", logline + 10, logCount);
					break;
				}

				shop->sellItem(choice - 1, player);
				printLog("아이템을 판매했습니다.", logline + 10, logCount);
				this_thread::sleep_for(chrono::milliseconds(1000)); 
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
	std::cout << "  " << player->getHealth() << "/" << player->getMaxHealth() << "  공격력: " << player->getAttack() << "      \n";
	std::cout << "몬스터 체력: ";
	drawHealthbar(monster->getHealth(), monster->getMaxHealth(), 20);
	std::cout << "  " << monster->getHealth() << "/" << monster->getMaxHealth() << "  공격력: " << monster->getAttack() << "       \n";
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

	while (std::getline(iss, lineStr)) 
	{
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

	while (std::getline(iss, lineStr)) 
	{
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

	while (std::getline(iss, lineStr)) 
	{
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

	while (std::getline(iss, lineStr)) 
	{
		setCursor(0, line + offset);
		std::cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
	SetConsoleCP(oldInputCP);
}

vector<string> logs;
const int MAX_LOGS = 10;
int logCount = 0;

void setColor(int color) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GameManager::printLog(const string& msg, int line, int& logCount)
{
	// 로그 영역이 가득 찼으면 클리어 후 초기화
	if (logCount >= MAX_LOGS) 
	{
		clearLogs(line);
		logCount = 0;
	}

	setCursor(0, line + logCount);

	// 한 줄 전체를 먼저 지움
	cout << string(80, ' ');

	// 다시 커서 위치 맞추고 로그 출력
	setCursor(0, line + logCount);

	bool isDamage = msg.find("피해") != std::string::npos;
	bool isHeal = msg.find("회복") != std::string::npos;
	bool isGold = msg.find("골드") != std::string::npos;
	bool isBoost = msg.find("증가") != std::string::npos;

	for (char c : msg) 
	{
		if (isdigit(static_cast<unsigned char>(c)))
		{
			if (isDamage) setColor(12);   // 빨강 (데미지)
			else if (isHeal) setColor(10); // 초록 (회복)
			else if (isGold) setColor(14); // 노랑 (골드)
			else if (isBoost) setColor(9); // 파랑 (공격력 증가)
			else setColor(7);              // 기본색
			std::cout << c;
			setColor(7); // 다시 기본색으로
		}
		else 
		{
			std::cout << c;
		}
	}

	logCount++;
}

void GameManager::clearLogs(int logStartLine) 
{
	for (int i = 0; i < MAX_LOGS; i++) 
	{
		setCursor(0, logStartLine + i);
		cout << string(80, ' ');  // 공백으로 줄 전체 덮기
	}

}