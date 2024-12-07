#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "unistd.h"
#include "Maze.h"
#include "CharacterMonster.h"

using namespace std;

void mapCreateAlgorithm(int size, int **dungeonMap); // 演算法生成一張地圖，直接更改至dungeonMap中
void printInstruction();

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
//         for (int i = currpos.y + 3; i < currpos.y - 3; i--)
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

//     //檢查角色的移動有沒有撞牆
//     bool mapHittingWall(Character p, Position d)
//     {
//         p.move(d);
//         int x = p.position.x;
//         int y = p.position.y;
//         if (dungeonMap[x][y] == 1)
//         {
//             return false;
//         }
//         else return true;
        
//     }
// };
bool printFileContents();
bool achievementGet(const string achievementName);


int main()
{
    // game.exe execute 開頭台詞
    cout << "..." << endl;
    sleep(2);

    // type "start" to start game, "achievement" to check the previous made cuisine, "delete" to delte game history
    //, "exit" to exit game, cout "invalid command" if the cin command matches none of these

    //=============="start"===============
    string menuCmd;
    while (getline(cin, menuCmd))
    {
        if (menuCmd == "start")
        {
            // type "easy", "normal", "hard" to switch difficulty, and change parameters depends on difficulty
            int difficulty, size, characterLife;
            cout << "Please choose a difficulty: " << "\n";
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
                    characterLife = 30;
                    size = 11;
                    break;
                case 2:
                    characterLife = 25;
                    size = 15;
                    break;
                case 3:
                    characterLife = 20;
                    size = 19;
                    break;
            }

            // 生成地圖=========================================================================================
            Maze* dungeons[3];
            for (int i = 0; i < 3; i++)
            {
                dungeons[i] = new Maze(size);
                dungeons[i]->generate();
            }

            //創建角色
            string characterName;
            cout << "Your name: " << endl;
            getline(cin, characterName);
            Character player = Character(characterName, characterLife, {0,0});

            // cout the background story and instruction to the player

            //以輸入wasd控制玩家移動，每次移動都會更新terminal所顯示的地圖
            //也有其他指令可以輸入，"help"為顯示操作說明，"inventory"為打開背包，"exit"為離開遊戲
            string inGameCmd;
            do
            {
                cin >> std::ws;
                getline(cin, inGameCmd);
                cout << "Enter your command: \n";
                //many if-else cases to determine the command
                int currLevel = 0;
                bool gameEnd = false;
                dungeons[currLevel]->display();
                if (gameEnd == false) {
                    cout << inGameCmd << endl;
                    // dungeons[currLevel]->display();
                    if (inGameCmd == "w" || inGameCmd == "a" || inGameCmd == "s" || inGameCmd == "d")
                    {
                        cout << "moved";
                        char moveCmd = inGameCmd[0];
                        dungeons[currLevel]->movePlayer(moveCmd, gameEnd);
                        dungeons[currLevel]->display();
                    }
                    else if (inGameCmd == "help") 
                    {
                        printInstruction();
                    }
                    else if (inGameCmd == "achievement") 
                    {
                        printFileContents();
                    }
                    else if (inGameCmd == "inventory") 
                    {

                    }
                    else if (inGameCmd == "dvcmd-break") 
                    {
                        //開發用終止迴圈
                        break;
                    }
                    else if (inGameCmd == "exit") 
                    {
                        cout << "the game history will not be preserved, but the achievement will be kept, are you sure?" << endl;
                        cout << "type \"yes\" to exit the game, or type any thing else to cancel" << endl;
                        string exitCmd;
                        getline(cin, exitCmd);
                        if (exitCmd == "yes") 
                        {
                            cout << "see you next time ~" << endl;
                            return 0;
                        }
                        else if (exitCmd == "any thing else")
                        {
                            cout << "Get achievement- \"Seriously?\" " << endl;
                            achievementGet("Seriously?");
                            continue;
                        }
                        else continue;
                    }
                    else break;

                    if (gameEnd && currLevel < 3) 
                    {
                        currLevel++;   
                        gameEnd = false;
                    }
                    
                    cout << gameEnd;
                }
                    
            }
            while (inGameCmd != "exit");

            cout << "..." << endl;
            sleep(2.5);
            cout << "(你似乎來到了一個房間，中間擺著一個鍋釜，牆上的水晶發出微弱又溫和的光線，地板不再粗糙而是經過打磨，看來終於來到了終點的寶物間)" << endl;
            sleep(5.5);
            cout << "乾，都已經夠餓了，還要走迷宮打怪，結果甚至不是拿到煮好的料理，這是什麼鬼餐廳啊" << endl;
            sleep(4.5);
            cout << "這是什麼? \"魔法鍋子 將食材放進以自動料理\"" << endl;
            sleep(4);
            cout << "什麼鬼，不就自動料理機，這旁邊甚至有插電哎，這算什麼寶物間啊" << endl;
            sleep(4.2);
            cout << "算了真的好餓，把背包的食材丟進去看看吧" << endl;
            sleep(4);
            
            cout << "請選擇將三樣食材放入鍋中: " << endl;
            // player.cooking();
        }

        //================"achievement"=====================
        else if (menuCmd == "achievement")
        {
            printFileContents();
        }

        //=================="exit"=======================
        else if (menuCmd == "exit")
        {
            cout << "the game history will not be preserved, but the achievement will be kept, are you sure?" << endl;
            cout << "type \"yes\" to exit the game, or type any thing else to cancel" << endl;
            string exitCmd;
            getline(cin, exitCmd);
            if (exitCmd == "yes") 
            {
                cout << "see you next time ~" << endl;
                return 0;
            }
            else if (exitCmd == "any thing else")
            {
                cout << "Get achievement- \"Seriously?\" " << endl;
                //achievement add
                continue;
            }
            else continue;
        }
    }
    
}

