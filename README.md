# TextRPGGame

**프로젝트 제작 기간** : 2025.09.03 ~ 2025.09.10

# 프로젝트 소개

이 게임은 무수한 에러 끝에 보스몬스터를 쓰러뜨리는데 성공한 김전사32호기의 이야기를
담고 있습니다.

## 소제목

김전사32호기의 모험

# 프로젝트 목표

그 동안 배운 C++ 문법들을 총동원해서 간단한 게임을 만들어 보고 팀 프로젝트를 진행하면서 소통의 중요성과 git 사용법에 대해 배운다.

# 프로젝트 구조
```less
TextRPGGAme
┗ src
  ├─ TextRPGGame.cpp
  ├─ TextRPGGame.sln
  │                          
  ├─ Character
  │    ├─ Character.cpp
  │    └─ Character.h
  │      
  ├─ GameManager
  │    ├─ GameManager.cpp
  │    ├─ GameManager.h
  │    └─ MainArt.h
  │      
  ├─ Item
  │    ├─ AttackBoost.cpp
  │    ├─ AttackBoost.h
  │    ├─ HealthPotion.cpp
  │    ├─ HealthPotion.h
  │    ├─ inventory.cpp
  │    ├─ inventory.h
  │    ├─ item.h
  │    ├─ Shop.cpp
  │    └─ Shop.h
  │      
  └─ Monster
       ├─ BossMonster.cpp
       ├─ BossMonster.h
       ├─ Goblin.cpp
       ├─ Goblin.h
       ├─ Monster.h
       ├─ Orc.cpp
       ├─ Orc.h
       ├─ Troll.cpp 
       └─ Troll.h
```
# 추가 구현
- 도트 아트를 활용하여 게임 장면을 추가했습니다.
