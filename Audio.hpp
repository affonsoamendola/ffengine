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
	unsigned char * m_allocated_memory;
public:
	unsigned int m_phased_sample_size;
	unsigned int m_total_sample_size;

	unsigned int m_oscillation_size = 0;

	float m_phase_shift = 1.;

	Sample(unsigned int sample_size);
	~Sample();

	inline unsigned char * get_raw_memory(){return m_allocated_memory;};
	inline unsigned char * get_phase_shifted_memory(){return Phase_Shift(this->m_phase_shift);};

	Mix_Chunk get_chunk()
	{
		Mix_Chunk new_chunk;
		
		new_chunk.allocated = 0;
		new_chunk.abuf = this->get_phase_shifted_memory();
		new_chunk.alen = this->m_phased_sample_size;
		new_chunk.volume = 128;

		return new_chunk;
	}

	inline unsigned char * Phase_Shift(float amount) 
	{return m_allocated_memory + static_cast<int>(this->m_oscillation_size * amount);};
};

class Synth
{
public:
	Synth(unsigned int sample_size);
	~Synth();

	Mix_Chunk m_current_chunk;
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
	float phase_shift;

	OSCILLATOR_TYPE Oscillator_Type;
public:
	Oscillator(unsigned int sample_size);
	~Oscillator();

	void Reset_Sampling();
	
	unsigned char * Get_Data();
};

void Square_Wave_Gen(	Sample* to_fill,
						unsigned char max, unsigned char min,
						int frequency, float phase_shift);
