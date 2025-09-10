// TextRPGGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include "GameManager.h"

using namespace std;

void setConsoleSize(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. 버퍼 크기 설정
    COORD bufferSize = { (SHORT)width, (SHORT)height };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    // 2. 창 크기 설정
    SMALL_RECT windowSize = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}

int main()
{
    setConsoleSize(180, 150);

    GameManager gm;

    //여기에 초기 화면 아스키아트 출력 코드 입력
    MainArt* mainart = new MainArt();
    gm.drawMainArt(mainart, 1);

    delete mainart;
    
    gm.setCursor(5, 160);
    std::cout << "Press any key to start..." << std::endl;
    _getch();  // 키 입력 대기 (Enter 불필요)

    string nickname;

    while (true)
    {
        gm.setCursor(0, 35); // 입력 시작 위치
        cout << "닉네임을 입력해 주세요(공백 불가): ";

        getline(cin, nickname);

        if (nickname.empty())
        {
            // 이전 입력 지우기
            gm.setCursor(0, 35);
            cout << string(50, ' '); // 50칸 정도 공백으로 덮기
            gm.setCursor(0, 35);      // 다시 커서 위치
            cout << "닉네임은 비워둘 수 없습니다.";
            Sleep(1000);              // 1초 대기
        }
        else if (nickname.find(' ') != string::npos)
        {
            gm.setCursor(0, 35);
            cout << string(50, ' ');
            gm.setCursor(0, 35);
            cout << "공백은 입력할 수 없습니다.";
            Sleep(1000);
        }
        else
        {
            break;
        }
    }


    Character* player = Character::getInstance(nickname);    //싱글톤 사용
    gm.player = player;
    
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
                Monster* monster = gm.generateMonster(player->getLevel());

                gm.battle(player, monster);

                //경험치 획득 문구 출력, 레벨 업 문구 출력
                cout << "50 Exp를 획득했습니다." << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));

                player->setExp(player->getExp() + 50);

                if (player->getExp() == 100)
                {
                    player->levelUp();
                    this_thread::sleep_for(chrono::milliseconds(3500));
                }
            }
            catch (const runtime_error& e)
            {
                system("cls");

                gm.drawDefeat(player, 1);
                cout << "\n" << endl;
                cout << e.what() << endl; //플레이어 사망시 프로그램 종료

                player->displayStatus();
                delete player;
                break;
            }
        
            //전투 종료 후 상점 방문
            system("cls");
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
                    gm.visitShop();
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
                delete player;
                break;
            }
        }
    }
    return 0;
}

