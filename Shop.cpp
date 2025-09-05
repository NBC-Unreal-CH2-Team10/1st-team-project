#include "Shop.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>
#include <limits>

// Shop 객체 생성자
Shop::Shop()
{
	availableItems.push_back(new HealthPotion());
	availableItems.push_back(new AttackBoost());
	/*
	새로운 아이템을 추가하려면 여기에
	*/
}

// Shop 객체 소멸자
Shop::~Shop()
{
	for (Item* item : availableItems)
	{
		delete item;
	}
	availableItems.clear();
}

void Shop::enter(Character* player)
{
	while (true)
	{
		cout << "\n=== 상점에 오신 것을 환영합니다!" << endl;
		player->displayStatus();
		cout << "==================" << endl;
		cout << "1. 구매" << endl;
		cout << "2. 판매" << endl;
		cout << "3. 상점 나가기" << endl;
		cout << "==================" << endl;
		cout << "선택: ";
		string choice;
		getline(cin, choice);
		// 입력 실패 처리 : 실패,
		if (choice == "1")
		{
			displayBuyMenu(player);
		}
		else if (choice == "2")
		{
			displaySellMenu(player);
		}
		else if (choice == "3")
		{
			cout << "상점에서 나갑니다." << endl;
			break;
		}
		else
		{
			cout << "잘못된 선택입니다." << endl;
		}
	}
}

// 구매 함수 구현
void Shop::displayBuyMenu(Character* player)
{
	cout << "\n--- 구매 가능한 아이템 ---" << endl;
	for (size_t i = 0; i < availableItems.size(); ++i)
	{
		cout << i + 1 << ". " << availableItems[i]->getName()
			<< " (" << availableItems[i]->getPrice() << " G" << ")" << endl;
	}
	cout << "0. 뒤로 가기" << endl;
	cout << "-----------------" << endl;
	cout << "구매할 아이템 번호를 선택하세요: ";

	int choice;
	cin >> choice;
	// 입력 실패 처리 : 실패, 음수, 초과
	if (cin.fail() || choice <0 || choice > availableItems.size())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "잘못된 선택입니다." << endl;
		return;
	}

	if (choice == 0)
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	Item* selectedItem = availableItems[choice - 1];
	if (player->hasEnoughGold(selectedItem->getPrice()))
	{
		// 각 아이템에 대해 새로운 인스턴스를 생성하여 구매
		if (dynamic_cast<HealthPotion*>(selectedItem)) {
			player->buyItem(new HealthPotion());
		}
		else if (dynamic_cast<AttackBoost*>(selectedItem)) {
			player->buyItem(new AttackBoost());
		}
	}
	else
	{
		cout << "골드가 부족합니다." << endl;
	}
}

// 판매 함수 구현
void Shop::displaySellMenu(Character* player)
{
	player->displayinventory();
	cout << "0. 뒤로 가기" << endl;
	cout << "판매할 아이템 번호를 선택하세요: ";

	int choice;
	cin >> choice;

	if (cin.fail() || choice <0 || choice > availableItems.size())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "잘못된 선택입니다." << endl;
		return;
	}

	if (choice == 0) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	Item* soldItem = player->sellItem(choice - 1);
	if (soldItem != nullptr) {
		delete soldItem;
	}
}

///