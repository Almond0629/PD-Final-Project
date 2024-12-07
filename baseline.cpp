#include <iostream>
#include <string>
#include "Maze.h"
#include "characterMonster.h"

using namespace std;

// struct Position
// {
//     int x;
//     int y;

//     bool operator==(const Position& pos2) const
//     {
//         if (this->x == pos2.x && this->y == pos2.y) return true;
//         else return false;
//     }
// };

// class Monster
// {
// private:
//     string name;
//     int life;
//     int atk;
// public:
//     Monster(/* args */);
//     ~Monster();

//     //當玩家和怪物戰鬥
//     void fight(player)
//     {
//         /* code */
//     }
// };
// //WARNING! 暫時想不到怪物的中類及區別

// class Character
// {
// private:
//     int life;
//     int currentLevel;
//     //inventory (這邊想用vector語法寫? 但我還不是很熟悉 先放著 之後再來重看一下影片)
    
// public:
//     Position position; // 紀錄玩家ㄉ位置

//     //constructor
//     Character() : currentLevel(0), x(0), y(0) //玩家自最左下角開始遊戲
//     {
//     }

//     int getCurrentLevel() {return currentLevel;}
//     void setCurrentLevel() {currentLevel++;}

//     //玩家移動
//     void move(int direction)
//     {
//         /* code */
//     }

//     //重設玩家位置
//     void resetPosition()
//     {
//         position = {0,0}
//     }

// }

// class Map
// {
// private:
//     int **dungeonMap; // 以二維陣列紀錄整張地圖樣子
//     const int mapSize;
//     int **itemPosition;    // 以稀疏矩陣紀錄補給品/錢幣在地圖上的生成位置，有東西則為1，無東西則為0
//     int itemCnt;           // 補給品/錢幣的總數 兩者比例為1:5
//     const int maxMosterCnt; //根據難易度每張地圖最多遇到怪物數量
//     int encouteredMonsterCnt; //已遇到的怪物數量
//     Monster** monsterList; //每個element代表一隻怪物，可能為不同種，在地圖中遇到的怪物是按照這份list依序遇到
    
// public:
//     //constructor
//     map(int size, int monstercnt) : mapSize(size), mosterCnt(monstercnt), encouteredMonsterCnt(0)
//     {
//         // 迷宮生成
//         mapCreateAlgorithm(size, dungeonMap);

//         // 根據生成的迷宮，生成補給品/錢幣的位置，直接更改itemPosition
//         itemCreateAlgorithm(dungeonMap, itemPosition);

//         //隨機從已存在的怪物中指派至monsterList，依序遇到的怪物則是按照這份list遇到
//         for (int i = 0; i < maxMosterCnt; i++)
//         {
//             /* code */
//         }
        

//     }

//     void mapPrint(Position currpos)
//     {
//         //根據dungeonMap, itemPosition, monsterPosition，顯示以玩家為中心附近7*7的地圖樣貌
//         //WARNING:邊界情況未考慮
//         for (int i = currpos.y + 3; i < currpos - 3; i--)
//         {
//             for (int j = currpos.x + 3; j < currpos.x - 3; j--)
//             {
//                 if (dungeonMap[i][j] == 1) cout << "▧ ";
//                 else if (itemPosition[i][j] == 1) cout << "※ ";
//                 else if (i == currpos.y && j == currpos.x) cout << "● ";
//                 else cout << "　";
//             }
//         }
//     }

//     //改變地圖的資料，例如當玩家走到戰利品點時，將該點itemPosition改為0，並將獲得的戰利品加入進inventory。
//     //或是走到怪物生成點時，觸發戰鬥
//     void mapUpadate(Character player)
//     {   
//         //get item
//         /* code */

//         //moster encouter
//         //隨機生成一個數字，設定上是每走一步有10%機率遇到怪物，根據難易度每張地圖最多遇到6 9 12隻
//         int randomNum;
//         if (randomNum % 10 == 0) 
//         {
//             monsterList[encouteredMonsterCnt].fight(player);
//             encouteredMonsterCnt++;
//         }
        
//     }
// }

int main()
{
    // game.exe execute
    cout << "Welcome to the Maze Game!\n";
    cout << "Use W/A/S/D to move. Press Q to quit.\n";

    // type "start" to start game, "achievement" to check the previous made cuisine, "delete" to delete game history
    //, "exit" to exit game, cout "invalid command" if the cin command matches none of these

    //=============="start"===============
    // type "easy", "normal", "hard" to switch difficulty
    int difficulty, size;
    cout << "Please choose a difficulty:" << "\n";
    cout << "Enter 1 for easy" << "\n";
    cout << "Enter 2 for normal" << "\n";
    cout << "Enter 3 for hard" << "\n";
    
    while (difficulty != 1 && difficulty != 2 && difficulty != 3)
    {
        cin >> difficulty;
        if (difficulty != 1 && difficulty != 2 && difficulty != 3)
            cout << "Invalid difficulty, please type again";
    }

    switch (difficulty) {
        case 1:
            size = 11;
            break;
        case 2:
            size = 15;
            break;
        case 3:
            size = 19;
            break;
    }

    Maze maze(size);
    maze.generate();
    char command;

    bool gameEnd = false;
    while (gameEnd == false) {
        maze.display();
        cout << "Enter your move: ";
        cin >> command;

        if (command == 'Q' || command == 'q') {
            cout << "Game Over! You collected " << maze.collectedPrizes << " prizes.\n";
            break;
        }

        maze.movePlayer(command, gameEnd);
    }
    cout << "You win!" << endl;


    // // 生成地圖
    // Map **dungeons = new Map[3];
    // for (int i = 0; i < 3; i++)
    // {
    //     dungeons[i] = new Map(mapSize);
    // }

    // Character player = new Character();

    // // cout the background story and instruction to the player

    // //以輸入wasd控制玩家移動，每次移動都會更新terminal所顯示的地圖
    // //也有其他指令可以輸入，"help"為顯示操作說明，"inventory"為打開背包，"exit"為離開遊戲
    // string cmd;
    // while(cin >> cmd)
    // {
    //     //many if-else cases to determine the command
    //         //if cmd == w a s d
    //         Character.move()
    //         int currLevel = player.getCurrentLevel();
    //         dungeons[currLevel].mapUpadate(player);
    //         dungeons[currLevel].mapPrint();

    //         //若玩家抵達終點且完成所有地圖，進結局
    //         if (player.position == END_POSITION && currLevel == 3)
    //         {
    //             /* code */
    //             break;
    //         }
    //         //若玩家抵達終點
    //         else if (player.position == END_POSITION)
    //         {
    //             player.setCurrentLevel();
    //             player.positionReset(); 
    //         }

    //         //if cmd == "help"

    //         //if cmd == "achievement"

    //         //if cmd == "inventory"

    //         //if cmd == "exit"
    // }

    // //================"achievement"=====================

    // //==================="delete"=======================

    // //=================="exit"=======================
}