#include "vector2d.h"


vector2d::vector2d(void)
{
	x=0;
	y=0;
}
vector2d::vector2d(float _x, float _y)
{
	set_x(_x);
	set_y(_y);
}
vector2d::vector2d(vector2d v1, vector2d v2)
{
	set_x(v1.get_x() - v2.get_x());
	set_y(v1.get_y() - v2.get_y());
}
vector2d::vector2d(float x1, float y1,float x2, float y2)
{
	set_x(x1 - x2);
	set_y(y1 - y2);
}
vector2d::~vector2d(void)
{
}

void vector2d::new_v(float _x, float _y)
{
	set_x(_x);
	set_y(_y);
}
float vector2d::get_x(void)
{
	return x;
}
void vector2d::set_x(float _x)
{
	x = _x;	
}
float vector2d::get_y(void)
{
	return y;
}
void vector2d::set_y(float _y)
{
	y = _y;
}
float vector2d::slope(void)
{
	if (get_x()!=0 && get_y()!=0)
	{
		return (get_y()/get_x());
	}
	else
	{
		return 0;
	}
}

vector2d& vector2d::operator=(vector2d& v)
{
	set_x(v.get_x());
	set_y(v.get_y());
	return *this;
}
bool vector2d::operator==(vector2d v)
{
	return ((get_x() == v.get_x()) && (get_y() == v.get_y()));
}
vector2d vector2d::operator+(vector2d v)
{
	vector2d t;
	t.set_x(get_x()+v.get_x());
	t.set_y(get_y()+v.get_y());
	return t;
}
vector2d vector2d::operator-(vector2d v)
{
	vector2d t;
	t.set_x(get_x()-v.get_x());
	t.set_y(get_y()-v.get_y());
	return t;
}
vector2d vector2d::operator*(float i)
{
	vector2d t;
	t.set_x(get_x() * i);
	t.set_y(get_y() * i);
	return t;
}
vector2d vector2d::normalize(void)
{
	if (magnetude()!=0)
	{
		set_x(get_x()/magnetude());
		set_y(get_y()/magnetude());
		return *this;
	}
	else
	{
		set_x(0);
		set_y(0);
		return *this;
	}
}
float vector2d::normal_dot(vector2d v)
{
	float xB = v.get_x() / v.magnetude();
	float yB = v.get_y() / v.magnetude();

	//dot product of normalized vector2d and vector2d v
	return ((get_x()*xB) + (get_y()*yB));
}
float vector2d::scalar_proj(float n,vector2d b)
{
	//dot product of normalized vector2d and vector2d v
	if ((magnetude() * b.magnetude())==0)
	{
		return 0;
	}
	else
	{
		return n / ((magnetude() * b.magnetude()));
	}
}
float vector2d::magnetude(void)
{
	//actual value is sqrt of
	return sqrt((get_x()*get_x()) + (get_y()*get_y()));
}
float vector2d::dot(vector2d v)
{
	return ((get_x()*v.get_x()) + (get_y()*v.get_y()));
}
