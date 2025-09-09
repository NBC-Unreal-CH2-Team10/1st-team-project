#include <iostream>
#include <string>
#include "BossMonster.h"
#include <random>
#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

BossMonster::BossMonster(int level)
{
	name = "BossMonster";

	art = {};

	//랜덤 범위의 값 코드 chat Gpt의 도움을 받아서 작성했습니다.
	random_device rd;	 //시드 생성 (난수 시드를 만드는 장치)
	mt19937 gen(rd());	 //엔진 초기화 (Mersenne Twister 19937 알고리즘 기반의 난수 생성기)

	uniform_int_distribution<int> healthDist(level * 30, level * 45);	//범위 설정 (level * 30 ~ level * 45)
	uniform_int_distribution<int> attackDist(level * 10, level * 15);	//범위 설정 (level * 10 ~ level * 15)

	health = healthDist(gen);

	maxHealth = health;

	attack = attackDist(gen);
}

string BossMonster::getName() const
{
	return name;
}
int BossMonster::getHealth() const
{
	return health;
}
int BossMonster::getAttack() const
{
	return attack;
}
int BossMonster::getMaxHealth() const
{
	return maxHealth;
}
string BossMonster::getart() const
{
	return art;
}


//몬스터 피격
void BossMonster::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0이 되면 죽어야하니 데미지가 오버될 떄 0으로 설정
}


//순수가상함수를 사용해서 일단 구현만 해두었습니다. 값x
Item* BossMonster::dropItem() {
	return new HealthPotion();
}

int BossMonster::getExp() const {
	return 0;
}

int BossMonster::getGold() const {
	return 0;
}