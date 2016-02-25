#pragma once
#include "vector2d.h"

//this is a base object class
//the main object class is a child of this class
//this allows me to separate out a number of related functions
//into a different class where they can be handled in a less
//cluttered manner
class rectangle
{
private:
	vector2d pt;
	vector2d xt;
	vector2d mv;
	vector2d *temp_mv;

	bool	gravity_applied;
	bool	moved;
	bool	fixed;
	bool	feel_gravity;
	bool	collision;	

	float	gravity_mod;

public:
	rectangle(void);
	rectangle(vector2d _pt, vector2d _xt, vector2d _mv);
	rectangle(float pt_x,float pt_y,float xt_x,float xt_y,float mv_x,float mv_y);
	~rectangle(void);

	virtual float		get_lft(void);
	virtual float		get_rgt(void);
	virtual float		get_top(void);
	virtual float		get_btm(void);

	virtual vector2d get_pt(void);
	virtual void set_pt(float _x,float _y);
	virtual void set_pt(vector2d _pt);
	virtual vector2d get_xt(void);
	virtual float get_xt_dist(void);
	virtual void set_xt(vector2d _xt);
	virtual void set_xt(float _x,float _y);
	virtual vector2d get_mv(void);
	virtual void set_mv(vector2d _mv);
	virtual void set_mv(float _x,float _y);
	virtual vector2d get_temp_mv(void);
	virtual vector2d* get_temp_mv_p(void);
	virtual void set_temp_mv(float _x,float _y);
	virtual void set_temp_mv(vector2d _mv);
	virtual void set_temp_mv(vector2d *_mv);

	// moved is used during collision detection
	// we step through objects moving them and checking for collisions
	// this boolean allows me to easily tag an object as having already been moved this frame
	virtual void	move(void);
	virtual bool	did_move(void);
	virtual void	did_move(bool _moved);
	virtual bool	is_fixed(void);
	virtual void	is_fixed(bool _moved);
	virtual bool	feels_gravity(void);
	virtual void	feels_gravity(bool _feelsgrav);

	// collision boolean is set when a collision is detected
	// it is used to speed up collision detection by allowing the object
	// that has already been collision to be skipped in subsequent checks
	// during the frame render
	virtual bool	did_collide(void);
	virtual void	did_collide(bool _collision);

	virtual float	get_gravity(void);
	virtual void	set_gravity(float _gravity);
	virtual bool	did_gravity(void);
	virtual void	did_gravity(bool _grav);
	virtual void	gravity(void);



};

