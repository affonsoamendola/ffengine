/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/
#include "SDL2/SDL.h"

#include "Input.hpp"
#include "Engine.hpp"

//INPUT SYSTEM CLASS MEMBER FUNCTIONS:
//Creates Input Subsystem.
Input_System::Input_System(Engine * parent_engine) : Engine_System(parent_engine)
{}

//Called once every frame, updates key states, and does polling on keyboard events.
void Input_System::update()
{
	this->m_keyboard_state 	=	SDL_GetKeyboardState(NULL); 
	this->m_mouse_state 	= 	SDL_GetMouseState(&this->m_mouse_x, &this->m_mouse_y);

	while(SDL_PollEvent(&(this->m_event)))
	{
		if(	this->m_event.type == SDL_KEYDOWN)
		{
			switch(this->m_event.key.keysym.scancode)
			{
				case SDL_SCANCODE_F12:
					this->m_parent_engine->m_graphics.m_show_fps = !this->m_parent_engine->m_graphics.m_show_fps;
					break;
				case SDL_SCANCODE_F11:
					this->m_parent_engine->m_graphics.m_show_frame_time = !this->m_parent_engine->m_graphics.m_show_frame_time;
					break;
			}
		}

		if(	(this->m_event.type == SDL_QUIT) ||
			(this->m_event.type == SDL_KEYDOWN && this->m_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
		{
			this->m_parent_engine->m_is_running = false;
			break;
		}
	}
}
//-------------------------