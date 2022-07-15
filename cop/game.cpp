#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "man.h"
#include "game.h"

using namespace std;


void game::HideCursor()
{//隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    
}

void game::gotoxy(int x, int y)
{	//清理一部分屏幕
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


ostream& operator<< (ostream&cout,const game& g)
{
    int i, j;
    for (i=1; i<=17; i++)
    {
        for (j=1; j<=17; j++)
        {
 			switch(g.map[i][j])
 			{
			case FREE:   cout<<"  "; break;
		    case WALL:   cout<<"■"; break;	
	    	case COP :   cout<<"★"; break; 
			case ENEMY:  cout<<"♀"; break;  
			case UP_BULLET:   cout<<"↑"; break;  
			case LEFT_BULLET: cout<<"←"; break; 
			case RIGHT_BULLET:cout<<"→"; break;   
			case DOWN_BULLET: cout<<"↓"; break; 
			}
        }
        cout<<endl;
    }
    cout<<"\n你是一名警察(★)，现一小偷(♀)正在行凶作恶\n请操控你的角色，击败小偷\n\n";
    cout<<"**  操作说明: WASD分别操作 上左下右 四个方向的移动  **\n";
    cout<<"**            IJKL分别发射 上左下右 四个方向的子弹  **\n\n";
    cout<<"##  提示:请不要试图与小偷近身搏斗,必要时使用你的枪  ##\n\n";    	
    return cout;
}



void game::mapSign()
{
	map[cop_ptr->x][cop_ptr->y]= COP;
	map[enemy_ptr->x][enemy_ptr->y]= ENEMY;
	map[up_bullet_ptr->x][up_bullet_ptr->y]= UP_BULLET;
	map[left_bullet_ptr->x][left_bullet_ptr->y]= LEFT_BULLET;	
	map[right_bullet_ptr->x][right_bullet_ptr->y]= RIGHT_BULLET;	
	map[down_bullet_ptr->x][down_bullet_ptr->y]= DOWN_BULLET;	
}

void game::updateWithInput()//与输入有关的更新
{
    char input;
    if (kbhit())
    {
        input = getch();

        //下面是警察移动   // 由于定义map数组时是[x][y],所以 x 为纵坐标, y 为横坐标 ! 
        if (input == 'a')                               // 向左移动
            if(map[cop_ptr->x][cop_ptr->y-1]==FREE)     // 横坐标减一,纵坐标不变
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y--;}
        if (input == 's')                               //向下移动
            if(map[cop_ptr->x+1][cop_ptr->y]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x++;}
        if (input == 'd')                               //向右移动
            if(map[cop_ptr->x][cop_ptr->y+1]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y++;}
        if (input == 'w')                               //向上移动
            if(map[cop_ptr->x-1][cop_ptr->y]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x--;}


        //下面是发射子弹
        if (input == 'i')                               //向上射击
            if(map[cop_ptr->x-1][cop_ptr->y]!=WALL)
                {up_bullet_ptr->x = cop_ptr->x-1;up_bullet_ptr->y = cop_ptr->y;}
        if (input == 'j')                               //向左射击
            if(map[cop_ptr->x][cop_ptr->y-1]!=WALL)
                {left_bullet_ptr->x = cop_ptr->x;left_bullet_ptr->y = cop_ptr->y-1;}
        if (input == 'k')                               //向下射击
            if(map[cop_ptr->x+1][cop_ptr->y]!=WALL)
                {down_bullet_ptr->x = cop_ptr->x+1;down_bullet_ptr->y = cop_ptr->y;}
        if (input == 'l')                               //向右射击
            if(map[cop_ptr->x][cop_ptr->y+1]!=WALL)
                {right_bullet_ptr->x = cop_ptr->x;right_bullet_ptr->y = cop_ptr->y+1;}

}
}


