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
	loop:  // ��β�����¿�ʼ��Ϸ,����ת���˴�
	enemy e(2,7,0);  // ��ʼ��С͵
	cop the_cop(16,9);  // ��ʼ������
	bullet p1(19,19),p2(0,0),p3(0,19),p4(0,1);  // ��ʼ���ӵ�
	
	game new_game(&the_cop,&e,&p1,&p2,&p3,&p4);	
	new_game.flag=0;
	new_game.flag2=0;	
		time_t t=time(NULL);    
		srand(t);               
		
		do{new_game.enemy_ptr->y=rand()%18;}
		while ((new_game.enemy_ptr->y==0)||(new_game.enemy_ptr->y==1)||(new_game.enemy_ptr->y==7)||(new_game.enemy_ptr->y==9)||(new_game.enemy_ptr->y==16)||(new_game.enemy_ptr->y==17)||(new_game.enemy_ptr->y==18));
		// ��֤С͵����λ�����

        while (new_game.flag2==0)
        {
            new_game.HideCursor(); // ���ع��
            new_game.mapSign();  // ���е�ͼ���
            new_game.gotoxy(0,0); // ��ֹƵ��,ʹ�����ȶ�
            cout<<new_game;    // ��ӡ
            new_game.updateWithoutInput(); // �����ƶ��뷢���ӵ�
            new_game.updateWithInput(); // �ӵ��������ж�ʤ��
        }

        switch(new_game.flag2)
        {
            case 1: cout<<"!!!!!  ��ɹ�������С͵��������  !!!!!\n\n";break;
            case 2: cout<<"!!!!!  �㱻С͵������ !!!!!\n\n";break;
        }
        
		cout<<" �� r �������¿�ʼ��Ϸ, �ո�����˳�,\n\n";    

	
	while(1)
	{
	    if (kbhit())
	    {
		    char input = getch();
	
		    if (input == 'r') 
		    {
		        system("cls"); // �����ؿ���Ϸ
		        goto loop;
		    }
		    
		    if(input == ' ') // �ո�������ѭ��,��Ϸ����
		    {break;}
		    
	    }
	}
        
	return 0;
}
