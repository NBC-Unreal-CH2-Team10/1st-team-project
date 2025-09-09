#include "Shop.h"
#include "Item.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;

Shop::Shop()
{
    availableItems.push_back(new HealthPotion());
    availableItems.push_back(new AttackBoost());
    // ※ 새로운 아이템을 추가하고 싶으면 여기에 추가 . . .
}

Shop::~Shop()
{
    // 상점이 소유한 모든 item 객체를 해제
    for (auto item : availableItems)
    {
        delete item;
    }
    availableItems.clear();
}

// 상점 진입
void Shop::visit(Character* player)
{
    cout << "\n상점에 방문합니다..." << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
    int mainChoice = -1;
    while (mainChoice != 3) // 3을 입력할 때 까지 반복
    {
        displayMainMenu(player);
        cin >> mainChoice;
        // 입력 오류 처리
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            mainChoice = -1;
        }

        switch (mainChoice)
        {
        case 1:
            buyLoop(player); // 구매 루프 시작
            break;
        case 2:
            sellLoop(player); // 판매 루프 시작
            break;
        case 3:
            cout << "\n상점에서 나갑니다..." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        default:
            cout << "\n잘못된 입력입니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }
    }
}

// 상점의 메인 메뉴
void Shop::displayMainMenu(Character* player) const
{
    system("cls");
    UINT oldCP = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
    std::cout << u8R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠉⣴⡶⠶⠶⠶⣶⡶⣶⣶⠶⣶⡶⠶⠶⣶⡶⠶⠶⢶⣶⣦⠉⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⣿⣷⣮⣭⠛⣿⡇⣩⡍⠀⣿⠀⣿⡇⢸⡇⢈⣉⣥⣿⣿⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣄⠻⠷⠶⠶⠾⠿⠷⠿⠷⠶⠿⠷⠶⠶⠿⠷⠾⠿⠿⠿⢟⣠⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⢉⣩⣭⣭⣭⣭⣭⣍⡉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠾⠛⣁⣤⠶⠶⠶⣤⣈⠛⠷⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⠟⠁⣰⠟⢁⡠⠔⠒⠢⢄⡈⠻⣆⠈⠿⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⣀⡿⠛⠭⠤⠀⠀⠀⠤⠭⠻⢿⣀⡀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⣟⡇⠀⠉⢉⡠⡆⠠⣉⠉⠀⢸⣻⠇⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣧⡀⠻⣿⣤⡐⠃⠒⠒⠒⠈⢂⣤⣿⠏⢀⣼⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠞⠋⠙⠳⣬⡙⠻⣷⡶⠶⠶⣾⠟⢋⣤⠞⠋⠙⠳⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⣾⣛⣿⣀⢠⡾⠃⠀⠀⠀⠀⣠⡽⠛⠙⠻⠶⠟⠋⠛⢯⣄⠀⠀⠀⠀⠘⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢸⣿⠶⢾⡏⣾⠃⠀⠀⠀⣴⠞⣿⣿⣷⣶⣤⣤⣤⣶⣾⣿⣿⠳⣦⠀⢀⣄⣘⣷⣾⢹⣆⠀⠀⣀⣠⡄⠀⠀⠀
⠀⠀⠀⠀⢀⡴⠞⠋⠀⠈⠻⢿⣄⠀⠀⢠⣿⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⣿⡄⠀⠸⣷⣭⡿⢧⣼⣷⠟⣩⡴⠇⠀⠀⠀
⠀⠀⠀⠀⢸⡇⣿⣿⣿⣟⣿⢾⣿⠀⠀⠀⢠⣤⠶⠛⠛⠿⣿⣿⠿⠿⠛⠓⠶⣤⡄⠐⠿⣭⣉⣙⠻⣾⣏⣿⣋⣭⡽⠗⠀⠀⠀
⠀⢸⡟⠛⠛⠻⠿⠭⠭⠭⠽⠟⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠻⠾⠛⣿⣟⣿⡟⠛⢻⡇⠀
⠀⠸⠧⠤⢤⡤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠭⢭⣤⠤⠼⠇⠀
⠀⠀⢸⡟⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⢻⡇⠀⠀
⠀⠀⢸⡇⣿                                     ⣿⢸⡇⠀⠀
⠀⠀⢸⡇⣿                                     ⣿⢸⡇⠀⠀
⠀⠀⢸⡇⣿                                     ⣿⢸⡇⠀⠀
⠀⠀⢸⡇⣿                                     ⣿⢸⡇⠀⠀
⠀⠀⢸⡇⢿⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⡿⢸⡇⠀⠀
⠀⠀⠘⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠃⠀⠀
)" << std::endl;
    SetConsoleOutputCP(oldCP);
    cout << "\n주인: 어서 오세요! 무엇을 도와드릴까요?\n" << std::endl;
    cout << "--- [ 상점 ] ---" << endl;
    cout << "1. 아이템 구매" << endl;
    cout << "2. 아이템 판매" << endl;
    cout << "3. 나가기" << endl;
    cout << "-----------------" << endl;
    cout << "현재 소지 골드: " << player->getGold() << " G\n" << endl;
    cout << "선택: ";
}

