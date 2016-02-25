#include "ascii_man.h"


ascii_man::ascii_man()
{
	did_move(false);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);
	isdead(false);
	can_die(true);

	initialize(0);
}
ascii_man::ascii_man(float _gravity)
{
	did_move(false);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);
	isdead(false);
	can_die(true);

	initialize(_gravity);
}


ascii_man::~ascii_man(void)
{ 
}

//initialize is called by each constructor 
void ascii_man::initialize(float _gravity)
{
	set_temp_mv(NULL);
	set_gravity(_gravity);
	set_render(""," 0 "," 8="," /\\","");
	set_pt(20,2);
	set_xt(1.2,1.5);
	set_mv(0,0);
	set_mass(3);
	set_frict((float)0.55);
	dir = 1;
	set_damage(10);
	set_health(50);
}

	int ascii_man::get_dir(void)
	{
		return dir;
	}
	void ascii_man::set_dir(int _dir)
	{
		dir = _dir;
	}

bool ascii_man::get_keyL(void)
{return keys[0];}
bool ascii_man::get_keyR(void)
{return keys[1];}
bool ascii_man::get_keyJ(void)
{return keys[2];}
bool ascii_man::get_keyS(void)
{return keys[3];}
void ascii_man::set_keyL(bool b)
{keys[0] = b;}
void ascii_man::set_keyR(bool b)
{keys[1] = b;}
void ascii_man::set_keyJ(bool b)
{keys[2] = b;}
void ascii_man::set_keyS(bool b)
{keys[3] = b;}

bool ascii_man::get_hitL(void)
{return hit[0];}
bool ascii_man::get_hitR(void)
{return hit[1];}
bool ascii_man::get_hitU(void)
{return hit[2];}
bool ascii_man::get_hitD(void)
{return hit[3];}
void ascii_man::set_hitL(bool b)
{hit[0] = b;}
void ascii_man::set_hitR(bool b)
{hit[1] = b;}
void ascii_man::set_hitU(bool b)
{hit[2] = b;}
void ascii_man::set_hitD(bool b)
{hit[3] = b;}
void ascii_man::reset_hit_bools(void)
{
	set_hitL(false);
	set_hitR(false);
	set_hitU(false);
	set_hitD(false);
}

//this is my custom movement fucntion unique to the ascii man class
void ascii_man::move(void)
{
	//dont move if i already moved it somewhere else
  	if (did_move()==false && did_collide()==false)
	{
		//temp move i think is now not used
		if (get_temp_mv_p()==NULL)
		{set_pt(get_pt()+get_mv());}
		else
		{
			set_pt(get_pt()+get_temp_mv());
			set_temp_mv(NULL);
		}
		did_move(true);
	}

	//this is where i set the direction the dude is moving
	if (get_mv().get_x() != 0)
	{set_dir((int)(get_mv().get_x()/abs(get_mv().get_x())));}
}
void ascii_man::collide(object *obj2, float adj, vector2d temp_mv, float x_over, float y_over)
{
	set_hit_object(obj2);

	if(x_over > y_over) 
	{
		if(this->get_pt().get_x() < obj2->get_pt().get_x())
		{set_hitR(true);}
		else
		{set_hitL(true);}
	}
	if(x_over < y_over)
	{
		if(this->get_pt().get_y() < obj2->get_pt().get_y())
		{set_hitD(true);}
		else
		{set_hitU(true);}
	}
	if (adj < 0.0001)
	{adj=1;}
	set_pt(get_pt() + (get_mv()* adj));
	set_mv(temp_mv * obj2->get_mass());

	if(this->get_mv().get_y() > 0 && get_hitD()==true && obj2->is_fixed()==true)
	{set_mv(get_mv().get_x(),0);}


	if (can_die()==true)
	{
		set_health(get_health()-obj2->get_damage());
	}
	if (get_health() <= 0)
	{
		isdead(true);
	}
	did_collide(true);
	did_move(true);
}

string ascii_man::get_str2(void)
{
	return " 0 ";
}
string ascii_man::get_str3(void)
{
	if (get_dir()==1)
	{
		return " 8=";
	}
	else
	{
		return "=8 ";
	}
}
string ascii_man::get_str4(void)
{
	if (get_dir()==1)
	{
		return " /\\";
	}
	else
	{
		return "/\\ ";
	}
}
