#include <iostream>
#include <string>
#include "Orc.h"
#include <random>

using namespace std;

Orc::Orc(int level)
{
	name = "Orc";

	//랜덤 범위의 값 코드 chat Gpt의 도움을 받아서 작성했습니다.
	random_device rd;	 //시드 생성 (난수 시드를 만드는 장치)
	mt19937 gen(rd());	 //엔진 초기화 (Mersenne Twister 19937 알고리즘 기반의 난수 생성기)

	uniform_int_distribution<int> healthDist(level * 20, level * 30);	//범위 설정 (level * 20 ~ level * 30)
	uniform_int_distribution<int> attackDist(level * 5, level * 10);	//범위 설정 (level * 5 ~ level * 10)

	health = healthDist(gen);
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


//몬스터 피격
void Orc::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0이 되면 죽어야하니 데미지가 오버될 떄 0으로 설정
}

//아이템 드랍 + 경험치 추가 + 골드 드랍 추가
DropAll* Orc::dropAll() {
	int exp = 50; // 경험치는 고정값으로 넣었습니다.



	//골드는 체력,공격력 설정과 같은 방법으로 랜덤으로 드랍하게 했습니다.
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> goldDist(1, 5);  // 1~5골드
	int gold = goldDist(gen);



	//FMath에 RandRange는 언리얼 전용 라이브러리라 사용하지 못한다고 하네요.. 
	uniform_int_distribution<int> chance(0, 1);
	DropItem* dropItem = nullptr;
	if (chance(gen) == 1) {
		dropItem = new DropItem("HealthPotion");
	}

	return new DropAll(dropItem, gold, exp);
}