void printInstruction()
{
    cout << "-help- show this instruction" << endl;
    cout << "-inventory- open your backpack" << endl;
    cout << "-achievement- show your achievement" << endl;
    cout << "-w- move upward" << endl;
    cout << "-a- move left" << endl;
    cout << "-s- move backward" << endl;
    cout << "-d- move right" << endl;
    cout << "-exit- exit the game" << endl;
}

//獲得成就(generated by chatgpt)
bool achievementGet(const string achievementName)
{
    const string fileName = "achievements.txt";

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    vector<string> lines;
    string line;

    // Read each line and store it in a vector
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    // Close the input file
    inFile.close();

    // Modify the specific boolean value
    for (size_t i = 0; i < lines.size() - 1; i += 2) { // Iterate only over even lines containing the boolean
        if (lines[i].find(achievementName) != string::npos) { // Replace "Ending" with the achievement you want to change
            if (lines[i][0] == '0') {
                lines[i][0] = '1'; // Change '0' to '1' to mark as completed
            } 
        }
    }

    // Open the file for writing (overwrite mode)
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    // Write the modified content back to the file
    for (const auto &modifiedLine : lines) {
        outFile << modifiedLine << "\n";
    }

    // Close the output file
    outFile.close();

    // cout << "Achievement status successfully modified." << endl;
    return true;
}

bool printFileContents() 
{
    const string fileName = "achievements.txt";

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    string line1, line2;
    while (getline(inFile, line1)) {
        // Skip the boolean flag (first element of each pair of lines)
        bool achievementComplete = false;
        if (line1[0] == '1') {
            achievementComplete = true;
            line1 = line1.substr(2); // Remove the leading boolean and space
        }
        else if (line1[0] == '0')
        {
            line1 = line1.substr(2);
        }

        // Read the description line
        if (getline(inFile, line2)) {
            if (achievementComplete)
            {
                cout << line1 << " - " << line2 << endl;
            }
            else
            {
                cout << "??? - ???" << endl;
            }         
        }
        
    }

    inFile.close();
}