// 구매 루프
void Shop::buyLoop(Character* player)
{
    int buyChoice = -1;
    while (buyChoice != 0)
    {
        system("cls");
        cout << "\n--- [ 아이템 구매 ] ---" << endl;
        for (size_t i = 0; i < availableItems.size(); ++i)
        {
            cout << i + 1 << ". " << availableItems[i]->getName()
                << " - " << availableItems[i]->getPrice() << " Gold" << endl;
        }
        player->getInventory()->displayInventory();
        cout << "현재 소지 골드: " << player->getGold() << " G\n" << endl;
        cout << "\n구매할 아이템 번호를 입력하세요 (0: 뒤로 가기): ";
        cin >> buyChoice;
        // 입력 오류 처리
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            buyChoice = -1;
            cout << "잘못된 입력입니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        //아이템 구매, 인덱스는 번호 - 1
        else if (buyChoice > 0 && buyChoice <= availableItems.size()) {
            buyItem(buyChoice - 1, player);
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        // 잘못된 번호 처리
        else if (buyChoice != 0) {
            cin.clear();
            cin.ignore(1024, '\n');
            buyChoice = -1;
            cout << "잘못된 아이템 번호입니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
    }
}

// 구매 처리
void Shop::buyItem(int index, Character* player)
{
    Item* itemToBuy = availableItems[index];

    // 1. 플레이어의 골드 확인
    if (player->getGold() >= itemToBuy->getPrice())
    {
        // 2. 플레이어의 골드 차감
        player->setGold(player->getGold() - itemToBuy->getPrice());

        // 3. 아이템의 '복사본'을 새로 생성하여 플레이어 인벤토리에 추가
        Item* newItem = nullptr;
        if (itemToBuy->getName() == "체력 물약") {
            newItem = new HealthPotion();
        }
        else if (itemToBuy->getName() == "공격력 강화") {
            newItem = new AttackBoost();
        }
        // ※ 새로운 아이템이 추가되면 여기에 else if를 추가 ...

        if (newItem) {
            player->getInventory()->addItem(newItem, false);
            cout << "'" << itemToBuy->getName() << "'을(를) 구매했습니다." << endl;
        }
    }
    else
    {
        cout << "골드가 부족합니다." << endl;
    }
}

// 판매 루프
void Shop::sellLoop(Character* player)
{
    int sellChoice = -1;
    while (sellChoice != 0)
    {
        system("cls");
        cout << "--- [ 아이템 판매 ] ---" << endl;
        for (size_t i = 0; i < availableItems.size(); ++i)
        {
            cout << i + 1 << ". " << availableItems[i]->getName()
                << " - " << availableItems[i]->getPrice() * 0.6 << " Gold" << endl;
        }
        player->getInventory()->displayInventory();

        // 인벤토리가 비었을 경우 판매 불가
        if (player->getInventory()->getSize() == 0)
        {
            cout << "\n판매할 아이템이 없습니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }
        cout << "현재 소지 골드: " << player->getGold() << " G\n" << endl;
        cout << "\n판매할 아이템 번호를 입력하세요 (0: 뒤로 가기): ";
        cin >> sellChoice;

        // 입력 오류 처리
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            sellChoice = -1;
            cout << "잘못된 입력입니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        // 아이템 판매, 인덱스는 번호 -1
        else if (sellChoice > 0 && sellChoice <= player->getInventory()->getSize())
        {
            sellItem(sellChoice - 1, player);
            this_thread::sleep_for(chrono::milliseconds(1000));

        }
        // 잘못된 번호 처리
        else if (sellChoice != 0) {
            cout << "잘못된 아이템 번호입니다." << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
    }
}

// 판매 처리 함수 작성
void Shop::sellItem(int index, Character* player)
{

    Inventory* playerInventory = player->getInventory();
    Item* itemToSell = playerInventory->getItem(index);

    // 1. 판매 가격 계산 (원가의 60%)
    int sellPrice = itemToSell->getPrice() * 0.6;

    // 2. 플레이어에게 골드 지급
    player->setGold(player->getGold() + sellPrice);

    // 3. 인벤토리에서 아이템 제거
    cout << "'" << itemToSell->getName() << "'을(를) 판매하여 " << sellPrice << " Gold를 얻었습니다." << endl;
    playerInventory->sellItem(index);
}