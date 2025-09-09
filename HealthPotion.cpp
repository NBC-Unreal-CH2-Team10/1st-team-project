#include "HealthPotion.h"
#include "Character.h" // Character의 멤버 함수 사용
#include <iostream>
#include <algorithm> // min 사용

using namespace std;

HealthPotion::HealthPotion()
{
    // 체력포션 초기값 설정
    name = "체력 물약";
    price = 10;
    healthRestore = 50;
}

string HealthPotion::getName() const
{
    return name;
}

int HealthPotion::getPrice() const
{
    return price;
}

void HealthPotion::use(Character* character)
{

    // ※ Character 클래스에 public : getHealth, getMaxHealth, setHealth 필요
    int currentHealth = character->getHealth();
    int maxHealth = character->getMaxHealth();

    // 최대 체력을 초과하여 회복되지 않도록 실제 회복량 계산, min: 두 값 중 작은 값을 반환
    int healAmount = min(healthRestore, maxHealth - currentHealth);

    character->setHealth(currentHealth + healAmount);
}