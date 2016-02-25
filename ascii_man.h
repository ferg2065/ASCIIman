#pragma once
#include "object.h"

//object is a child of the object base class
//it has a number of special characteristics
class ascii_man : public object
{
private:
	//dir is updated when the ascii man changes horizontal direction 
	int dir;

	bool keys[4];	// array for storing left,right,up,space keys
	bool hit[4];	//array for holding collision values for up/down/left/right	

public:
	ascii_man();
	ascii_man(float _gravity);
	~ascii_man(void);

	//virtual members of base object class
	virtual void initialize(float _gravity);
	virtual void	move(void);
	virtual void	collide(object *obj2, float adj, vector2d temp_mv, float x_over, float y_over);
	virtual string	get_str2(void);
	virtual string	get_str3(void);
	virtual string	get_str4(void);

	//unique members of this class
	int get_dir(void);
	void set_dir(int _dir);
	bool get_keyL(void);
	bool get_keyR(void);
	bool get_keyJ(void);
	bool get_keyS(void);
	void set_keyL(bool b);
	void set_keyR(bool b);
	void set_keyJ(bool b);
	void set_keyS(bool b);

	bool get_hitL(void);
	bool get_hitR(void);
	bool get_hitU(void);
	bool get_hitD(void);
	void set_hitL(bool b);
	void set_hitR(bool b);
	void set_hitU(bool b);
	void set_hitD(bool b);
	void reset_hit_bools(void);

};

