#pragma once
#include "object.h"
#include <vector>

class enemy : public object
{
public:
	enemy(float _gravity);
	enemy(vector2d _pt, float _gravity);
	enemy(float pt_x, float pt_y, float _gravity);
	~enemy(void);
	//virtual string	get_render(void);

	//enemies need to know if they are about to fall off a platform or if ascii man is near
//	virtual bool check(object *obj2);
	virtual void initialize(float _gravity);
//	virtual void collide(object *obj2, float adj, vector2d temp_mv, float x_over, float y_over);
	virtual void move(void);
	
	//adjust the spawn position so that enemy does not immediately die
	void adj_spawn(vector<object*> *objs);
};

