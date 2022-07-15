#ifndef __MAN_H__
#define __MAN_H__


class point
{
	public:
	int x,y;
	point(int xx,int yy)
	{
	x=xx;
	y=yy;
	}
	
};

class bullet :public point
{
	public:
		bullet(int px,int py):point(px,py){}
};

class cop : public point
{
	public:
		cop(int px,int py):point(px,py){}
};


class enemy : public point
{	public:
		int speed;
		enemy(int px,int py,int s):point(px,py),speed(s){}
};

#endif
