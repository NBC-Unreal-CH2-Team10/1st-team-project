#include <iostream>
#include <string>
#include <random>
#include "Goblin.h"

using namespace std;

Goblin::Goblin(int level)
{
	name = "Goblin";

	//랜덤 범위의 값 코드 chat Gpt의 도움을 받아서 작성했습니다.
	random_device rd;	 //시드 생성 (난수 시드를 만드는 장치)
	mt19937 gen(rd());	 //엔진 초기화 (Mersenne Twister 19937 알고리즘 기반의 난수 생성기)

	uniform_int_distribution<int> healthDist(level * 20, level * 30);	//범위 설정 (level * 20 ~ level * 30)
	uniform_int_distribution<int> attackDist(level * 5, level * 10);	//범위 설정 (level * 5 ~ level * 10)

	health = healthDist(gen);
	attack = attackDist(gen);
}

string Goblin::getName() const
{
	return name;
}
int Goblin::getHealth() const
{
	return health;
}
int Goblin::getAttack() const
{
	return attack;
}


//몬스터 피격
void Goblin::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0이 되면 죽어야하니 데미지가 오버될 떄 0으로 설정
}

//아이템 드랍
DropItem* Goblin::dropItem()
{
	return new DropItem("sword");
}