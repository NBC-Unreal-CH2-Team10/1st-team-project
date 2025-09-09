#include <iostream>
#include <string>
#include "Orc.h"
#include <random>
#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

Orc::Orc(int level)
{
	name = "Orc";

	exp = 50;

	art = {};

	//랜덤 범위의 값 코드 chat Gpt의 도움을 받아서 작성했습니다.
	random_device rd;	 //시드 생성 (난수 시드를 만드는 장치)
	mt19937 gen(rd());	 //엔진 초기화 (Mersenne Twister 19937 알고리즘 기반의 난수 생성기)

	uniform_int_distribution<int> healthDist(level * 20, level * 30);	//범위 설정 (level * 20 ~ level * 30)
	uniform_int_distribution<int> attackDist(level * 5, level * 10);	//범위 설정 (level * 5 ~ level * 10)

	uniform_int_distribution<int> goldDist(1, 5);  // 1~5골드
	gold = goldDist(gen);

	health = healthDist(gen);

	maxHealth = health;

	attack = attackDist(gen);
}

string Orc::getName() const
{
	return name;
}
int Orc::getHealth() const
{
	return health;
}
int Orc::getAttack() const
{
	return attack;
}
int Orc::getMaxHealth() const
{
	return maxHealth;
}
int Orc::getExp() const
{
	return exp;
}
int Orc::getGold() const
{
	return gold;
}
vector<string>& Orc::getArt()
{
	return art;
}


//몬스터 피격
void Orc::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0이 되면 죽어야하니 데미지가 오버될 떄 0으로 설정
}

//아이템 드랍
Item* Orc::dropItem() {

	random_device rd;
	mt19937 gen(rd());

	//FMath에 RandRange는 언리얼 전용 라이브러리라 사용하지 못한다고 하네요.. 
	uniform_int_distribution<int> dist(0, 99);  // 0~99 난수 생성

	int per = dist(gen);

	//확률에 따른 드랍아이템
	if (per < 40) {
		return new HealthPotion();  // 40% hp drop
	}
	else if (per < 60) {
		return new AttackBoost();  // 20% AB drop
	}
	else {
		return nullptr;  // 40% drop X
	}

}