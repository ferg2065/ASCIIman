#include "object.h"


object::object(void)
{
	xmax = 0;
	ymax = 0;
}
object::object(int _xmax,int _ymax)
{
	xmax = _xmax;
	ymax = _ymax;
}

object::~object(void)
{
}

object* object::get_hit_object(void)
{
	return hit_object;
}
void object::set_hit_object(object *hit_obj)
{
	hit_object = hit_obj;
}


void object::set_render(string s1,string s2,string s3,string s4,string s5)
{
	str1=s1;
	str2=s2;
	str3=s3;
	str4=s4;
	str5=s5;
}
string object::get_str1(void)
{
	return str1;
}
string object::get_str2(void)
{
	return str2;
}
string object::get_str3(void)
{
	return str3;
}
string object::get_str4(void)
{
	return str4;
}
string object::get_str5(void)
{
	return str5;
}
float object::get_frict(void)
{
	return frict;
}
void object::set_frict(float new_frict)
{
	frict = new_frict;
}
int object::get_health(void)
{
	return health;
}
void object::set_health(int new_health)
{
	health = new_health;
}
int object::get_damage(void)
{
	return damage;
}
void object::set_damage(int new_damage)
{
	damage = new_damage;
}
float object::get_mass(void)
{
	return mass;
}
void object::set_mass(float new_mass)
{
	mass = new_mass;
}
void object::update(object *obj2)
{
	////check(obj2);
	move();
	//gravity();	
}

