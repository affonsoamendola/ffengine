#include "SDL2/SDL.h"

#include "Input.hpp"
#include "Engine.hpp"

Input_System::Input_System(Engine * parent_engine) : Engine_System(parent_engine)
{}

void Input_System::update()
{
	this->m_keyboard_state 	=	SDL_GetKeyboardState(NULL); 
	this->m_mouse_state 	= 	SDL_GetMouseState(&this->m_mouse_x, &this->m_mouse_y);

	/*
	if(keystate[SDL_SCANCODE_UP]) this->m_parent_engine->m_raymarcher.m_camera_position.z += 1. * this->m_parent_engine->delta_time();
	if(keystate[SDL_SCANCODE_DOWN]) this->m_parent_engine->m_raymarcher.m_camera_position.z -= 1. * this->m_parent_engine->delta_time();
	if(keystate[SDL_SCANCODE_RIGHT]) this->m_parent_engine->m_raymarcher.m_camera_position.x += 1. * this->m_parent_engine->delta_time();
	if(keystate[SDL_SCANCODE_LEFT]) this->m_parent_engine->m_raymarcher.m_camera_position.x -= 1. * this->m_parent_engine->delta_time();
	*/

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