#pragma once
#include <vector>

class Item;
class Character;

// 인벤토리의 한 슬롯을 나타내는 구조체
// 아이템 객체 포인터 + 수량
struct InventorySlot
{
    Item* item;
    int quantity;
};

// 플레이어의 아이템을 관리하는 클래스
// 1. 인벤토리 관리 인터페이스 제공
// 2. 아이템 객체의 생성과 소멸 관리
// 3. 아이템 추가, 사용, 판매 기능 제공
class Inventory
{
public:
    ~Inventory();

    // 인벤토리 관리 인터페이스
    void manage(Character* owner);

    // 아이템 추가 하고 수량을 관리하는 함수
    // showMessage 파라미터 역할은 메시지 분기. 획득:true, 구매:false
    void addItem(Item* item, bool showMessage = true);

    // 인벤토리에서 아이템을 판매
    // 아이템 수량 감소, 0이 되면 슬롯 제거
    void sellItem(int index);

    // 인벤토리 크기 반환
    size_t getSize() const;

    // 인벤토리 슬롯 벡터에 대한 읽기 전용 접근 제공
    const std::vector<InventorySlot>& getSlots() const;

    // 인벤토리 크기를 검사하고 내용을 출력하는 함수
    void displayInventory() const;

    // 인덱스에 해당하는 아이템 포인터를 반환
    // 인덱스가 유효하지 않으면 nullptr 반환
    Item* getItem(int index) const;

private:
    // 아이템을 사용하고 수량을 관리하는 함수
    void useItem(int index, Character* owner);

    // --- 멤버변수 --- 
    // 인벤토리 슬롯 벡터
    std::vector<InventorySlot> slots;

};