bool object::check (object *obj2)
{
	bool x_hit = false;
	bool y_hit = false;
	object *A;
	object *B = obj2;
	A=dynamic_cast<object*>(this);
	//just stop the check here if comparing two non-moving objects
	if (
		A->get_mv().get_x()==0 && 
		A->get_mv().get_y()==0 && 
		B->get_mv().get_x()==0 && 
		B->get_mv().get_x()==0
		)
	{return false;}

	float dist_x;
	float dist_y;
	float move_x;
	float move_y;
	if ((B->get_pt().get_x()-B->get_xt().get_x()) >= (A->get_pt().get_x()+A->get_xt().get_x()))
	{
		dist_x = ((B->get_pt().get_x()-B->get_xt().get_x()) - (A->get_pt().get_x()+A->get_xt().get_x()));
		move_x = (A->get_mv().get_x() - B->get_mv().get_x());
	}
	else if ((B->get_pt().get_x()+B->get_xt().get_x()) <= (A->get_pt().get_x()-A->get_xt().get_x()))
	{
		dist_x = ((A->get_pt().get_x()-A->get_xt().get_x()) - (B->get_pt().get_x()+B->get_xt().get_x()));
		move_x = (B->get_mv().get_x() - A->get_mv().get_x());
	}
	else 
	{
		dist_x = 0;
		move_x = abs(B->get_mv().get_x() - A->get_mv().get_x());
	}
	if ((B->get_pt().get_y()-B->get_xt().get_y()) >= (A->get_pt().get_y()+A->get_xt().get_y()))
	{
		dist_y = ((B->get_pt().get_y()-B->get_xt().get_y()) - (A->get_pt().get_y()+A->get_xt().get_y()));
		move_y = (A->get_mv().get_y() - B->get_mv().get_y());
	}
	else if ((B->get_pt().get_y()+B->get_xt().get_y()) <= (A->get_pt().get_y()-A->get_xt().get_y()))
	{
		dist_y = ((A->get_pt().get_y()-A->get_xt().get_y())-(B->get_pt().get_y()+B->get_xt().get_y()));
		move_y = (B->get_mv().get_y() - A->get_mv().get_y());
	}
	else
	{
		dist_y = 0;
		move_y = abs(B->get_mv().get_y() - A->get_mv().get_y());
	}

	//find the overlap amount of the objects if they were to move
	float test_x = dist_x - move_x;
	float test_y = dist_y - move_y;

	//if there is no everlap in either dimension then the objects didnt collide
	if (dist_x == 0 && dist_y == 0)
	{
		test_x=test_x;
	}
	if (test_x > 0 && test_y == 0)
	{
		return false;
	}
	if (dist_x < 0 && dist_y == 0)
	{
		x_hit = true;
	}
	if (test_x == 0 && test_y > 0)
	{
		return false;
	}
	if (test_x == 0 && test_y < 0)
	{
		y_hit = true;
	}
	 if (test_x > 0 || test_y > 0)
	{
		return false;
	}
	else
	{
		//vector AC represents the total movement of both objects
		vector2d AC = (obj2->get_mv() - this->get_mv());

		//these are ratios of excess movement to total movement
		float vx = abs((abs(dist_x))/(abs(move_x)));

		float vy = abs((abs(dist_y))/(abs(move_y)));
		if (move_x==0 || (vx==0 && move_x!=0))
		{vx=0;}
		if (move_y==0 || (vy==0 && move_y!=0))
		{vy=0;}

		float adj = 0;

		//the point of collision is the point at which both x and y
		//ratios allow for collision, so basically get the larger of
		//the two
		//the smaller one is where the first dimension has a collision
		//the larger one is the point where both dimensions finally have
		//a collision
		if (vx < 1 && vx > adj)
		{adj = vx;}
		if (vy < 1 && vy > adj)
		{adj = vy;}
		//if (adj == 0)
		//{adj = 1;}
		if (adj < 0.001)
		{adj = 0;}
		if (move_x ==0 && move_y==0)
		{adj=0;}

		//vector dist_v is the vector i calculate 
		//new movement vector with
		vector2d dist_v(0,0);

		// calculate the new movement vector for B
		vector2d new_this_mv = this->get_mv();
		if (test_x==0)
		{
			dist_v.new_v(0,1);
		}
		else if (AC.get_y()==0)
		{
			//if the only movement of either object is along the x axis
			//and we have determined that the objects collide
			//then we want to reverse the x direction 
			dist_v.new_v(1,0);
		}
		else
		{
			//if the slope is positive then the object is moving either \  
			//down right or up left                                      \ 
			if (AC.slope() > 0)
			{
				if (AC.slope() > (this->get_xt().slope()))
				{
					dist_v.new_v(0,1);
				}
				else
				{
					dist_v.new_v(1,0);
				}
			}
			else
			{			
				if (AC.slope() > -(this->get_xt().slope()))
				{
					dist_v.new_v(1,0);
				}
				else
				{
					dist_v.new_v(0,1);
				}
			}
		}
		float a1 = this->get_mv().dot(dist_v);
		float a2 = obj2->get_mv().dot(dist_v);

		// find the difference in movement of the objects 
		// this will be used as a scalar multiple
		float scalar_dif = (2 * (a1 - a2)) / (this->get_mass() + obj2->get_mass());
		if (scalar_dif < .00001)
		{scalar_dif=0;}
		vector2d new_A_mv;
		vector2d new_B_mv;

		if (scalar_dif < 0)
		{
			new_A_mv = A->get_mv() + (dist_v * adj * B->get_mass());
			new_B_mv = B->get_mv() - (dist_v * adj * A->get_mass());
		}
		else
		{
			new_A_mv = A->get_mv() - (dist_v * scalar_dif * B->get_mass());
			new_B_mv = B->get_mv() + (dist_v * scalar_dif * A->get_mass());
		}
		vector2d adj_vect_this = (dist_v * scalar_dif * obj2->get_mass());
		vector2d adj_vect_obj2 = (dist_v * scalar_dif * this->get_mass());

		//pass stuff to collide function
		//by passing it rather than doing stuff here
		//i can treat objects like asciiman differently than all other objects
		//i do this with my virtual functions
		A->collide(B, adj, new_A_mv, vx, vy);
		B->collide(A, adj, new_B_mv, vx, vy);

		return true;
	}
}
void object::collide(object *obj2, float adj, vector2d temp_mv, float x_over, float y_over)
{
	set_hit_object(obj2);

	//update movement for object based on math from check() function
	//set_temp_mv(this->get_mv() * adj);
	set_pt(get_pt() + (get_mv()* adj));
	set_mv(temp_mv * obj2->get_mass());

	if (can_die()==true)
	{
		set_health(get_health()-obj2->get_damage());
	}
	if (get_health() <= 0)
	{
		isdead(true);
	}
	did_collide(true);
}
void object::friction(object *obj2)
{
}
void object::render(int x,int y, float p)
{
	float pos;
	int width = (int)(2*get_xt().get_x());
	did_move(false);
	did_collide(false);
	did_gravity(false);
	if (get_lft() < p)
	{
		//this math keeps the object from re-appearing on other side of screen
		//due to word wrap
		pos = (p-get_lft()); // negative number equaling the number of characters past 
		//the edge of the screen
		if (get_str1().size()!=0)
		{mvaddstr((int)(get_pt().get_y()-2), 0, get_str1().substr((int)pos,(int)(width-pos)).c_str());}
		if (get_str2().size()!=0)
		{mvaddstr((int)(get_pt().get_y()-1), 0, get_str2().substr((int)pos,(int)(width-pos)).c_str());}
		if (get_str3().size()!=0)
		{mvaddstr((int)(get_pt().get_y()), 0, get_str3().substr((int)pos,(int)(width-pos)).c_str());}
		if (get_str4().size()!=0)
		{mvaddstr((int)(get_pt().get_y()+1), 0, get_str4().substr((int)pos,(int)(width-pos)).c_str());}
		if (get_str5().size()!=0)
		{mvaddstr((int)(get_pt().get_y()+2), 0, get_str5().substr((int)pos,(int)(width-pos)).c_str());}
	}
	else if (get_pt().get_x() >= (x-get_xt().get_x()-p))
	{
		//this math keeps the object from re-appearing on other side of screen
		//due to word wrap
		//pos = (int)(x -1 - get_rgt()-p);// negative number equaling the number of characters past 
		float past_edge = get_rgt()-(x+p);
		//the edge of the screen
		mvaddstr((int)(get_pt().get_y()-2), (int)(get_lft()-p), get_str1().substr(0,(int)(width-past_edge)).c_str());
		mvaddstr((int)(get_pt().get_y()-1), (int)(get_lft()-p), get_str2().substr(0,(int)(width-past_edge)).c_str());
		mvaddstr((int)(get_pt().get_y()), (int)(get_lft()-p), get_str3().substr(0,(int)(width-past_edge)).c_str());
		mvaddstr((int)(get_pt().get_y()+1), (int)(get_lft()-p), get_str4().substr(0,(int)(width-past_edge)).c_str());
		mvaddstr((int)(get_pt().get_y()+2), (int)(get_lft()-p), get_str5().substr(0,(int)(width-past_edge)).c_str());
	}
	else
	{
		mvaddstr((int)(get_pt().get_y()-2), (int)(get_lft()-p), get_str1().c_str());
		mvaddstr((int)(get_pt().get_y()-1), (int)(get_lft()-p), get_str2().c_str());
		mvaddstr((int)(get_pt().get_y()), (int)(get_lft()-p), get_str3().c_str());
		mvaddstr((int)(get_pt().get_y()+1), (int)(get_lft()-p), get_str4().c_str());
		mvaddstr((int)(get_pt().get_y()+2), (int)(get_lft()-p), get_str5().c_str());
	}
}
void object::isdead(bool _isdead)
{
	dead = _isdead;
}
bool object::isdead(void)
{
	return dead;
}
void object::can_die(bool _candie)
{
	is_alive = _candie;
}
bool object::can_die(void)
{
	return is_alive;
}
