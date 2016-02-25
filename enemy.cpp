#include "enemy.h"


enemy::enemy(float _gravity)
{
	did_move(false);
	can_die(true);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);

	set_pt(1,1);
	set_mv(1,0);
	set_xt(1.5,2.5);

	initialize(_gravity);
}
enemy::enemy(vector2d _pt, float _gravity)
{
	did_move(false);
	can_die(true);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);

	set_pt(_pt);
	set_mv(1,0);
	set_xt(1.5,2.5);

	initialize(_gravity);
}
enemy::enemy(float pt_x, float pt_y, float _gravity)
{
	did_move(false);
	can_die(true);
	did_collide(false);
	feels_gravity(true);
	did_gravity(false);
	is_fixed(false);

	set_pt(pt_x,pt_y);
	set_mv(1,0);
	set_xt(1.5,2.5);

	initialize(_gravity);
}
enemy::~enemy(void)
{
}

void enemy::initialize(float _gravity)
{
	set_temp_mv(NULL);
	set_gravity(_gravity);
	set_render("^0^","<8>","=O=","|||","UUU");
	set_mass(5);
	set_frict((float)0.65);
	set_damage(10);
	set_health(15);
}

//void enemy::collide(object *obj2, float adj, vector2d temp_mv, float x_over, float y_over)
//{
//}
void enemy::move(void)
{
	if (did_collide()==true)
	{
		if (this->get_mv().get_x() > 0 && get_hit_object()->get_rgt() > this->get_rgt())
		{
			this->set_pt((this->get_pt().get_x() + this->get_mv().get_x()),this->get_pt().get_y());
		}
		else if (this->get_mv().get_x() > 0)
		{
			this->set_mv((this->get_mv().get_x() * -1),this->get_mv().get_y());
		}
		if (this->get_mv().get_x() < 0 && get_hit_object()->get_lft() < this->get_lft())
		{
			this->set_pt((this->get_pt().get_x() + this->get_mv().get_x()),this->get_pt().get_y());
		}
		else if (this->get_mv().get_x() < 0)
		{
			this->set_mv((this->get_mv().get_x() * -1),this->get_mv().get_y());
		}
	}
	object::move();
}

void enemy::adj_spawn(vector<object*> *objects)
{
	int i;
	for (i=0;i<objects->size();i++)
	{
		//find a fixed object that is to the left of the corrent object and within 50 units of it
		if (objects->at(i)->is_fixed()==true && objects->at(i)->get_lft() < this->get_lft() && (this->get_lft()-objects->at(i)->get_lft()) < 50)
		{
			this->set_pt(objects->at(i)->get_pt().get_x(),(objects->at(i)->get_pt().get_y() - objects->at(i)->get_xt().get_y() - this->get_xt().get_y() - 1));
			i=objects->size();
		}
	}
}
