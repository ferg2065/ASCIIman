#include "engine.h"

engine::engine(float _gravity)
{
	set_gravity(_gravity);
	initscr();					//initialize curses mode
	keypad(stdscr,true);		//get arrow keys as well 
	noecho();					//dont echo key presses to console
	curs_set(0);				//dont show the cursor
	getmaxyx(stdscr,ymax,xmax);	//get console size in rows and columns of characters
	quit = false;

	level_shift = 0;


	new_level();

}
engine::~engine(void)
{
	endwin();
}

float engine::get_gravity(void)
{
	return gravity;
}
void engine::set_gravity(float _gravity)
{
	gravity = _gravity;
}

void engine::new_level(void)
{
	l_pos(0);
	dude = new ascii_man(get_gravity());
	//the height the platforms will be at in the game
	int pltfrm_ht = ymax-2;
	//add an initial 25 spaces of floor 
	//25/2-1 = 12
	float x_coord = 12.5;
	float platform_radius = 12.5;

	//delete existing level info and generate new
	int gap;
	objects.clear();
	platform *temp;
	temp = new platform((float)x_coord, (float)pltfrm_ht, (float)(platform_radius), (float)0.5, get_gravity());
	objects.push_back(temp);
	x_coord+=(int)platform_radius;
	srand ( (int)time(NULL) );

	do
	{
		srand (rand() ^ (int)time(NULL) );		
		gap = rand() % 10 + 4;
		//add a gap between 4 and 6 spaces wide
		//objects.insert(floor.end(),platform_radius," ");
		srand (rand() ^ (int)time(NULL) );		
		platform_radius = (float)((rand() % 15 + 5) +.5);
		x_coord+=(int)(gap+platform_radius);
		temp = new platform((float)x_coord, (float)pltfrm_ht, (float)(platform_radius), (float)0.5, get_gravity());
		//add a chunk of floor between 10 and 30 spaces wide
		objects.push_back(temp);
		x_coord+=(int)platform_radius;
	// keep adding new randomly sized chunks of floor until the level is a certain size
	}while (x_coord<300);
	level_size = (int)(x_coord+.5);

	//generate some obstacles 


	//spawn_enemies();
	for (gap=0;gap<6;gap++)
	{
		srand (rand() ^ (int)time(NULL) );		
		platform_radius = (float)(rand() % level_size + 40);
		enemy *an_enemy;
		an_enemy = new enemy(platform_radius,5,get_gravity());
		an_enemy->adj_spawn(&objects);
		objects.push_back(an_enemy);
	}

	objects.insert(objects.begin(),dude);
}

