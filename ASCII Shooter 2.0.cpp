#pragma once
#include "engine.h"
#include <Windows.h>

int main()
{ 
	//declare an instance of my game engine
	//pass it whatever modifier i have decided to use for gravity
	engine myengine((float)0.2);
	do 
	{
		// render function gets c-strings and x,y coords for 
		// each object and uses curses to render them
		myengine.render();

		// update function does all collision detection and
		// movement for game objects
		myengine.update();

		//pause in-between frames
		Sleep(60);

	// continue to loop until the quit boolean is true
	}while (!myengine.get_quit());
	return 0;
}




