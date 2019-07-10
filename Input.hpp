#pragma once
/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

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

