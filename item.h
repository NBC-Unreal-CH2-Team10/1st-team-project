#pragma once
#include <string>

class Character;

class Item
{
public:
    virtual ~Item() {}

    // 순수 가상 함수들
    // 아이템의 이름을 반환
    virtual std::string getName() const = 0;
    // 아이템의 가격을 반환
    virtual int getPrice() const = 0;
    // 캐릭터의 포인터를 받아 아이템 효과를 발동
    virtual void use(Character* character) = 0;

protected:
    // --- 멤버 변수 ---
    std::string name;
    int price;
};