void engine::poll_keys(void)
{
	if(GetAsyncKeyState(VK_LEFT)!=0)
	{dude->set_keyL(true);}
	else
	{dude->set_keyL(false);}
	
	if(GetAsyncKeyState(VK_RIGHT)!=0)
	{dude->set_keyR(true);}
	else
	{dude->set_keyR(false);}

	if(GetAsyncKeyState(VK_UP)!=0)
	{dude->set_keyJ(true);}
	else
	{dude->set_keyJ(false);}

	if(GetAsyncKeyState(VK_SPACE)!=0)
	{dude->set_keyS(true);}
	else
	{dude->set_keyS(false);}
}
int engine::get_xmax(void)
{
	return xmax;
}
int engine::get_ymax(void)
{
	return ymax;
}
bool engine::get_quit(void)
{
	return quit;
}
void engine::update(void)
{
	/*
	in this function 
	-get user input
	-check for collisions
	-react to collisions and input as neccesary
	-move each object
	-remove dead objects from the game

	*/


	dude->reset_hit_bools();
	poll_keys();

	if (dude->get_keyS()==true)
	{
		bullet *newbullet;
		if (dude->get_dir() == 1)
		{newbullet = new bullet((dude->get_pt().get_x() + dude->get_xt().get_x()+1), dude->get_pt().get_y(), dude->get_dir(), 1 ,get_gravity());}
		else
		{newbullet = new bullet((dude->get_pt().get_x() - dude->get_xt().get_x()-1), dude->get_pt().get_y(), dude->get_dir(), 1 ,get_gravity());}
		objects.insert(objects.begin(),newbullet);
	}
	if (dude->get_keyJ()==true && dude->get_hitU() == false && dude->get_mv().get_y() >= -.5)
	{
		if (dude->get_mv().get_y() > 1)
		{
			dude->set_mv(dude->get_mv().get_x(),(float)(dude->get_mv().get_y()-.5));
		}
		else if (dude->get_mv().get_y() > -.5)
		{
			dude->set_mv(dude->get_mv().get_x(),(float)(dude->get_mv().get_y()-1.75));
		}
	}
	if(dude->get_keyL()==true && dude->get_hitL()==false)
	{
		if(dude->get_mv().get_x() > -2)
		{		
			dude->set_mv((float)(dude->get_mv().get_x()-.4),dude->get_mv().get_y());
		}
	}
	if(dude->get_keyR()==true && dude->get_hitR()==false)
	{
		if(dude->get_mv().get_x() < 2)
		{		
			dude->set_mv((float)(dude->get_mv().get_x()+.4),dude->get_mv().get_y());
		}
	}
	if(dude->get_keyR()==false && dude->get_hitR()==false && dude->get_keyL()==false && dude->get_hitL()==false)

	{
		if(dude->get_mv().get_x() < 0)
		{
			dude->set_mv((float)(dude->get_mv().get_x()+.4),dude->get_mv().get_y());
			if(dude->get_mv().get_x() > 0)
			{dude->set_mv(0,dude->get_mv().get_y());}
		}
		else if (dude->get_mv().get_x() > 0)
		{
			dude->set_mv((float)(dude->get_mv().get_x()-.4),dude->get_mv().get_y());
			if(dude->get_mv().get_x() < 0)
			{dude->set_mv(0,dude->get_mv().get_y());}
		}
	}




	/*
	level shifting code for move through the level
	*/
	if (dude->get_pt().get_x()-l_pos() < l_bound() && dude->get_pt().get_x() > l_bound())
	{
		l_pos(dude->get_pt().get_x() - l_bound());
	}
	else if (dude->get_pt().get_x()-l_pos() > r_bound() && dude->get_pt().get_x() < get_level_size()-l_bound())
	{
		l_pos((dude->get_pt().get_x() - r_bound()));
	}






	for (int i = 0;i<(int)objects.size();i++)
	{
		for (int j = i+1;j<(int)objects.size();j++)
		{
			objects[i]->check(objects[j]);
		}

		objects[i]->move();
		objects[i]->gravity();
	}

	if (dude->get_pt().get_x()-l_pos() > xmax)
	{dude->isdead(true);}
	if (dude->get_pt().get_x()-l_pos() < 0)
	{dude->isdead(true);}
	if (dude->get_pt().get_y() > ymax)
	{dude->isdead(true);}

	for (int i = 0;i < (int)objects.size();i++)
	{
		if (objects[i]->isdead()==true)
		{objects.erase(objects.begin()+i);}
	}

	if (dude->isdead())
	{new_level();}

}
void engine::render(void)
{
	string mystr;
	int _x,_y;
	clear();
	for (int i = 0;i<(int)objects.size();i++)
	{
		_y = (int)objects[i]->get_pt().get_y();
		_x = (int)objects[i]->get_pt().get_x();
		int i1 = (int)objects[i]->get_rgt();
		int i2 = (int)objects[i]->get_lft();
		if (objects[i]->get_rgt()-level_shift > 0 && objects[i]->get_lft()-level_shift < xmax)
		{objects[i]->render(xmax,ymax,level_shift);}
	}
	refresh();
}

void engine::shoot(void)
{
	bullet *newbullet;
 	newbullet = new bullet((dude->get_pt().get_x() + dude->get_xt().get_x()+1), dude->get_pt().get_y(), dude->get_dir(), 1 ,get_gravity());
 	objects.insert(objects.begin(),newbullet);
}

float engine::l_pos(void)
{
	return level_shift;
}
void engine::l_pos(float new_pos)
{
	level_shift = new_pos;
}
int engine::r_bound(void)
{
	return xmax-20;
}
int engine::l_bound(void)
{
	return 20;
}
int engine::get_level_size(void)
{
	return level_size;
}
void engine::set_level_size(int _size)
{
	level_size = _size;
}
