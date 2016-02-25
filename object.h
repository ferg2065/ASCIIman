#pragma once
//allows me to use string
#include <string>
//allows me to use "NULL"
#include <cstdlib>
//gives me access to math functions such as absolute
#include <math.h>
#include "rectangle.h"
#include "curses.h"
#include "limits.h"
using namespace std;

//this is the base class for all in-game objects
class object : public rectangle
{
private:

	//saves the object it collides with
	object *hit_object;

	//render strings
	string str1;
	string str2;
	string str3;
	string str4;
	string str5;

	//intitialization function
	virtual void initialize(float _gravity)=0;

	//object's mass
	// used in collisions 
	float mass;

	//objects friction modifier
	//used in collisions
	float frict;

	//damage the object causes other objects when it hits them
	int damage;

	//amount of damage this object can take before dying
	int health;

	// object's animation string
	string anim;

	// right boundary of console
	int xmax;

	// bottom boundary of console
	int ymax;

	bool is_alive;
	bool dead;

public:
	object(void);
	object(int _xmax,int _ymax);
	~object(void);

	object* get_hit_object(void);
	void set_hit_object(object *hit_obj);

	virtual void	set_render(string s1,string s2,string s3,string s4,string s5);
	virtual string	get_str1(void);
	virtual string	get_str2(void);
	virtual string	get_str3(void);
	virtual string	get_str4(void);
	virtual string	get_str5(void);
	virtual float	get_frict(void);
	virtual void	set_frict(float new_frict);
	virtual int		get_damage(void);
	virtual void	set_damage(int new_damage);
	virtual int		get_health(void);
	virtual void	set_health(int new_health);
	virtual float	get_mass(void);
	virtual void	set_mass(float new_mass);


	virtual void	update(object *obj2);
	virtual bool	check(object *obj2);
	virtual void	collide(object *obj2, float adj, vector2d temp_mv, float x_over, float y_over);
	virtual void	friction(object *obj2);
	virtual void	can_die(bool _candie);
	virtual bool	can_die(void);
	virtual void	isdead(bool _isdead);
	virtual bool	isdead(void);
	virtual void	render(int x,int y, float p);
};

