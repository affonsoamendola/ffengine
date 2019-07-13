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

enum NOTE_NAME
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

struct Note
{
	NOTE_NAME mus_note;
	int octave = 0;
};

extern std::map<NOTE_NAME, std::string> NOTE_NAME_LABEL;

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

	void copy(const Sample& sample);
	void mix(const Sample* sample);

	void clear(){memset(m_allocated_memory, 0, m_audio_buffer_size);};

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
	ATTACK,
	DECAY
};

class Effect
{
public:
	Effect(unsigned int sample_len);
	~Effect();

	EFFECT_TYPE m_type = DECAY;

	unsigned int m_sample_len;

	bool m_active = false;

	float*	m_current_profile;

	unsigned int m_last_t = 0;

	void reset_effect(){m_active = false; m_last_t = 0;}
	bool update_effect(unsigned int time_shift);

	void on_excite();
	void on_release();

	bool attack_gen(unsigned int wind_up, unsigned int time_shift);
	bool decay_gen(unsigned int wind_down, unsigned int time_shift);
};

class Oscillator
{
	OSCILLATOR_TYPE Oscillator_Type;
public:
	Oscillator(unsigned int sample_rate, unsigned int sample_size);
	~Oscillator();

	bool m_phase_correction = true;

	bool m_active = false;
	unsigned int m_frequency = 440;

	Sample m_current_sample;

	void on_excite(unsigned int frequency);
	void on_release();
	
	inline void reset()
	{
		m_active = false;
		m_current_sample.clear();
	}

	Sample * update_sample();

	void square_wave_gen(	unsigned char max, unsigned char min,
							unsigned int frequency, unsigned int phase_shift);
};

class Synth_Channel
{
	bool m_free = true;
	bool m_active = false;
	bool m_excited = false;
	bool m_allow_post_effect_override = false;

	unsigned int m_current_frequency = 440;
public:
	Synth_Channel(unsigned int sample_rate, unsigned int sample_size);
	~Synth_Channel();

	inline bool get_free()
	{
		if(m_allow_post_effect_override) return m_free;
		else return !m_active;
	}
	inline bool get_active(){return m_active;}

	inline void excite()
	{
		if(m_active == true)
		{
			reset();
		}

		m_active = true;
		m_excited = true;
		m_free = false;
		m_oscillator.on_excite(m_current_frequency);

		for(int i = 0; i < m_effects.size(); i++)
		{
			m_effects[i]->reset_effect();
			m_effects[i]->on_excite();
		}	
	}

	inline void release()
	{
		m_free = true;
		m_excited =false; 

		m_oscillator.on_release();

		for(int i = 0; i < m_effects.size(); i++)
		{
			m_effects[i]->on_release();
		}
	}

	inline void reset()
	{
		m_active = false;
		m_free = true;
		m_oscillator.reset();

		for(int i = 0; i < m_effects.size(); i++)
		{
			m_effects_done[i] = false;
			m_effects[i]->reset_effect();
		}
	}

	void set_note(NOTE_NAME new_note, unsigned int octave);
	inline unsigned int get_frequency(){return m_current_frequency;}

	unsigned int m_current_instrument = 0;

	NOTE_NAME m_current_note = C;
	unsigned int m_current_octave = 0;

	Sample m_sample;

	std::vector<Effect *> m_effects;
	std::vector<bool> m_effects_done;
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
	Audio_System(Engine * parent_engine, unsigned int sample_rate = 44100, unsigned int audio_buffer_size = 1024);
	~Audio_System();
	
	unsigned int m_active_channels = 0;

	Sample m_final_mix_sample;

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


unsigned int get_frequency_note(NOTE_NAME note, int octave);

