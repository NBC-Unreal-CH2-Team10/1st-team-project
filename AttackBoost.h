#pragma once
#pragma once
#include "Item.h"

using namespace std;

class AttackBoost : public Item
{
private:
    int attackIncrease; // 공격력 부스트만의 고유한 데이터

public:
    AttackBoost();

    // Item의 use() 함수를 공격력 증가 기능으로 재정의한다.
    void use(Character* character) override;
};