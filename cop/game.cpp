#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "man.h"
#include "game.h"

using namespace std;


void game::HideCursor()
{//���ع��
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    
}

void game::gotoxy(int x, int y)
{	//����һ������Ļ
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
		    case WALL:   cout<<"��"; break;	
	    	case COP :   cout<<"��"; break; 
			case ENEMY:  cout<<"��"; break;  
			case UP_BULLET:   cout<<"��"; break;  
			case LEFT_BULLET: cout<<"��"; break; 
			case RIGHT_BULLET:cout<<"��"; break;   
			case DOWN_BULLET: cout<<"��"; break; 
			}
        }
        cout<<endl;
    }
    cout<<"\n����һ������(��)����һС͵(��)������������\n��ٿ���Ľ�ɫ������С͵\n\n";
    cout<<"**  ����˵��: WASD�ֱ���� �������� �ĸ�������ƶ�  **\n";
    cout<<"**            IJKL�ֱ��� �������� �ĸ�������ӵ�  **\n\n";
    cout<<"##  ��ʾ:�벻Ҫ��ͼ��С͵������,��Ҫʱʹ�����ǹ  ##\n\n";    	
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

void game::updateWithInput()//�������йصĸ���
{
    char input;
    if (kbhit())
    {
        input = getch();

        //�����Ǿ����ƶ�   // ���ڶ���map����ʱ��[x][y],���� x Ϊ������, y Ϊ������ ! 
        if (input == 'a')                               // �����ƶ�
            if(map[cop_ptr->x][cop_ptr->y-1]==FREE)     // �������һ,�����겻��
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y--;}
        if (input == 's')                               //�����ƶ�
            if(map[cop_ptr->x+1][cop_ptr->y]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x++;}
        if (input == 'd')                               //�����ƶ�
            if(map[cop_ptr->x][cop_ptr->y+1]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y++;}
        if (input == 'w')                               //�����ƶ�
            if(map[cop_ptr->x-1][cop_ptr->y]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x--;}


        //�����Ƿ����ӵ�
        if (input == 'i')                               //�������
            if(map[cop_ptr->x-1][cop_ptr->y]!=WALL)
                {up_bullet_ptr->x = cop_ptr->x-1;up_bullet_ptr->y = cop_ptr->y;}
        if (input == 'j')                               //�������
            if(map[cop_ptr->x][cop_ptr->y-1]!=WALL)
                {left_bullet_ptr->x = cop_ptr->x;left_bullet_ptr->y = cop_ptr->y-1;}
        if (input == 'k')                               //�������
            if(map[cop_ptr->x+1][cop_ptr->y]!=WALL)
                {down_bullet_ptr->x = cop_ptr->x+1;down_bullet_ptr->y = cop_ptr->y;}
        if (input == 'l')                               //�������
            if(map[cop_ptr->x][cop_ptr->y+1]!=WALL)
                {right_bullet_ptr->x = cop_ptr->x;right_bullet_ptr->y = cop_ptr->y+1;}

}
}


void game::updateWithoutInput()  //�������޹صĸ���, ���ӵ����������С͵
{
    if (up_bullet_ptr->y < 18 && up_bullet_ptr->x > 0)           //�ӵ�up�Զ�����
        {
            if(map[up_bullet_ptr->x-1][up_bullet_ptr->y]!=WALL)
                {map[up_bullet_ptr->x][up_bullet_ptr->y]=0;up_bullet_ptr->x--;}
            else {map[up_bullet_ptr->x][up_bullet_ptr->y]=0;up_bullet_ptr->x=19;up_bullet_ptr->y=19;}
        }
    if (left_bullet_ptr->y < 18 && left_bullet_ptr->x > 0)       //�ӵ�left�Զ�����
        {
            if(map[left_bullet_ptr->x][left_bullet_ptr->y - 1]!=WALL)
                {map[left_bullet_ptr->x][left_bullet_ptr->y]=0;left_bullet_ptr->y--;}
            else {map[left_bullet_ptr->x][left_bullet_ptr->y]=0;left_bullet_ptr->x=0;left_bullet_ptr->y=0;}
        }
    if (right_bullet_ptr->y < 18 && right_bullet_ptr->x > 0)     //�ӵ�right�Զ�����
        {
            if(map[right_bullet_ptr->x][right_bullet_ptr->y + 1]!=WALL)
                {map[right_bullet_ptr->x][right_bullet_ptr->y]=0;right_bullet_ptr->y++;}
            else {map[right_bullet_ptr->x][right_bullet_ptr->y]=0;right_bullet_ptr->x=0;right_bullet_ptr->y=19;}
        }
    if (down_bullet_ptr->y < 18 && down_bullet_ptr->x > 0)       //�ӵ�down�Զ�����
        {
            if(map[down_bullet_ptr->x + 1][down_bullet_ptr->y]!=WALL)
                {map[down_bullet_ptr->x][down_bullet_ptr->y]=0;down_bullet_ptr->x++;}
            else {map[down_bullet_ptr->x][down_bullet_ptr->y]=0;down_bullet_ptr->x=0;down_bullet_ptr->y=1;}
        }
	
	// �˴������� bool������ԭ���Ǽ�������� if �ж����ĳ���
	bool condition1=(up_bullet_ptr->x == enemy_ptr->x) && (up_bullet_ptr->y == enemy_ptr->y);
	bool condition2=(left_bullet_ptr->x == enemy_ptr->x) && (left_bullet_ptr->y == enemy_ptr->y);
	bool condition3=(right_bullet_ptr->x == enemy_ptr->x) && (right_bullet_ptr->y == enemy_ptr->y);
	bool condition4=(down_bullet_ptr->x == enemy_ptr->x) && (down_bullet_ptr->y == enemy_ptr->y);
	
	
    if (condition1||condition2||condition3||condition4)
        //�����˱�����ʱ
        {
            flag2=1;// printf("��ɹ�������С͵��\n");
        }
        
    enemy_ptr->speed = 0;
    if (enemy_ptr->speed == 0)
    {               //
        time_t t=time(NULL);    //    ��ϵͳʱ����Ϊ��ǩ�����������
        srand(t);               //
        int p;
        flag=0;
        Sleep(100);
        while(flag==0)
        {
            p=rand()%4;
            switch(p)
            {
                case 0:if(map[enemy_ptr->x-1][enemy_ptr->y]==0||map[enemy_ptr->x-1][enemy_ptr->y]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->x--;flag=1;}break;//С͵���������������
                case 1:if(map[enemy_ptr->x][enemy_ptr->y-1]==0||map[enemy_ptr->x][enemy_ptr->y-1]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->y--;flag=1;}break;//�Ŀյ��ƶ�Ŷ
                case 2:if(map[enemy_ptr->x+1][enemy_ptr->y]==0||map[enemy_ptr->x+1][enemy_ptr->y]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->x++;flag=1;}break;//
                case 3:if(map[enemy_ptr->x][enemy_ptr->y+1]==0||map[enemy_ptr->x][enemy_ptr->y+1]==2){map[enemy_ptr->x][enemy_ptr->y]=0;enemy_ptr->y++;flag=1;}break;//
            }
        }
        enemy_ptr->speed= 1;
    }
    if(enemy_ptr->x == cop_ptr->x && enemy_ptr->y == cop_ptr->y){flag2=2;}
}
