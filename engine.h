#pragma once
//i use windows.h to get access to asynchronous keyboard data
//i poll the state of individual keys whenever i want to 
#include <Windows.h>
//time.h is used for getting better random numbers
#include <time.h>
#include <vector>
#include "ascii_man.h"
#include "curses.h"
#include "platform.h"
#include "enemy.h"
#include "bullet.h"

#pragma once
class engine
{
private:
	vector<object*> objects; 

	//constant pointer to asciiman object
	ascii_man *dude;
	//level shifter for allowing scroll effect in game
	float level_shift;
	int level_size;
	bool quit;				// quit game boolean, for main() while loop equit
	int ymax,xmax;			// console width / height
	//gravity modifier
	float gravity;

	void poll_keys(void);	// poll current key states on keys i want 
	void new_level(void);	//generate new level

public:
	engine(float _gravity);
	~engine(void);
	
	float get_gravity(void);
	void set_gravity(float _gravity);
	float l_pos(void);
	void l_pos(float new_pos);
	int r_bound(void);
	int l_bound(void);
	int get_level_size(void);
	void set_level_size(int _size);


	int get_xmax(void);
	int get_ymax(void);
	bool get_quit(void);
	void shoot(void);

	void update(void);
	void render(void);
};

