#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include<ctime>
#include<string>
using namespace std;
struct player
{
    char name[50];
    int score;
};
void menu();
void selectfrom();
void spawnRandom(int **arr, int size);
int **initializingGrid(int size);
void displayGame( int **arr, int size);
bool PushBoxes(int **arr, int size);
bool combineBoxes(int **arr, int size, int &score);
void reversingRows(int **arr, int size);
void transposeRowsCols(int **arr, int size);
bool movekeyA(int **arr, int size, int &score);
bool movekeyD(int **arr, int size, int &score);
bool movekeyW(int **arr, int size, int &score);
bool movekeyS(int **arr, int size, int &score);
bool loseOrWin(int **arr, int size);
void updateScores(string filename, player pl, int diff);
void updateScoresTextFile(string filename, player pl, int diff);
void displayAllLeaderboard(string filename);
void displayTopNPlayers(string filename, int n);
void displayTopNScores(string filename, string nameof, int n);
void DeallocateGame(int **arr, int size);
int main()
{
    srand(time(0));
    cout<<"\n-------- Welcome to the 2048 Game! --------\n\n";
    menu();
    struct player PL;
    cout<<"Enter your Username (No Spaces Allowed): ";
    cin>>PL.name;
    int size;
    string mode;
    PL.score = 0;
    cout<<"Choose your Difficulty Mode ( Easy | Medium | Hard ): ";
    cin>>mode;
    while(mode != "Easy"&& mode != "easy" && mode != "Medium" && mode != "medium" && mode != "Hard" && mode != "hard")
    {
        cout<<"Invalid Input! Try small letters only.\n";
        cout<<"Choose your Difficulty( easy | medium | hard ): ";
        cin>>mode;
    }
    if(mode == "Easy" || mode == "easy")
    {
        size = 6;
    }
    else if(mode == "Medium" || mode == "medium")
    {
        size = 10;
    }
    else if(mode == "Hard" || mode == "hard")
    {
        size = 15;
    }
    int **array = initializingGrid(size);
    bool lose = false;
    while(!lose)
    {
        system("cls");
        displayGame(array, size);
        cout<<"\nScore: "<<PL.score<<"\n";
        char UserInput;
        cout<<"Make a Move (W/A/S/D/Q) W = UP, A = LEFT, S = DOWN, D = RIGHT, Q = QUIT: ";
        cin>>UserInput;
        while(UserInput != 'W'&& UserInput != 'A'&& UserInput != 'S'&& UserInput != 'D' && UserInput != 'Q')
        {
            cout<<"Invalid Move! Use Capital W-A-S-D-Q keys only!\n";
            cout<<"Make a Move(W/A/S/D/Q): ";
            cin>>UserInput;
        }
        bool moved = false;
        if(UserInput == 'W')
        {
            moved = movekeyW(array,size,PL.score);
        }
        else if(UserInput == 'A')
        {
            moved = movekeyA(array,size,PL.score);
        }
        else if(UserInput == 'D')
        {
            moved = movekeyD(array,size,PL.score);
        }
        else if(UserInput == 'S')
        {
            moved = movekeyS(array,size,PL.score);
        }
        else if(UserInput == 'Q')
        {
            cout<<"You have Quit the Game.\n";
            break;
        }
        else 
        {
            cout<<"Invalid move!\n";
            continue;
        }

        if(moved)
        {
            spawnRandom(array, size);
        }
        if(!loseOrWin(array, size))
        {
            system("cls");
            displayGame(array, size);
            break;
        }

    }
    cout<<"Game Over!\nYour Score: "<<PL.score;
    string filename = "leaderboard.bin";
    string Tfilename = "leaderboard.txt";
    int choice;
    cout<<"\nNow you can Access our LeaderBoard.\n";
    selectfrom();
    cout<<"Enter your choice: ";
    cin>>choice;
    while(choice < 0 || choice > 3)
    {
        cout<<"Invalid Input! Enter your choice: ";
        cin>>choice;
    }
    int N;
    string NameSearch;
    switch(choice)
    {
        case 0:
        break;
        case 1:
        updateScores(filename, PL, size);
        updateScoresTextFile(Tfilename, PL, size);
        displayAllLeaderboard(filename);
        cout<<"You can see the Leaderboard in the file (leaderboardDisplay.txt).\n";
        break;
        case 2:
        cout<<"Enter the Top N number of players you want to view: ";
        cin>>N;
        while(N < 1)
        {
            cout<<"Invalid Input!\nEnter the Top N scores of the Player to View: ";
            cin>>N;
        }
        updateScores(filename, PL, size);
        updateScoresTextFile(Tfilename, PL, size);
        displayTopNPlayers(filename, N);
        cout<<"You can see the Leaderboard in the file (leaderboardDisplay.txt).\n";
        break;
        case 3:
        cout<<"Enter the Username of the Player's Score to View: ";
        cin>>NameSearch;
        cout<<"Enter the Top N scores of the Player to View: ";
        cin>>N;
        while(N < 1)
        {
            cout<<"Invalid Input!\nEnter the Top N scores of the Player to View: ";
            cin>>N;
        }
        updateScores(filename, PL, size);
        updateScoresTextFile(Tfilename, PL, size);
        displayTopNScores(filename, NameSearch, N);
        cout<<"You can see the Leaderboard in the file (leaderboardDisplay.txt).\n";
    }
    DeallocateGame(array, size);
   
    return 0;
}
void menu()
{
    cout<<"GAME RULES: \n";
    cout<<"1. There are 3 difficulty modes\n";
    cout<<"2. Size of Grid Varies with the Difficulty mode\n";
    cout<<"3. Easy - 6 x 6 , Medium - 10 x 10 , Hard - 15 x 15\n";
    cout<<"4. The Player will Lose if the Grid is Full and if there are no moves possible.\n";
    cout<<"5. The Player's Score will be calculated on the basis of the tile the player has merged.\n";
    cout<<"6. Players can also view the Leaderboard after finshing the game.\n";
    cout<<"ENJOY THE GAME!\n\n";
}
void selectfrom()
{
    cout<<"The LeaderBoard can be Viewed in the file.\n";
    cout<<"Enter 0 if you do NOT want to View the LeaderBoard.\n";
    cout<<"Enter 1 if you want to View the Whole LeaderBoard.\n";
    cout<<"Enter 2 if you want to View the Top N Players from the LeaderBoard.\n";
    cout<<"Enter 3 if you want to View the Top N Scores of a specific Player from the LeaderBoard.\n";
}
int **initializingGrid(int size)
{
    int **arr = new int*[size];
    for(int i = 0; i < size; i++)
    {
        arr[i] = new int[size];
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }
    spawnRandom(arr, size);
    spawnRandom(arr, size);
    return arr;
}
void spawnRandom(int **arr, int size)
{
    int row, cols;
    do
    {
        row = rand() % size;
        cols = rand() % size;
    }
    while(arr[row][cols] != 0);
    int num = rand() % 10;
    int Rnum;
    if(num == 0)
    {
        Rnum = 4; 
    }
    else
    {
        Rnum = 2;
    }
    arr[row][cols] = Rnum;
}
void displayGame( int **arr, int size)
{
    cout<<"\n2048 GAME\n\n";
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(arr[i][j] == 0)
            {
                cout<<"-\t";
            }
            else
            {
                cout<<arr[i][j]<<"\t";
            }
        }
        cout<<"\n\n";
    }
}
bool PushBoxes(int **arr, int size)
{
    bool done = false;
    for(int i = 0; i < size; i++)
    {
        int position = 0;
        int *temp = new int[size];
        for(int j = 0; j < size; j++)
        {
            temp[j] = 0;
        }
        for(int j = 0; j < size; j++)
        {
            if(arr[i][j] != 0)
            {
                temp[position] = arr[i][j];
                if(j != position)
                {
                    done = true;
                }
                position++;
            }
        }
        for(int j =0; j < size; j++)
        {
            arr[i][j] = temp[j];
        }
        delete[]temp;
    }
    return done;
}
bool combineBoxes(int **arr, int size, int &score)
{
    bool done = false;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size - 1; j++)
        {
            if(arr[i][j] == arr[i][j+1] && arr[i][j] != 0)
            {
                arr[i][j] = arr[i][j] * 2;
                arr[i][j + 1] = 0;
                score = score + arr[i][j];
                done = true;
            }
        }
    }
    return done;
}
void reversingRows(int **arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        int start = 0, end = size - 1;
        while(start < end)
        {
            int temp = arr[i][start];
            arr[i][start] = arr[i][end];
            arr[i][end]= temp;
            start++;
            end--;
        }
    }
}
void transposeRowsCols(int **arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            int temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}
bool movekeyA(int **arr, int size, int &score)
{
    bool flag1 = PushBoxes(arr,size);
    bool flag2 = combineBoxes(arr, size, score);
    bool flag3 = PushBoxes(arr, size);
    return (flag1 || flag2 || flag3);
}
bool movekeyD(int **arr, int size, int &score)
{
    reversingRows(arr, size);
    bool move= movekeyA(arr,size,score);
    reversingRows(arr, size);
    return move;
}
bool movekeyW(int **arr, int size, int &score)
{
    transposeRowsCols(arr, size);
    bool move = movekeyA(arr,size,score);
    transposeRowsCols(arr, size);
    return move;
}
bool movekeyS(int **arr, int size, int &score)
{
    transposeRowsCols(arr, size);
    reversingRows(arr, size);
    bool move = movekeyA(arr,size,score);
    reversingRows(arr, size);
    transposeRowsCols(arr, size);
    return move;
}
bool loseOrWin(int **arr, int size)
{
    bool flag = false;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(arr[i][j] == 0)
            {
                flag = true;
            }
        }
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size-1; j++)
        {
            if(arr[i][j] == arr[i][j+1])
            {
                flag = true;
            }
        }
    }
    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(arr[i][j] == arr[i+1][j])
            {
                flag = true;
            }
        }
    }
    return flag;
}
void updateScores(string filename, player pl, int diff)
{
   ofstream out(filename,ios::binary | ios::app);
   out.write((char*)&pl, sizeof(pl));
   out.write((char*)&diff, sizeof(diff));
   out.close();
}
void updateScoresTextFile(string filename, player pl, int diff)
{
   ofstream out(filename, ios::app);
   out<<pl.name<<" "<<pl.score<<" "<<diff<<"\n";
   out.close();
}
void displayTopNPlayers(string filename, int n)
{
    player P[100];
    int diff[100];
    int a = 0;
    ifstream in(filename, ios::binary);
    while(in.read((char*)&P[a], sizeof(player)))
    {
        in.read((char*)&diff[a], sizeof(int));
        a++;
    }
    in.close();
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = i + 1; j < a; j++)
        {
            if(P[j].score > P[i].score)
            {
                player temp = P[i];
                P[i] = P[j];
                P[j] = temp;
                int temp1 = diff[i];
                diff[i] = diff[j];
                diff[j] = temp1;
            }
        }
    }
    ofstream out ("leaderboardDisplay.txt", ios::out);
    out<<"\n--- Top "<<n<<" Players ---\n";
    out<<"| Ranking | Name | Score | Grid Size (Difficulty Level) |\n";
    for(int i = 0; (i < a) && (i < n); i++)
    {
        out<<(i+1)<<". "<<P[i].name<<" | "<<P[i].score<<" | "<<diff[i]<<"\n";
    }
    out<<"------------------------------\n";
    out.close();
}
void displayTopNScores(string filename, string nameof, int n)
{
    ifstream in(filename, ios::binary);
    player scores[100];
    int diff[100];
    int a = 0;
    player temp;
    int tempDiff;
    while (in.read((char*)&temp, sizeof(player)))
    {
         in.read((char*)&tempDiff, sizeof(int));
        if(strcmp(temp.name ,nameof.c_str()) == 0)
        {
            scores[a] = temp;
            diff[a] = tempDiff;
            a++;
        }
    }
    in.close();
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = i + 1; j < a; j++)
        {
            if(scores[j].score> scores[i].score)
            {
                player c = scores[i];
                scores[i] = scores[j];
                scores[j] = c;
                int temp = diff[i];
                diff[i] = diff[j];
                diff[j] = temp;
            }
        }
    }
    ofstream out ("leaderboardDisplay.txt", ios::out);
    out<<"\n--- Top "<<n<<" Scores of "<< nameof<<" | Grid Size (Difficulty Level) ---\n";
    for(int i = 0; (i < a) && (i < n); i++)
    {
        out<<(i+1)<<". "<<scores[i].score<<" | "<<diff[i]<<'\n';
    }
    out<<"------------------------------\n";
    out.close();
}
void displayAllLeaderboard(string filename)
{
    player P[100];
    int diff[100];
    int a = 0;
    ifstream in(filename, ios::binary);
    while(in.read((char*)&P[a], sizeof(player)))
    {
        in.read((char*)&diff[a], sizeof(int));
        a++;
    } 
    in.close();
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = i + 1; j < a; j++)
        {
            if(P[j].score > P[i].score)
            {
                player temp = P[i];
                P[i] = P[j];
                P[j] = temp;
                int temp1 = diff[i];
                diff[i] = diff[j];
                diff[j] = temp1;
            }
        }
    }
    ofstream out("leaderboardDisplay.txt", ios::out);
    out<<"\n----------[ LeaderBoard ]----------\n";
    out<<"| Ranking | Name | Score | Grid Size (Difficulty Level) |\n";
    for(int i = 0; i < a; i++)
    {
        out<<(i+1)<<". "<<P[i].name<<" | "<<P[i].score<<" | "<<diff[i]<<"\n";
    }
    out<<"------------------------------\n";
    out.close();
}
void DeallocateGame(int **arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        delete[]arr[i];
    }
    delete[] arr;
}