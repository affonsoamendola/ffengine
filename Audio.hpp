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

#include "Engine_System.hpp"

class Sample
{
public:
	bool m_is_raw_oscillation = 0;
	
	unsigned char * m_allocated_memory;

	unsigned int m_phased_sample_size;
	unsigned int m_total_sample_size;
	unsigned int m_sample_rate;

	unsigned int m_raw_bytes;

	unsigned int m_oscillation_size = 0;

	float m_phase_shift = 0.;
	float m_next_sample_phase = 0.;

	Sample(unsigned int sample_rate, unsigned int sample_size);
	~Sample();

	inline unsigned char * get_raw_memory(){return m_allocated_memory;};
	inline unsigned char * get_phase_shifted_memory(){return Phase_Shift(this->m_phase_shift);};

	inline unsigned char * Phase_Shift(float amount) 
	{return m_allocated_memory + static_cast<int>(this->m_oscillation_size*2 * amount);};
};

class Synth_Channel
{
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
	OSCILLATOR_TYPE Oscillator_Type;
public:
	Oscillator(unsigned int sample_rate, unsigned int sample_size);
	~Oscillator();

	bool m_active = true;
	bool m_phase_correction = true;

	unsigned int m_current_frequency = 440;

	Sample m_current_sample;

	void reset_sampling();
	
	Sample * update_sample();
};

class Audio_System : public Engine_System
{
private:
	unsigned char * m_audio_buffer;
	unsigned int m_audio_buffer_size;
	unsigned int m_sample_rate;
	SDL_AudioSpec m_audio_system_spec;

public:
	Audio_System(Engine * parent_engine, unsigned int sample_rate = 44100, unsigned int audio_buffer_size = 512);
	~Audio_System();

	Oscillator m_current_oscillator;

	void update();
};

void callback(void * userdata, unsigned char * audio_stream, int len);

void Square_Wave_Gen(	Sample* to_fill,
						unsigned char max, unsigned char min,
						int frequency, float phase_shift);
