#include <stdlib.h>
#include <ncurses.h>


bool g_gameover;

int height=4,width=4;
int x, y, n_x, n_y;     //初始化最初两个数字的位置

char Board[4][4]={'1'};
enum eDirection{LEFT,RIGHT,UP,DOWN};    //the direction to move
eDirection g_dir;

int score = 0;  //init score, todo

void Init(){

    initscr();
    clear();
    noecho();
    curs_set(0);    // set the appearance of cursor, 0-invisible

    x = (rand()%4);
    y = (rand()%4);
    int temp_x = (rand()%4);
    int temp_y = (rand()%4);
    while(x == temp_x && y == temp_y){
        int temp_x = (rand()%4);
        int temp_y = (rand()%4);
        n_x = temp_x;
        n_y = temp_y;
    }

    Board[x][y] = '2';
    Board[n_x][n_y] = '2';
}

void Update(){
    clear();    //clear window

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(Board[i][j]){
                mvprintw(i, j, "%s", &Board[i][j]);
            }
        }
    }

    refresh();
}

void Operate(){
    keypad(stdscr, true);
    halfdelay(1);
    int c = getch();

    switch (c)
    {
    case KEY_LEFT:
        g_dir = LEFT;
        break;
    case KEY_RIGHT:
        g_dir = RIGHT;
        break;
    case KEY_UP:
        g_dir = UP;
        break;
    case KEY_DOWN:
        g_dir = DOWN;
        break;
    case 'q':
        g_gameover = true;
        break;
    }
}

void Logic(){
    switch (g_dir)
    {
        case LEFT:
            for (int i = 0; i < height; i++)
            {
                for (int j = 0,k = 0; j < width; j++)
                {
                    if(Board[i][j] != ' '){
                        Board[i][++k] = Board[i][j];
                        Board[i][j] = ' ';
                    }
                }
            }
            break;
        case RIGHT:
            for (int i = 0; i < height; i++)
            {
                for (int j = width,k = width; j > 0; j--)
                {
                    if(Board[i][j] != ' '){
                        Board[i][--k] = Board[i][j];
                        Board[i][j] = ' ';
                    }
                }
            }
            break;
        case UP:
            for (int i = 0; i < height; i++)
            {
                for (int j = 0,k = 0; j < width; j++)
                {
                    if(Board[i][j] != ' '){
                        Board[--k][j] = Board[i][j];
                        Board[i][j] = ' ';
                    }
                }
            }
            break;
        case DOWN:
            for (int j = 0; j < width; j++)
            {
                for (int i = height,k = height; i > 0; i++)
                {
                    if(Board[i][j] != ' '){
                        Board[++k][j] = Board[i][j];
                        Board[i][j] = ' ';
                    }
                }
            }
            break;
        default:
            break;
    }
}

int main(){
    Init();
    
    while(!g_gameover){
        Update();
        Operate();
        Logic();
    }

    getch();
    endwin();
    return 0;
}