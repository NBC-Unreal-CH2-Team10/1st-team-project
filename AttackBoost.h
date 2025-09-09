#pragma once
#include "Item.h"

// Item을 상속받는 '공격력 강화' 클래스
class AttackBoost : public Item
{
public:
    AttackBoost();

    // 이름을 반환 '체력 물약'
    std::string getName() const override;
    // 가격을 반환
    int getPrice() const override;
    // 캐릭터의 공격력을 증가시킴
    void use(Character* character) override;
private:
    // --- 멤버변수 ---
    // 공격력 증가량
    int attackIncrease;
};