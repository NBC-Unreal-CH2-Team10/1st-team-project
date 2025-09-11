#include "Inventory.h"
#include "Item.h"
#include "Character.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Inventory::~Inventory()
{
    // 인벤토리가 소유한 모든 Item 객체의 메모리를 해제
    for (const auto& slot : slots)
    {
        delete slot.item;
    }
    slots.clear();
}

// 인벤토리 관리 인터페이스
void Inventory::manage(Character* owner)
{
    int choice = -1;
    while (choice != 0) // 0을 입력할 때 까지 반복
    {
        system("cls");
        cout << "\n--- [ 캐릭터 상태 ] ---" << '\n';
        cout << "체력: " << owner->getHealth() << " / " << owner->getMaxHealth() << '\n';
        cout << "공격력: " << owner->getAttack() << '\n';
        displayInventory();

        if (getSize() == 0) // 인벤토리가 비었다면 1.5초 대기 후 뒤로가기
        {
            this_thread::sleep_for(chrono::milliseconds(1500));
            return;
        }

        cout << "\n사용할 아이템 번호를 입력하세요 (0: 나가기): ";
        cin >> choice;

        // 입력 오류 처리
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            choice = -1;
            cout << "\n잘못된 입력입니다." << '\n';
            this_thread::sleep_for(chrono::milliseconds(1500));
            continue;
        }
        // 아이템 사용, 인덱스는 번호 -1
        else if (choice > 0 && choice <= getSize())
        {
            useItem(choice - 1, owner);
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        // 잘못된 번호 처리
        else if (choice != 0)
        {
            cout << "\n잘못된 번호입니다." << '\n';
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
    }
}


// 아이템 추가 하고 수량을 관리하는 함수
// 1. 단 아이템을 생성하여 포인터를 전달받음
void Inventory::addItem(Item* newItem, bool showMessage)
{
    for (auto& slot : slots)
    {   // 2. 슬롯에 같은 아이템이 있는지 검사
        if (slot.item->getName() == newItem->getName())
        {
            // 3. 같은 아이템이 있으면 수량을 증가
            slot.quantity++;
            // 4. 새로 생성된 newItem 객체는 메모리 해제
            delete newItem;
            if (showMessage) {
                cout <<"\n" << "'" << slot.item->getName() << "'을(를) 획득했습니다." << '\n';
            }
            return;
        }
    }

    // 5. 같은 아이템이 없으면 새로운 슬롯을 만들어 추가
    InventorySlot newSlot;
    newSlot.item = newItem;
    newSlot.quantity = 1;
    slots.push_back(newSlot);
    if (showMessage) {
        cout << "'" << newItem->getName() << "'을(를) 획득했습니다." << '\n';
    }
}


// 아이템 판매 함수
void Inventory::sellItem(int index)
{
    // 인덱스가 유효하지 않으면 판매없이 종료
    if (index < 0 || index >= slots.size())
    {
        return;
    }

    // 판매 후 수량 감소
    slots[index].quantity--;

    // 수량이 0이 되면 슬롯 제거
    if (slots[index].quantity <= 0)
    {
        delete slots[index].item; // 아이템 객체 메모리 해제
        slots.erase(slots.begin() + index); // 벡터에서 슬롯 제거
    }
}

size_t Inventory::getSize() const
{
    return slots.size();
}

const vector<InventorySlot>& Inventory::getSlots() const
{
    return slots;
}


// 인벤토리 크기를 검사하고 내용을 출력하는 함수
void Inventory::displayInventory() const
{
    cout << "\n--- [ 인벤토리 ] ---" << '\n';
    if (slots.empty())
    {
        cout << "비어있습니다..." << '\n';
    }
    else
    {
        for (size_t i = 0; i < slots.size(); ++i)
        {
            cout << i + 1 << ". " << slots[i].item->getName()
                << " (" << slots[i].quantity << "개)" << '\n';
        }
    }
    cout << "--------------------" << '\n';
}

// 아이템을 사용하고 수량을 관리하는 함수
void Inventory::useItem(int index, Character* owner)
{
    // 인덱스가 유효하지 않으면 사용없이 종료
    if (index < 0 || index >= slots.size())
    {
        cout << "잘못된 번호입니다." << '\n';
        return;
    }

    // 아이템 효과 발동
    slots[index].item->use(owner);

    // 사용 후 수량 감소
    slots[index].quantity--;

    // 수량이 0이 되면 인벤토리에서 제거
    if (slots[index].quantity <= 0)
    {
        cout << "'" << slots[index].item->getName() << "'을(를) 모두 사용했습니다." << '\n';
        delete slots[index].item; // 아이템 객체 메모리 해제
        slots.erase(slots.begin() + index); // 벡터에서 슬롯 제거
    }
}

Item* Inventory::getItem(int index) const
{
    if (index < 0 || index >= slots.size())
    {
        return nullptr;
    }
    return slots[index].item;
}

