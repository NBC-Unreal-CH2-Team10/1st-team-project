// TextRPGGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <vector>
#include "GameManager.h"

using namespace std;

string nickname;

int main()
{
    cout << "게임을 시작합니다." << endl;

    cout << "닉네임을 입력해 주세요(공백 불가): "; //공백 입력시 예외 처리 추가 필요
    cin >> nickname;

    Character* player = new Character(nickname);        //delete 필수

    while (true)
    {
        if (player->getLevel() != 10) //10레벨이 아닐 경우
        {
            try
            {
                //전투 상황
                Monster* monster = GameManager::generateMonster(player->getLevel);

                GameManager::battle(player, monster);
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

