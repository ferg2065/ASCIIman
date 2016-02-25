#pragma once
#include <cstdlib>
#include <math.h>

//this class gave me access to a number of functions i was using 
//for collision detection on circles

//turned out i had no real use for circles
//and i didnt really need vector math for rectangle collisions
class vector2d
{
private:
	float x,y;

public:

	vector2d(void);
	vector2d(float _x, float _y);
	vector2d(vector2d v1, vector2d v2);
	vector2d(float x1, float y1,float x2, float y2);
	~vector2d(void);

	void	new_v(float _x, float _y);
	float	get_x(void);
	void	set_x(float _x);
	float	get_y(void);
	void	set_y(float _y);
	float	slope(void);

	//set equality of 2d vector2d
	vector2d&		operator=(vector2d& v);

	//test equality of 2d vector2ds
	bool			operator==(vector2d v);

	//add vector2ds
	vector2d		operator+(vector2d v);

	//subtract vector2ds
	vector2d		operator-(vector2d v);

	//scale a vector2d
	vector2d		operator*(float i);

	//normalize vector
	vector2d		normalize(void);

	//get dot product of normalize vector2d and vector2d argument
	float		normal_dot(vector2d v);

	//get scalar projection
	float		scalar_proj(float n, vector2d b);

	//returns the magnetude of the vector2d squared
	float		magnetude(void);

	//returns the dot product of two vector2ds
	float		dot(vector2d v);
};

