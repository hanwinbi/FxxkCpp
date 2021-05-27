/*
how to compile this game?
$ gcc SnakeGame.cpp -o play -lncurses
how to run
$ ./play
*/

#include <stdlib.h>
#include <ncurses.h>

bool gameover;

const int height=20, width=20;
int x,y,fruitX,fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int TailX[100],TailY[100];
int nTail = 0;

void Setup(){

    initscr();
    clear();
    noecho();   //this will not echo what you typed
    curs_set(0);

    gameover = false;
    dir = STOP;
    x = height/2; //the pos of snake
    y = width/2;
    fruitX = (rand()%width) + 1; // the pos of food, random generate
    fruitY = (rand()%height) + 1;
    score = 0;
}

void Draw(){
    clear();    //clear window info
    // make the board

    for(int i= 0; i != width+2; ++i){
        mvprintw(0, i , "*");   //because we use -ncurses-, so we need this to print 
    }

    //draw the board
    for (int i = 0; i != height+2; ++i)
    {
        for (int j = 0; j < width+2; ++j)
        {
            if( i == 0 || i == width+1){
                mvprintw(i,j,"*");
            }else if(j == 0 || j == height+1 ){
                mvprintw(i,j,"*");
            }else if(i == y && j == x){ //print head of snake
                mvprintw(i,j,"O");
            }else if(i == fruitY && j == fruitX){
                mvprintw(i,j,"0");
            }else{
                for (int k = 0; k < nTail; k++)
                {
                    if(j == TailX[k] && i == TailY[k]){
                        mvprintw(i,j,"o");
                    }
                }
                
            }
        }
        
    }

    mvprintw(height/2, width +3, "Score: %d", score);
    
    refresh();
}

void Input(){
    //monitor keyboard key press
    keypad(stdscr, true);   //capture spaciel keystrokes, call this
    halfdelay(1);   //just press once, you do not need to hold on it
    int c = getch();

    switch (c)
    {
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 'q':
        gameover = true;
        break;
    }
}

void Logic(){

    //init the tail array
    int prevX = TailX[0];
    int prevY = TailY[0];

    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    

    switch (dir)
    {
    case LEFT:
        if(dir == RIGHT){
            break;
        }
        x--;
        break;
    case RIGHT:
        if(dir == LEFT){
            break;
        }
        x++;
        break;
    case UP:
        if(dir == DOWN){
            break;
        }
        y--;
        break;
    case DOWN:
        if(dir == UP){
            break;
        }
        y++;
        break;
    default:
        break;
    }

    //when the snake collide with wall
    if(x > width || x < 1 || y > height || y < 1){
        gameover = true;
    }

    //condition when snake eat the food
    if(x == fruitX && y == fruitY){
        score += 1;
        fruitX = (rand()%width) + 1; // the pos of food, random generate
        fruitY = (rand()%height) + 1;
        nTail++;
    }

    //if snake eat himself, his dead
    for (int i = 0; i < nTail; i++)
    {
        if(TailX[i] == x && TailY[i] == y){
            gameover = true;
        }
    }
    
}

int main(){

    Setup();
    Draw();

    while(!gameover){
        Draw();
        Input();
        Logic();
    }

    getch();
    endwin();   //clean all data resources allocated by ncurses

    return 0;
}