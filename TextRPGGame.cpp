// TextRPGGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <vector>
#include <conio.h>
#include "GameManager.h"

using namespace std;



int main()
{
    //여기에 초기 화면 아스키아트 출력 코드 입력
    
    std::cout << "Press any key to start..." << std::endl;
    _getch();  // 키 입력 대기 (Enter 불필요)

    string nickname;

    while (true)
    {
        cout << "닉네임을 입력해 주세요(공백 불가): "; //공백 입력시 예외 처리 추가 필요

        getline(cin, nickname); //일단은 공백 포함에서 모두 받음

        if (nickname.find(' ') != string::npos)  //공백이 있는지 확인
        {
            cout << "공백은 입력할 수 없습니다." << endl;
        }
        else
        {
            break;
        }
    }

    Character* player = Character::getInstance(nickname);    //싱글톤 사용

    GameManager gm;

    while (true)
    {
        system("cls"); //콘솔 로그 지우기

        //화면 최상단에 캐릭터 정보 출력
        //닉네임/체력/레벨/경험치/골드/처치한 몬스터 수

        gm.playerUI(player);

        if (player->getLevel() != 10) //10레벨이 아닐 경우
        {
            try
            {
                //전투 상황
                Monster* monster = gm.generateMonster(player->getLevel);

                gm.battle(player, monster);

                //경험치 획득 문구 출력, 레벨 업 문구 출력
                cout << "50 Exp를 획득했습니다." << endl;

                player->setExp(player->getExp() + 50);

                if (player->getExp() == 100)
                {
                    player->levelUp();
                }
            }
            catch (const runtime_error& e)
            {
                system("cls");

                gm.drawDefeat(player, 1);
                cout << "\n" << endl;
                cout << e.what() << endl; //플레이어 사망시 프로그램 종료

                player->displayStatus();
            }

            system("cls");
        
            //전투 종료 후 상점 방문
            gm.setCursor(0, 0);
            gm.playerUI(player);
            cout << "\n" << endl;

            string answer;

            while (true)
            {
                cout << "상점을 방문하시겠습니까? (Y/N)" << endl;
                cin >> answer;

                if (cin.fail()) //잘 못된 타입이 입력되면 true 반환
                {
                    cin.clear(); // 오류 상태 초기화
                    cin.ignore(1000, '\n'); // 잘못된 입력 버리기
                    cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
                    continue;
                }

                if (answer == "Y" || answer == "y")
                {
                    gm.visitShop(player);
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        else //10레벨 도달 후 보스전 진입
        {
            try
            {
                //전투 상황
                Monster* monster = gm.generateBossMonster(player->getLevel()); //보스 몹 생성

                gm.battle(player, monster);

                cout << "보스 몬스터를 처치했습니다!" << endl;
                break;
            }
            catch (const runtime_error& e)
            {
                system("cls");

                gm.drawDefeat(player, 1);
                cout << "\n" << endl;
                cout << e.what() << endl; //플레이어 사망시 프로그램 종료

                player->displayStatus();
            }
        }
    }
    return 0;
}

