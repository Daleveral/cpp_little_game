#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include "man.h"
using namespace std;

enum MAP_POINT
{
	FREE =0,WALL =1,COP =2, ENEMY =3, UP_BULLET =4, LEFT_BULLET =5,
	RIGHT_BULLET =6, DOWN_BULLET= 7
};


class game
{
	public:
		cop* cop_ptr;
		enemy* enemy_ptr;
		bullet* up_bullet_ptr;
		bullet* left_bullet_ptr;
		bullet* right_bullet_ptr;
		bullet* down_bullet_ptr;
		
		int flag;
		int flag2;
		int map[19][19]={
		     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		     {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		     {1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,1},
		     {0,1,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0},
		     {0,1,0,1,0,1,0,1,0,0,1,1,0,1,1,0,0,1,0},
		     {0,1,0,1,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0},
		     {0,1,0,0,1,0,0,1,0,0,1,1,0,1,1,0,0,1,0},
		     {0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0},
		     {0,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,1,1,0},
		     {0,1,0,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0},
		     {0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,0},
		     {0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0},
		     {0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0},
		     {0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0},
		     {0,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0},
		     {0,1,0,1,0,0,0,0,1,0,1,0,1,1,1,0,0,1,0},
		     {1,1,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1,1},
		     {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		};
		
		game(cop* c,enemy* e,bullet* b1,bullet* b2,bullet* b3,bullet* b4)
		{
			cop_ptr = c;
			enemy_ptr = e;
			up_bullet_ptr = b1;
			left_bullet_ptr =  b3;
			right_bullet_ptr =  b4;
			down_bullet_ptr = b2;
		}
		
		void HideCursor();
		void gotoxy(int , int );
		void mapSign();
		void updateWithInput();
		void updateWithoutInput();
		friend ostream& operator<< (ostream&,const game&);
};

#endif
