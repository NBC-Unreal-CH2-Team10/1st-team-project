#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

using namespace std;

// 생성자: 부모(Item) 생성자를 호출해 이름을 정하고, 자신의 멤버 변수를 초기화한다.
HealthPotion::HealthPotion()
    : Item("체력 포션"), healthRestore(50)
{
}

// 기능 구현: 캐릭터의 heal 함수를 호출해 체력을 회복시킨다.
void HealthPotion::use(Character* character)
{
    cout << character->getName() << "이(가) " << getName() << "을(를) 사용합니다." << endl;
    character->heal(healthRestore);
}