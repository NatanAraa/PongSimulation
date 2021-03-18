/*
 *   Copyright (c) 2021 Araa
 *   All rights reserved.
 */

// 4210191023_NatanAndro

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <mutex>
#include "scores.h"
#include "players.h"

using namespace std;

//Score global variabel
Score score(0, 0);

mutex m;

//Player Hit Ball Randomizer
void PlayerHit(Player *players, bool *roundOver)
{
    m.lock();
    int *i = new int;
    srand((int)i);
    delete i;
    players->SetHits(rand() % 101);
    m.unlock();

    //UI
    cout << "Hits Points : " << players->GetHits();
    if (players->GetPlayers() == 0)
    {
        cout << " ,Player X ";
    }
    else
    {
        cout << " ,Player Y ";
    }

    //cek miss ball
    if (players->GetHits() <= 50)
    {
        if (players->GetPlayers() == 0)
        {
            score.AddScoreY();
        }
        else
        {
            score.AddScoreX();
        }
        cout << "Ball Miss!" << endl;

        *roundOver = true;
    }
    else
    {
        cout << "Ball Hit!" << endl;
    }

    this_thread::sleep_for(chrono::seconds(1));
}

void FirstTurn(int *players)
{
    int *i = new int;
    srand((int)i);
    delete i;
    *players = rand() % 2;
}

int main()
{
    //Title
    cout << ">>>> Pong Simulations <<<<" << endl;
    srand(time(0));
    Player playerX(0);

    //Clone players
    Player playerY = playerX;

    int currentRound = 1;
    //Main Loop
    while (score.XScore() < 10 && score.YScore() < 10)
    {
        int RandomStart;
        thread RandomFirst(FirstTurn, &RandomStart);
        RandomFirst.join();
        bool roundIsOver = false;
        cout << "Now Round : " << currentRound << endl;
        
        //looping round
        while (roundIsOver == false)
        {
            if (RandomStart == 0)
            {
                cout << "Player X First" << endl;
                //X Player Thread
                thread playerXThread(PlayerHit, &playerX, &roundIsOver);
                playerXThread.join();

                //miss cek
                if (roundIsOver == true)
                {
                    currentRound++;
                    break;
                }


                //Y Player Thread
                thread playerYThread(PlayerHit, &playerY, &roundIsOver);
                playerYThread.join();


                //miss cek
                if (roundIsOver == true)
                {
                    currentRound++;
                    break;
                }
            }
            else if (RandomStart == 1)
            {
                cout << "Player Y First" << endl;

                //Y Players Thread
                thread playerYThread(PlayerHit, &playerY, &roundIsOver);
                playerYThread.join();


                //miss cek
                if (roundIsOver == true)
                {
                    currentRound++;
                    break;
                }

                //X Player Thread
                thread playerXThread(PlayerHit, &playerX, &roundIsOver);
                playerXThread.join();


                // miss cek
                if (roundIsOver == true)
                {
                    currentRound++;
                    break;
                }
            }
        }
    }
    //print final score
    cout << "\nFinal Result" << endl;
    if (score.XScore() >= 10)
    {
        cout << "Player X WIN with Score :  " << score.XScore() << "-" << score.YScore() << endl;
    }
    else
    {
        cout << "Player Y WIN with Score :  " << score.YScore() << "-" << score.XScore() << endl;
    }

    return 0;
}