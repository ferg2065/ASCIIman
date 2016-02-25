#pragma once
#include "object.h"

class bullet : public object
{
private:
	int type;

public:
	bullet(float _gravity);
	bullet(vector2d _p, int type,int dir,float _gravity);
	bullet(float pt_x, float pt_y,int dir, int type, float _gravity);
	~bullet(void);

	virtual void initialize(float _gravity);

	int get_type(void);
	void set_type(int _type);
};

