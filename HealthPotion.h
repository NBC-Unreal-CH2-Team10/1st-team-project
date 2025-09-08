#pragma once
#include "Item.h"

using namespace std;

class HealthPotion : public Item
{
private:
    int healthRestore;

public:
    HealthPotion();
    // 부모의 use() 함수를 재정의(override)하겠다고 명시한다.
    void use(Character* character) override;
};
