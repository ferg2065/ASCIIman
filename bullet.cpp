#include "bullet.h"


bullet::bullet(float _gravity)
{
	did_move(false);
	can_die(true);
	did_collide(false);
	feels_gravity(false);
	did_gravity(false);
	is_fixed(false);

	set_pt(1,1);
	set_mv(5,0);
	set_type(1);
}
bullet::bullet(vector2d _p, int type,int dir,float _gravity)
{
	did_move(false);
	can_die(true);
	did_collide(false);
	feels_gravity(false);
	did_gravity(false);
	is_fixed(false);

	set_type(type);
	set_pt(_p);
	set_mv(6*dir,0);
	set_type(type);
}
bullet::bullet(float pt_x, float pt_y, int dir, int type, float _gravity)
{
	did_move(false);
	can_die(true);
	did_collide(false);
	feels_gravity(false);
	did_gravity(false);
	is_fixed(false);

	set_type(type);
	set_mv((6 * dir),0);
	set_pt(pt_x,pt_y);
	set_xt(0.5,0.5);
	initialize(_gravity);
}

void bullet::initialize(float _gravity)
{
	set_temp_mv(NULL);
	set_gravity(_gravity);
	if (get_type()==1)
	{set_render("","","-","","");}
	if (get_type()==2)
	{set_render("","","*","","");}
	set_mass(.1);
	set_frict(0.05);
	set_damage(10);
	set_health(1);
}

int bullet::get_type(void)
{
	return type;
}
void bullet::set_type(int _type)
{
	type = _type;
}

bullet::~bullet(void)
{
}
