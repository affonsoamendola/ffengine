#pragma once
/*  
  Copyright Affonso Amendola 2019
  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "SDL2/SDL.h"

#include "Engine_System.hpp"

enum MUS_NOTE
{
	C,
	CS,
	D,
	DS,
	E,
	F,
	FS,
	G,
	GS,
	A,
	AS,
	B
};

extern std::map<MUS_NOTE, std::string> MUS_NOTE_LABEL;

//Forward decc
class Effect;


class Sample
{
public:
	bool m_is_raw_oscillation = 0;
	
	unsigned char * m_allocated_memory;

	unsigned int m_sample_rate;

	unsigned int m_sample_len;
	unsigned int m_audio_buffer_size;

	unsigned int m_oscillation_size = 0;

	unsigned int m_continuing_phase = 0;

	Sample(unsigned int sample_rate, unsigned int sample_len);
	~Sample();

	void apply_effect(Sample* original, Effect* effect);
};

enum OSCILLATOR_TYPE
{
	SQUARE_WAVE,
	SINE_WAVE,
	TRIANGLE_WAVE,
	SAWTOOTH,
	REV_SAWTOOTH
};

enum EFFECT_TYPE
{
	ATTACK
};

class Effect
{
public:
	Effect(unsigned int sample_len);
	~Effect();

	EFFECT_TYPE m_type = ATTACK;

	unsigned int m_sample_len;

	bool m_active = false;

	float*	m_current_profile;

	unsigned int m_last_t = 0;

	void reset_effect(){m_last_t = 0;}
	void update_effect(unsigned int time_shift);

	void attack_gen(unsigned int wind_up, unsigned int time_shift);
};

class Oscillator
{
	OSCILLATOR_TYPE Oscillator_Type;
public:
	Oscillator(unsigned int sample_rate, unsigned int sample_size);
	~Oscillator();

	bool m_phase_correction = true;

	Sample m_current_sample;
	
	Sample * update_sample(bool playing, unsigned int freq);

	void square_wave_gen(	unsigned char max, unsigned char min,
							unsigned int frequency, unsigned int phase_shift);
};

class Synth_Channel
{
	bool m_active = false;
	unsigned int m_current_frequency = 0;
public:
	Synth_Channel(unsigned int sample_rate, unsigned int sample_size);
	~Synth_Channel(){};

	inline bool get_active(){return m_active;}
	inline void set_active(bool state)
	{
		m_active = state; 
		m_effect.m_active = state;
	}

	void set_note(MUS_NOTE new_note, unsigned int octave);
	inline unsigned int get_frequency(){return m_current_frequency;}

	unsigned int m_current_instrument = 0;

	MUS_NOTE m_current_note = C;
	unsigned int m_current_octave = 0;

	Sample m_sample;

	Effect m_effect;
	Oscillator m_oscillator;

	Sample * get_more_audio();
};

class Audio_System : public Engine_System
{
private:
	unsigned char * m_audio_buffer;
	unsigned int m_sample_len;
	unsigned int m_audio_buffer_size;
	unsigned int m_sample_rate;
	SDL_AudioSpec m_audio_system_spec;

public:
	Audio_System(Engine * parent_engine, unsigned int sample_rate = 44100, unsigned int audio_buffer_size = 512);
	~Audio_System();

	std::vector<Synth_Channel*> m_synth_channels;

	Synth_Channel* get_free_channel(unsigned int instrument);

	void update();
};

void callback(void * userdata, unsigned char * audio_stream, int len);
						
unsigned char square_wave(	int x, unsigned char max, unsigned char min, unsigned int* carry,
							unsigned int phase, unsigned int frequency, unsigned int sample_rate);

unsigned char sine_wave(	int x, unsigned char max, unsigned char min, unsigned int* carry,
							unsigned int phase, unsigned int frequency, unsigned int sample_rate);

unsigned char triangle_wave(int x, unsigned char max, unsigned char min, unsigned int* carry,
							unsigned int phase, unsigned int frequency, unsigned int sample_rate);

unsigned char sawtooth_wave(int x, unsigned char max, unsigned char min, unsigned int* carry,
							unsigned int phase, unsigned int frequency, unsigned int sample_rate);


unsigned int get_frequency_note(MUS_NOTE note, int octave);

