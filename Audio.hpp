/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/
#pragma once

#include <string>
#include <memory>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "Engine_System.hpp"

class Audio_System : public Engine_System
{
	Audio_System(Engine * parent_engine);
	~Audio_System();

	void update();
};

class Synth
{
public:
	Synth(unsigned int sample_rate);
	~Synth();

	Mix_Chunk current_chunk;

	unsigned char * current_sample;
	unsigned int sample_rate;	
};