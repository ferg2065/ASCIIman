#include "rectangle.h"


rectangle::rectangle(void)
{
}
rectangle::rectangle(vector2d _pt,vector2d _xt,vector2d _mv)
{
	set_pt(_pt);
	set_xt(_xt);
	set_mv(_mv);
}
rectangle::rectangle(float pt_x,float pt_y,float xt_x,float xt_y,float mv_x,float mv_y)
{
	set_pt(pt_x,pt_y);
	set_xt(xt_x,xt_y);
	set_mv(mv_x,mv_y);
}
rectangle::~rectangle(void)
{
}

float rectangle::get_lft(void)
{
	return get_pt().get_x() - get_xt().get_x();
}
float rectangle::get_rgt(void)
{
	return get_pt().get_x() + get_xt().get_x();
}
float rectangle::get_top(void)
{
	return get_pt().get_y() - get_xt().get_y();
}
float rectangle::get_btm(void)
{
	return get_pt().get_y() + get_xt().get_y();
}

vector2d rectangle::get_pt(void)
{
	return pt;
}
void rectangle::set_pt(float _x,float _y)
{
	if (is_fixed()==false)
	{
		pt.set_x(_x);
		pt.set_y(_y);
	}
}
void rectangle::set_pt(vector2d _pt)
{
	if (is_fixed()==false)
	{
		pt = _pt;
	}
}
vector2d rectangle::get_xt(void)
{
	return xt;
}
float rectangle::get_xt_dist(void)
{
	return xt.magnetude();
}
void rectangle::set_xt(vector2d _xt)
{
	xt = _xt;
}
void rectangle::set_xt(float _x,float _y)
{
	xt.set_x(_x);
	xt.set_y(_y);
}
vector2d rectangle::get_mv(void)
{
	return mv;
}
void rectangle::set_mv(vector2d _mv)
{
	if (is_fixed()==false)
	{
		mv = _mv;
	}
}
void rectangle::set_mv(float _x,float _y)
{
	if (is_fixed()==false)
	{
		mv.set_x(_x);
		mv.set_y(_y);
	}
}
vector2d rectangle::get_temp_mv(void)
{
	vector2d t;
	t = *temp_mv;
	return t;
}
vector2d* rectangle::get_temp_mv_p(void)
{
	return temp_mv;
}
void rectangle::set_temp_mv(vector2d *_mv)
{
	temp_mv = new vector2d();
	temp_mv =_mv;
}
void rectangle::set_temp_mv(float _x,float _y)
{
	temp_mv = new vector2d();
	temp_mv->set_x(_x);
	temp_mv->set_y(_y);
}
void rectangle::set_temp_mv(vector2d _mv)
{
	temp_mv = new vector2d();
	*temp_mv = _mv;
}

bool rectangle::did_move(void)
{
	return moved;
}
void rectangle::did_move(bool _moved)
{
	moved = _moved;
}
bool rectangle::is_fixed(void)
{
	return fixed;
}
void rectangle::is_fixed(bool _moves)
{
	fixed = _moves;
}
void rectangle::move(void)
{
	if (did_move()==false && did_collide()==false && is_fixed()==false)
	{
		if (get_temp_mv_p()==NULL)
		{set_pt(get_pt()+get_mv());}
		else
		{
			set_pt(get_pt()+get_temp_mv());
			set_temp_mv(NULL);
		}
		did_move(true);
	}
}

bool rectangle::did_collide(void)
{
	return collision;
}
void rectangle::did_collide(bool _collision)
{
	collision = _collision;
}

float rectangle::get_gravity(void)
{
	return gravity_mod;
}
void rectangle::set_gravity(float _gravity)
{
	gravity_mod = _gravity;
}
bool rectangle::did_gravity(void)
{
	return gravity_applied;
}
void rectangle::did_gravity(bool _grav)
{
	gravity_applied = _grav;
}
void rectangle::gravity(void)
{
	if (did_collide()==false && is_fixed()==false && did_gravity()==false && feels_gravity()==true)
	{
		set_mv(get_mv().get_x(), get_mv().get_y() + get_gravity());
		did_gravity(true);
	}
}
bool rectangle::feels_gravity(void)
{
	return feel_gravity;
}
void rectangle::feels_gravity(bool _feelsgrav)
{
	feel_gravity = _feelsgrav;
}
