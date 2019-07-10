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
public:
	Audio_System(Engine * parent_engine);
	~Audio_System();

	void update();
};

class Sample
{
public:
	Sample(unsigned int sample_size);
	~Sample();
};

class Synth
{
public:
	Synth(unsigned int sample_size);
	~Synth();

	Mix_Chunk m_current_chunk;

	Sample m_current_sample;
	unsigned int m_sample_size;	
};

enum OSCILLATOR_TYPE
{
	SQUARE_WAVE,
	SINE_WAVE,
	TRIANGLE_WAVE,
	SAWTOOTH,
	REV_SAWTOOTH
};

class Oscillator
{
	unsigned char * m_allocated_memory;
	unsigned int m_sample_size;
	float phase_shift;

	OSCILLATOR_TYPE Oscillator_Type;
public:
	Oscillator(unsigned int sample_size);
	~Oscillator();

	void Reset_Sampling();
	
	unsigned char * Get_Data();
};

void Square_Wave_Gen(	unsigned char* sample_location,
						int sample_size,
						unsigned char max, unsigned char min,
						int frequency, float phase_shift);
