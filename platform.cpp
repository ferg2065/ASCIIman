#include "platform.h"


platform::platform(float _gravity)
{
	did_move(false);
	can_die(false);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);

	set_mv(0,0);
	set_pt(0,0);
	set_xt(0,0);

	initialize(_gravity);
}
platform::platform(vector2d _pt, vector2d _xt, float _gravity)
{
	did_move(false);
	can_die(false);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);

	set_mv(0,0);
	set_pt(_pt);
	set_xt(_xt);
	initialize(_gravity);
}
platform::platform(float pt_x, float pt_y, float xt_x,float xt_y,float _gravity)
{
	did_move(false);
	can_die(false);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);

	set_mv(0,0);
	set_pt(pt_x,pt_y);
	set_xt(xt_x,xt_y);
	initialize(_gravity);
}
platform::~platform(void)
{
}
void platform::initialize(float _gravity)
{
	set_temp_mv(NULL);
	is_fixed(true);
	set_gravity(_gravity);
	set_mass(1);
	set_frict((float)(0.15));
	string str="";
	str.append((int)(2*get_xt().get_x()),'-');
	set_render("","",str,"","");
	set_damage(0);
	set_health(1);
}

