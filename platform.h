#pragma once
#include "object.h"

class platform : public object
{
public:
	platform(float _gravity);
	platform(vector2d _pt, vector2d _xt, float _gravity);
	platform(float pt_x, float pt_y, float xt_x,float xt_y, float _gravity);
	~platform(void);

	void initialize(float _gravity);
};

