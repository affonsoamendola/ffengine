#pragma once

#include <memory>

#include "SDL2/SDL.h"

#include "Engine_System.hpp"

class Engine;

class Input_System : public Engine_System
{
private:
	SDL_Event m_event;

public:
	const unsigned char * m_keyboard_state;
	int m_mouse_state;

	int m_mouse_x;
	int m_mouse_y;

	Input_System(Engine * parent_engine);

	void update();
};

