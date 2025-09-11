#include "Shop.h"
#include "Item.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "GameManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <Windows.h>

using namespace std;

Shop::Shop()
{
    availableItems.push_back({
        HealthPotion::BASE_NAME,    // "체력 물약"
        HealthPotion::BASE_PRICE,   // 10
        9,
        []() { return new HealthPotion(); }
        });
    availableItems.push_back({
        AttackBoost::BASE_NAME,     // "공격력 강화"
        AttackBoost::BASE_PRICE,    // 15
        5,
        []() { return new AttackBoost(); }
        });
    // ※ 새로운 아이템을 추가하고 싶으면 여기에 추가 . . .
}

Shop::~Shop()
{
    //for (auto item : availableItems)
    //{
    //    delete item;
    //}
    availableItems.clear();
}

// 상점 진입
void Shop::visit(Character* player)
{
    std::cout << "\n상점에 방문합니다..." << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    int mainChoice = -1;
    while (mainChoice != 3) // ※ 3을 입력할 때 까지 반복, 기능 추가시 숫자 변경
    {
        displayMainMenu(player);
        std::cin >> mainChoice;
        // 입력 오류 처리
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
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
            /* ※ 상점에서 인벤토리 관리기능 병합시 주석 해제
        case 3:
            player->getInventory()->manage(player);
            break;
            */
        case 3:
            std::cout << "\n상점에서 나갑니다..." << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break;
        default:
            std::cout << "\n잘못된 입력입니다." << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
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
)" << '\n';
    SetConsoleOutputCP(oldCP);
    std::cout << "\n주인: 어서 오세요! 무엇을 도와드릴까요?\n" << '\n';
    std::cout << "--- [ 상점 ] ---" << '\n';
    std::cout << "1. 아이템 구매" << '\n';
    std::cout << "2. 아이템 판매" << '\n';
    // ※ 인벤토리 관리 기능 추가시 주석 해제
    //std::cout << "X. 인벤토리 관리" << std::endl;
    std::cout << "3. 나가기" << '\n';
    std::cout << "-----------------" << '\n';
    std::cout << "현재 소지 골드: " << player->getGold() << " G\n" << '\n';
    std::cout << "선택: ";
}

// 구매 루프
int Shop::buyLoop(Character* player)
{
    int buyChoice;

    //cout << "\n--- [ 아이템 구매 ] ---" << endl;
    for (size_t i = 0; i < availableItems.size(); ++i)
    {
        std::cout << "\n--- [ 아이템 구매 ] ---" << '\n';
        for (size_t i = 0; i < availableItems.size(); ++i)
        {
            std::cout << i + 1 << ". " << availableItems[i].name
                << " - " << availableItems[i].price << " Gold"
                << " (재고: " << availableItems[i].stock << "개)" << '\n';
        }
        player->getInventory()->displayInventory();
        std::cout << "현재 소지 골드: " << player->getGold() << " G\n" << '\n';
        std::cout << "\n구매할 아이템 번호를 입력하세요 (0: 뒤로 가기): ";
        std::cin >> buyChoice;

        // 입력 오류 처리
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            buyChoice = -1;
            std::cout << "잘못된 입력입니다." << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			return -1;
        }
        else if (buyChoice >= 0 && buyChoice <= availableItems.size()) 
        {
            return buyChoice;
        }
        else
        {
            cout << "\n잘못된 아이템 번호입니다." << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            return -2;
        }
    }
}

// 구매 처리
void Shop::buyItem(int index, Character* player)
{
    ShopSlot& itemToBuy = availableItems[index]; // 참조로 가져와서 직접 수정

    GameManager* gm = new GameManager();
    gm->setCursor(0, 33);
    // 1. 재고 확인
    if (itemToBuy.stock <= 0)
    {
        std::cout << "해당 아이템은 품절되었습니다." << '\n';
        this_thread::sleep_for(chrono::milliseconds(1500));
        return;
    }
    // 2. 플레이어의 골드 확인
    if (player->getGold() >= itemToBuy.price)
    {
        // 3. 플레이어의 골드 차감
        player->setGold(player->getGold() - itemToBuy.price);

        // 4. Shopslot의 createItem 호출하여 아이템의 '복사본'을 새로 생성
        Item* newItem = itemToBuy.createItem();

        player->getInventory()->addItem(newItem, false);
        std::cout << "'" << itemToBuy.name << "'을(를) 구매했습니다." << '\n';
        this_thread::sleep_for(chrono::milliseconds(1500));
        // 5. 재고 감소
        itemToBuy.stock--;
    }
    else
    {
        std::cout << "골드가 부족합니다." << '\n';
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
    delete gm;
}

// 판매 루프
int Shop::sellLoop(Character* player)
{
    int sellChoice = -1;

    cout << "--- [ 아이템 판매 ] ---" << '\n';
    for (size_t i = 0; i < availableItems.size(); ++i)
    {
        cout << i + 1 << ". " << availableItems[i].name
            << " - " << availableItems[i].price * 0.6 << " Gold" << '\n';
    }
    player->getInventory()->displayInventory();

    // 인벤토리가 비었을 경우 판매 불가
    if (player->getInventory()->getSize() == 0)
    {
        cout << "\n판매할 아이템이 없습니다." << '\n';
        this_thread::sleep_for(chrono::milliseconds(1500));
        return 0;
    }
    cout << "현재 소지 골드: " << player->getGold() << " G\n" << '\n';
    cout << "\n판매할 아이템 번호를 입력하세요 (0: 뒤로 가기): ";
    cin >> sellChoice;

    // 입력 오류 처리
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        sellChoice = -1;
        cout << "잘못된 입력입니다." << '\n';
        this_thread::sleep_for(chrono::milliseconds(1500));
        return sellChoice;
    }
    // 아이템 판매, 인덱스는 번호 -1
    else if (sellChoice > 0 && sellChoice <= player->getInventory()->getSize())
    {
        return sellChoice;
    }
    // 잘못된 번호 처리
    else if (sellChoice != 0) {
        return -1;
    }

}

// 판매 처리 함수 작성
void Shop::sellItem(int index, Character* player)
{
    Inventory* playerInventory = player->getInventory();
    Item* itemToSell = player->getInventory()->getItem(index);

    // 1. 판매 가격 계산 (원가의 60%)
    int sellPrice = itemToSell->getPrice() * 0.6;

    // 2. 플레이어에게 골드 지급
    player->setGold(player->getGold() + sellPrice);

    // 3. 인벤토리에서 아이템 제거
    std::cout << "'" << itemToSell->getName() << "'을(를) 판매하여 " << sellPrice << " Gold를 얻었습니다." << '\n';
    playerInventory->sellItem(index);
    // 4. 상점 재고 증가
    //for (auto& slot : availableItems)
    //{
    //    if (slot.name == itemToSell->getName())
    //    {
    //        slot.stock++;
    //        break; // 해당 아이템을 찾았으면 루프 종료
    //    }
    //}
}