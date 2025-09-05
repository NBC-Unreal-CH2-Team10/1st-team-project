#pragma once
#include <string>

using namespace std;

class Character;
// Character 클래스 전방 선언
// 모든 아이템의 기반이 되는 '추상 클래스'
class Item
{
protected:
    string name;

public:
    Item(const string& name) : name(name) {}
    // 부모 포인터로 자식 객체를 delete 할 때를 대비한 '가상 소멸자'
    virtual ~Item() = default;

    string getName() const { return name; }

    // 순수 가상 함수: Item을 상속받는 자식 클래스는 반드시 use() 함수를 만들어야 한다.
    virtual void use(Character* character) = 0;
};