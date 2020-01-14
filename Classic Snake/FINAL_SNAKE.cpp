#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>;

using namespace std;
void help();
void game();
void check();
void dead();
void level();
void high();
int snake_x[500],snake_y[500],snake_size = 5,score,highscore,spd = 100,l;
bool checkdied = false,BONUS = false;
main()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);

    initwindow(screenWidth, screenHeight); /* initialize graphics and local variables */

    int cursor_y = ((screenHeight/2)-200);
    char ch;
    int page = 0;
    while(1)
    {
        setcolor(YELLOW);
        settextstyle(3,0,6);
        outtextxy((screenWidth/2)-230,(screenHeight/2)-330,"Classic Snake");
        setcolor(GREEN);
        settextstyle(3,0,3); /*this part prints menu again but inside while loop,because other functions will return here*/
        outtextxy((screenWidth/2)-200,(screenHeight/2)-200,"New Game");
        outtextxy((screenWidth/2)-200,(screenHeight/2)-170,"Help");
        outtextxy((screenWidth/2)-200,(screenHeight/2)-140,"Select Level");
        outtextxy((screenWidth/2)-200,(screenHeight/2)-110,"Highscore");
        outtextxy((screenWidth/2)-200,(screenHeight/2)-80,"Select Snake Skin");
        outtextxy((screenWidth/2)-200,(screenHeight/2)-50,"Exit");
        outtextxy((screenWidth/2)-250,cursor_y,">");
        setcolor(WHITE);
        settextstyle(3,0,3);
        outtextxy((screenWidth/2)-350,(screenHeight/2)+150,"<<< You can select a higher level to make it more challenging : ) >>>");

        if(kbhit){
        ch = getch();
        setcolor(BLACK);
        outtextxy((screenWidth/2)-250,cursor_y,">");
        if(ch == 13) {
            if(cursor_y==(screenHeight/2)-50) exit(0);
            else if(cursor_y==(screenHeight/2)-170) help();
            else if(cursor_y==(screenHeight/2)-200) game();
            else if(cursor_y==(screenHeight/2)-140) level();
            else if(cursor_y==(screenHeight/2)-110) high();
        }
        }
        setcolor(WHITE);
        if(ch==80) {cursor_y+=30;
        if(cursor_y > (screenHeight/2)-50) {cursor_y=((screenHeight/2)-200);}
        }
        if(ch==72) {cursor_y-=30;
        if(cursor_y < ((screenHeight/2)-200)) {cursor_y=(screenHeight/2)-50;}
        }
        outtextxy((screenWidth/2)-250,cursor_y,">");
    }

    return 0;
}
void help()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    setcolor(CYAN);
    outtextxy((screenWidth/2)-200,(screenHeight/2),"**Move the snake using the Arrow keys.");
    outtextxy((screenWidth/2)-180,(screenHeight/2)+30,"Press 'Alt' to Pause **");
    char ch = getch();
    clearviewport();
    return;
}
void game()
{

    clearviewport();
    freopen("GameData.dat","r",stdin);
    cin >> highscore;

    cleardevice();
    char ch;
    string key = "right";
    int maxx = getmaxx();
    int maxy = getmaxy()-50;
    int x = 13,y = 13;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    while(true)
        {
         clearviewport();
        if(score >0 && score%5==4) BONUS = true;
        else{ bonus = 500;
        BONUS = false;
        }
        if(!BONUS || bonus == 0){
        setcolor(BLACK);
        settextstyle(5, HORIZ_DIR, 5);
        outtextxy(250,10,"Hurry!! 888");
        setcolor(LIGHTCYAN);
        setfillstyle(SOLID_FILL,LIGHTCYAN);
        circle(food_x,food_y,5); //x position,y position,size
        floodfill(food_x,food_y,LIGHTCYAN);

        }
        else
        {
        setcolor(GREEN);
        setfillstyle(SOLID_FILL,GREEN);
        circle(food_x,food_y,15);
        floodfill(food_x,food_y,GREEN);

        char spp[1000];
        setcolor(BLACK);
        settextstyle(5, HORIZ_DIR, 5);
        sprintf(spp,"Hurry!! %d",bonus);
        outtextxy(250,10,"Hurry!! 888");
        setcolor(LIGHTBLUE);
        outtextxy(250,10,spp);
        // clears
        }
        maxx = getmaxx();
        maxy = getmaxy()-50;
        setcolor(LIGHTBLUE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch(); if(ch == 0) ch = getch();
            if(ch == 72 && key != "down" ) key = "up";
            if(ch == 80 && key != "up") key = "down";
            if(ch == 75 && key != "right") key = "left";
            if(ch == 77 && key != "left") key = "right";
            if(ch == 27) {
            cleardevice();
            return;
        }

        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else {
        for(int _size = snake_size-2;_size >= 0;_size--) {
        snake_x[_size+1] = snake_x[_size];
        snake_y[_size+1] = snake_y[_size];
        }
        snake_x[0] = x;
        snake_y[0] = y;

        setcolor(CYAN);
        circle(snake_x[0],snake_y[0],7);
        setfillstyle(SOLID_FILL,LIGHTBLUE);
        floodfill(snake_x[0],snake_y[0],CYAN);

        setcolor(GREEN);
        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(snake_x[_size],snake_y[_size],GREEN);
        }

        char ara[100];
        sprintf(ara,"Score: %d",score);
        setcolor(LIGHTCYAN);
        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(00,maxy+10,ara);
        sprintf(ara,"Bestscore: %d",highscore);
        setcolor(LIGHTCYAN);
        outtextxy(450,maxy+10,ara);

        delay(spd);

        }
        if(x == food_x && y== food_y)
        {
        snake_size++;score++;
            /* Snake eats food*/
        if(score%5==0 && score>0)score+=bonus;

        food_x = rand()%maxx,food_y = rand()%maxy;
        temp = food_x%13;
        food_x-=temp;
        temp = food_y%13;
        food_y-=temp;

        if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
        {
            while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5) {
            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;
            }
        }
        }
        if(key == "right") x = x+13; if(x > maxx) x =0;
        if(key == "left") x = x-13; if(x < 0) x = maxx-(maxx%13);
        if(key == "up") y = y-13; if(y > maxy) y = 0;
        if(key == "down") y = y+13; if(y < 0) y = maxy-(maxy%13);
        check();
        if(checkdied){
        dead();
        return;
        }

    if(BONUS){
    if(bonus>0)
    bonus-=10;
      }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[_size],snake_y[_size],BLACK);
        }
    }
}
void check()
{
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
    cout << score << endl;
    else cout << highscore << endl;

    for(int i = 1;i < snake_size;i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
        {
            delay(1000);
            setcolor(WHITE);
            for(int i = 0;i < snake_size;i++)
            {
                circle(snake_x[i],snake_y[i],5);
                setfillstyle(SOLID_FILL,RED);
                floodfill(snake_x[i],snake_y[i],WHITE);
            }
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            return;
            }
            }
            }
        }
    }
}
void dead()
{
    checkdied = false;
    snake_size = 5;
    score = 0;
//    clearviewport();
}
void level()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    char ch;
    char ara[100];
    while(true){

    int i = abs(spd/10.-10);
    sprintf(ara,"** SELECT LEVEL : %d **",i);
    setcolor(CYAN);
    outtextxy((screenWidth/2)-200,(screenHeight/2),ara);

    if(kbhit())
    {
        ch = getch();
        if(ch == 80) {
        spd-=10;
        if(spd < 0) spd = 100;
        }
        else if(ch == 72) {
            spd+=10;
        if(spd > 100) spd = 0;
        }
        else if(ch == 13)
            break;
    sprintf(ara,"** SELECT LEVEL : %d **",i);
    setcolor(BLACK);
    outtextxy((screenWidth/2)-200,(screenHeight/2),ara);
    }
    }

    clearviewport();
}
void high()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    freopen("GameData.dat","r",stdin);
    cin >> highscore;
    char ara[100];
    sprintf(ara,"** Highscore: %d **",highscore);
    setcolor(RED);
    outtextxy((screenWidth/2)-200,(screenHeight/2),ara);
    char ch = getch();
    clearviewport();
}
