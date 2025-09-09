#pragma once
#include "Item.h"

// Item을 상속받는 '체력 물약' 클래스
class HealthPotion : public Item
{
public:
    HealthPotion();

    // 이름을 반환 '체력 물약'
    std::string getName() const override;
    // 가격을 반환
    int getPrice() const override;
    // 캐릭터의 체력을 회복시킴
    void use(Character* character) override;
private:
    // --- 멤버변수 ---
    // 물약의 회복량
    int healthRestore;
};