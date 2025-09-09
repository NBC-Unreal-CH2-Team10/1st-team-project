#include "GameManager.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>
#include <sstream>


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

	auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // 공격력 증가 포션이 존재하는지 확인

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

	cout << "전투를 시작합니다!" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000)); //1초 딜레이

	int logline = monster->getart().size() + 4; //아트에서 2줄 아래
	int battlelog = logline + 6;
	int delay = 500; //0.5초

	system("cls");
	
	while (player->getHealth() != 0 && monster->getHealth() != 0) // attack 함수 제작?
	{
		playerUI(player);  //커서 맨위로 이동 후 1줄짜리 UI 출력

		drawMonsterArt(monster, 2); // 3번째 줄부터 아트 출력

		printLog(monster->getName() + "이(가) 나타났습니다!", logline);
		
		battleUI(player, monster, logline + 2);

		monster->takeDamage(player->getAttack());				//몬스터가 먼저 공격 받음
		playerUI(player);
		battleUI(player, monster, logline);
		printLog("모험가가 " + to_string(player->getAttack()) + "의 피해를 입혔습니다.", battlelog);
		++battlelog;
		this_thread::sleep_for(chrono::milliseconds(delay));

		player->takeDamage(monster->getAttack());				//플레이어가 공격 받음
		playerUI(player);
		battleUI(player, monster, logline);
		printLog("몬스터가 " + to_string(monster->getAttack()) + "의 피해를 입혔습니다.", battlelog);
		++battlelog;
		this_thread::sleep_for(chrono::milliseconds(delay));


		if (player->getHealth() < (player->getMaxHealth() / 2)) //최대 체력의 50% 아래로 내려갈 경우 자동 사용
		{
			string find = "체력 물약";

			auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // 체력 포션이 존재하는지 확인

			if (it != inventory.end())
			{
				//체력 포션 사용
				inventory[it - inventory.begin()]->use(player);
				playerUI(player);
				battleUI(player, monster, logline);
				printLog("체력 포션을 사용하여 50의 체력을 회복했습니다!", battlelog);
				++battlelog;
				this_thread::sleep_for(chrono::milliseconds(delay));
			}
		}
		++battlelog;
	}

	if (player->getHealth() == 0)
	{
		throw runtime_error("모험가가 사망했습니다.");
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

	cout << monster->getGold() << "골드를 획득했습니다." << endl;

	player->addInventory(monster->dropItem());

	//드랍 아이템이 있는지 확인하고 있으면 인벤에 추가 없으면 넘어가기

	delete monster;
}

void GameManager::visitShop(Character* player)
{
	Shop* shop = new Shop();

	int logline = shop->getart().size() + 4; //상점 아트 4줄 아래부터

	while (true)
	{
		system("cls"); //콘솔 화면 지우기

		playerUI(player);

		drawShopArt(shop, 2);

		int choice;
		//구매 혹은 판매 선택지 출력

		printLog("==================", logline);
		printLog("1. 구매", logline + 1);
		printLog("2. 판매", logline + 2);
		printLog("3. 상점 나가기", logline + 3);
		printLog("==================", logline + 4);
		
		cout << "번호를 입력하세요: ";

		cin >> choice;
		cin.ignore(1000, '\n');

		if (cin.fail()) //잘 못된 타입이 입력되면 true 반환
		{
			cin.clear(); // 오류 상태 초기화
			cin.ignore(1000, '\n'); // 잘못된 입력 버리기
			cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
			continue;
		}

		if (choice == 1) //구매
		{
			while (true) {
				system("clear");

				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->buyLoop(player);

				if (choice == 0) break;       // 뒤로가기
				if (choice == -1) 
				{
					printLog("잘못된 입력입니다. 다시 입력해주세요.", logline + 10);											//로그 출력 라인 위치 수정 필요
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1초 대기
					continue;
				}

				// 선택한 아이템 구매 처리
				setCursor(0, logline + 10);
				shop->buyItem(choice - 1, player);
			}
		}
		else if (choice == 2) //판매
		{
			while (true)
			{
				system("cls"); //콘솔 화면 지우기

				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->sellLoop(player);

				if (choice == 0) break;       // 뒤로가기
				if (choice == -1)
				{
					printLog("잘못된 선택입니다. 다시 입력해주세요.", logline + 10);											//로그 출력 라인 위치 수정 필요
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1초 대기
					continue;
				}
				else if (choice == -2)
				{
					printLog("판매할 아이템이 없습니다.", logline + 10);
					break;
				}

				// 아이템 판매

				shop->sellItem(choice - 1, player);
				printLog("아이템을 판매했습니다.", logline + 10);
				this_thread::sleep_for(chrono::milliseconds(1000)); // 1초 대기
			}
		}
		else if (choice == 3)
		{
			string answer;

			cout << "상점을 나가시겠습니까? (Y/N)" << endl;
			cin >> answer;
			cin.ignore(1000, '\n');

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
	
	vector<Item*> item = player->getInventory();
	
	for (int i = 1; i <= item.size(); ++i)
	{
		cout << i << ". " << item[i]->getName() << ": " << item[i]->getPrice()*0.8 << "골드" << endl; //여기서 price는 상점에서 판매시 가격
	}
}

void drawHealthbar(int hp, int maxHp, int barWidth = 10)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	double ratio = (double)hp / maxHp;
	int filled = (int)(ratio * barWidth);

	cout << "[";

	for (int i = 0; i < barWidth; i++)
	{
		if (i < filled) {
			SetConsoleTextAttribute(hConsole, 10); // 10 = 초록색
			cout << u8"■";
		}
		else {
			SetConsoleTextAttribute(hConsole, 7); // 12 = 빨간색
			cout << u8"-";  // 빈 칸도 □ 대신 색칠된 ■로 통일 가능
		}
	}

	SetConsoleTextAttribute(hConsole, 7); // 기본 색상으로 복구
	cout << "] ";

	SetConsoleOutputCP(oldCP);
}

void GameManager::playerUI(Character* player) // 콘솔창 상단 고정
{
	setCursor(0, 0);
	cout << "닉네임: " << player->getName() << " | 체력: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth());
	cout << " " << player->getHealth() << "/" << player->getMaxHealth();
	cout << " | 레벨: " << player->getLevel();
	cout << " | 경험치: " << player->getExp() << "/100";
	cout << " | 골드: " << player->getGold() << " G";
	cout << " | 처치한 몬스터 수: " << player->getKillcount() << "마리\n" << endl;
}

void GameManager::battleUI(Character* player, Monster* monster, int line)
{
	setCursor(0, line); // 커서 이동
	cout << "========== 전투 상태 ==========\n";
	cout << "모험가 체력: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth(), 20);
	cout << "  " << player->getHealth() << "/" << player->getMaxHealth() << "  공격력: " << player->getAttack() << "\n";
	cout << "몬스터 체력: ";
	drawHealthbar(monster->getHealth(), monster->getMaxHealth(), 20);
	cout << "  " << monster->getHealth() << "/" << monster->getMaxHealth() << "  공격력: " << monster->getAttack() << "\n";
	cout << "===============================\n";
}

void GameManager::setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameManager::drawMonsterArt(Monster* monster, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = monster->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::drawShopArt(Shop* shop, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = shop->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::drawDefeat(Character* player, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = player->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::drawMainArt(MainArt* mainart, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = mainart->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::printLog(const string& msg, int line)
{
	setCursor(0, line);
	cout << msg << "                         \n"; // 공백으로 이전 텍스트 지우기
}
