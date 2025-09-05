// TextRPGGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <vector>
#include "GameManager.h"

using namespace std;



int main()
{
    cout << "게임을 시작합니다." << endl;

    cout << "닉네임을 입력해 주세요(공백 불가): "; //공백 입력시 예외 처리 추가 필요
    string nickname;

    getline(cin, nickname); //일단은 공백 포함에서 모두 받음

    if (nickname.find(' ') != string::npos)  //공백이 있는지 확인
    {
        cout << "공백은 입력할 수 없습니다." << endl;
    }
    else
    {
        Character* player = new Character(nickname);        //delete 필수
    }

    int killmonster = 0;

    while (true)
    {
        system("clear"); //콘솔 로그 지우기

        //화면 최상단에 캐릭터 정보 출력
        //닉네임/체력/레벨/경험치/골드/처치한 몬스터 수

        cout << "닉네임: " << player->getName() << " | 체력: ";
        GameManager::drawHealthbar(player->getHP(), player->getMaxHp());
        cout << " " << player->getHP() << "/" << player->getMaxHp();
        cout << " | 레벨: " << player->getLevel(); 
        cout << " | 경험치: " << player->getExp() << "/100";
        cout << " | 골드: " << player->getGold();
        cout << " | 처치한 몬스터 수: " << killmonster << "마리\n" << endl;

        if (player->getLevel() != 10) //10레벨이 아닐 경우
        {
            try
            {
                //전투 상황
                Monster* monster = GameManager::generateMonster(player->getLevel);

                GameManager::battle(player, monster);

                //몬스터 처치 -> 경험치와 골드 아이템 획득

                ++killmonster; //처치한 몬스터 수

                //골드 획득
                //몬스터마다 골드 다르게 하고 dropGold 같은 함수로 드랍 골드 확인
                //플레이어에 addGold 함수로 골드 추가, 골드 획득 문구 출력
                player->addGold(monster->dropGold());
                player->addInventory(monster->dropItem());

                //경험치 획득 문구 출력, 레벨 업 문구 출력
                player->addExp(50);

                if (player->getExp() == 100)
                {
                    player->levelUp();
                }
            }
            catch (const runtime_error& e)
            {
                cout << e.what() << endl; //플레이어 사망시 프로그램 종료
            }
        
            //전투 종료 후 상점 방문
            GameManager::visitShop(player);
        }
        else //10레벨 도달 후 보스전 진입
        {
            try
            {
                //전투 상황
                Monster* monster = GameManager::generateBossMonster(); //보스 몹 생성

                GameManager::battle(player, monster);

                cout << "보스 몬스터를 처치했습니다!" << endl;
                break;
            }
            catch (const runtime_error& e)
            {
                cout << e.what() << endl; //플레이어 사망시 프로그램 종료
            }
        }
    }
    return 0;
}

