#include <iostream>
#include "man.h"
#include "game.h"
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;


int main() 
{
	loop:  // 结尾若重新开始游戏,则跳转至此处
	enemy e(2,7,0);  // 初始化小偷
	cop the_cop(16,9);  // 初始化警察
	bullet p1(19,19),p2(0,0),p3(0,19),p4(0,1);  // 初始化子弹
	
	game new_game(&the_cop,&e,&p1,&p2,&p3,&p4);	
	new_game.flag=0;
	new_game.flag2=0;	
		time_t t=time(NULL);    
		srand(t);               
		
		do{new_game.enemy_ptr->y=rand()%18;}
		while ((new_game.enemy_ptr->y==0)||(new_game.enemy_ptr->y==1)||(new_game.enemy_ptr->y==7)||(new_game.enemy_ptr->y==9)||(new_game.enemy_ptr->y==16)||(new_game.enemy_ptr->y==17)||(new_game.enemy_ptr->y==18));
		// 保证小偷出现位置随机

        while (new_game.flag2==0)
        {
            new_game.HideCursor(); // 隐藏光标
            new_game.mapSign();  // 进行地图标记
            new_game.gotoxy(0,0); // 防止频闪,使界面稳定
            cout<<new_game;    // 打印
            new_game.updateWithoutInput(); // 警察移动与发射子弹
            new_game.updateWithInput(); // 子弹飞行与判断胜负
        }

        switch(new_game.flag2)
        {
            case 1: cout<<"!!!!!  你成功击毙了小偷，好样的  !!!!!\n\n";break;
            case 2: cout<<"!!!!!  你被小偷干死了 !!!!!\n\n";break;
        }
        
		cout<<" 按 r 键以重新开始游戏, 空格键则退出,\n\n";    

	
	while(1)
	{
	    if (kbhit())
	    {
		    char input = getch();
	
		    if (input == 'r') 
		    {
		        system("cls"); // 清屏重开游戏
		        goto loop;
		    }
		    
		    if(input == ' ') // 空格则跳出循环,游戏结束
		    {break;}
		    
	    }
	}
        
	return 0;
}