void game::updateWithoutInput()  //与输入无关的更新, 即子弹飞行与击毙小偷
{
    if (up_bullet_ptr->y < 18 && up_bullet_ptr->x > 0)           //子弹up自动飞行
        {
            if(map[up_bullet_ptr->x-1][up_bullet_ptr->y]!=WALL)
                {map[up_bullet_ptr->x][up_bullet_ptr->y]=0;up_bullet_ptr->x--;}
            else {map[up_bullet_ptr->x][up_bullet_ptr->y]=0;up_bullet_ptr->x=19;up_bullet_ptr->y=19;}
        }
    if (left_bullet_ptr->y < 18 && left_bullet_ptr->x > 0)       //子弹left自动飞行
        {
            if(map[left_bullet_ptr->x][left_bullet_ptr->y - 1]!=WALL)
                {map[left_bullet_ptr->x][left_bullet_ptr->y]=0;left_bullet_ptr->y--;}
            else {map[left_bullet_ptr->x][left_bullet_ptr->y]=0;left_bullet_ptr->x=0;left_bullet_ptr->y=0;}
        }
    if (right_bullet_ptr->y < 18 && right_bullet_ptr->x > 0)     //子弹right自动飞行
        {
            if(map[right_bullet_ptr->x][right_bullet_ptr->y + 1]!=WALL)
                {map[right_bullet_ptr->x][right_bullet_ptr->y]=0;right_bullet_ptr->y++;}
            else {map[right_bullet_ptr->x][right_bullet_ptr->y]=0;right_bullet_ptr->x=0;right_bullet_ptr->y=19;}
        }
    if (down_bullet_ptr->y < 18 && down_bullet_ptr->x > 0)       //子弹down自动飞行
        {
            if(map[down_bullet_ptr->x + 1][down_bullet_ptr->y]!=WALL)
                {map[down_bullet_ptr->x][down_bullet_ptr->y]=0;down_bullet_ptr->x++;}
            else {map[down_bullet_ptr->x][down_bullet_ptr->y]=0;down_bullet_ptr->x=0;down_bullet_ptr->y=1;}
        }
	
	// 此处定义多个 bool变量的原因是减缩下面的 if 判断语句的长度
	bool condition1=(up_bullet_ptr->x == enemy_ptr->x) && (up_bullet_ptr->y == enemy_ptr->y);
	bool condition2=(left_bullet_ptr->x == enemy_ptr->x) && (left_bullet_ptr->y == enemy_ptr->y);
	bool condition3=(right_bullet_ptr->x == enemy_ptr->x) && (right_bullet_ptr->y == enemy_ptr->y);
	bool condition4=(down_bullet_ptr->x == enemy_ptr->x) && (down_bullet_ptr->y == enemy_ptr->y);
	
	
    if (condition1||condition2||condition3||condition4)
        //当敌人被击中时
        {
            flag2=1;// printf("你成功击毙了小偷！\n");
        }
        
    enemy_ptr->speed = 0;
    if (enemy_ptr->speed == 0)
    {               //
        time_t t=time(NULL);    //    以系统时间作为标签，生成随机数
        srand(t);               //
        int p;
        flag=0;
        Sleep(100);
        while(flag==0)
        {
            p=rand()%4;
            switch(p)
            {
                case 0:if(map[enemy_ptr->x-1][enemy_ptr->y]==0||map[enemy_ptr->x-1][enemy_ptr->y]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->x--;flag=1;}break;//小偷会随机向上下左右
                case 1:if(map[enemy_ptr->x][enemy_ptr->y-1]==0||map[enemy_ptr->x][enemy_ptr->y-1]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->y--;flag=1;}break;//的空地移动哦
                case 2:if(map[enemy_ptr->x+1][enemy_ptr->y]==0||map[enemy_ptr->x+1][enemy_ptr->y]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->x++;flag=1;}break;//
                case 3:if(map[enemy_ptr->x][enemy_ptr->y+1]==0||map[enemy_ptr->x][enemy_ptr->y+1]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->y++;flag=1;}break;//
            }
        }
        enemy_ptr->speed= 1;
    }
    if(enemy_ptr->x == cop_ptr->x && enemy_ptr->y == cop_ptr->y){flag2=2;}
}
