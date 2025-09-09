#include "AttackBoost.h"
#include "Character.h" // Character의 멤버 함수 사용
#include <iostream>

using namespace std;


AttackBoost::AttackBoost()
{
    // 공격력 강화 아이템 초기값 설정
    name = "공격력 강화";
    price = 15;
    attackIncrease = 10;
}

string AttackBoost::getName() const
{
    return name;
}

int AttackBoost::getPrice() const
{
    return price;
}

void AttackBoost::use(Character* character)
{
    // ※ Character 클래스에 public: getAttack, setAttack 필요 
    int currentAttack = character->getAttack();
    character->setAttack(currentAttack + attackIncrease);

    cout << name << "을(를) 사용했습니다. 공격력이 영구적으로 " << attackIncrease << " 증가합니다!" << endl;
    cout << "현재 공격력: " << character->getAttack() << endl;
}