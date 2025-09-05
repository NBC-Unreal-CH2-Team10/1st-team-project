#include "AttackBoost.h"
#include "Character.h"
#include <iostream>

using namespace std;

// 생성자: 아이템 이름과 공격력 증가량을 초기화한다.
AttackBoost::AttackBoost()
    : Item("공격력 부스트", 25), attackIncrease(10)
{
}
// 기능 구현: 캐릭터의 increaseAttack 함수를 호출하여 공격력을 증가시킨다.
void AttackBoost::use(Character* character)
{
    cout << character->getName() << "이(가) " << getName() << "을(를) 사용합니다." << endl;
    character->increaseAttack(attackIncrease);
}