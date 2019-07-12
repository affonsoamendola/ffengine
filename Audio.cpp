/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/
/*
	TODO:
	Make it work.
	Software Synthesizer.
	Play samples (.wav and others)
	Play Music (.ogg and others)
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

#include "Engine.hpp"
#include "Utility.hpp"
#include "Audio.hpp"

#include "SDL2/SDL.h"

using namespace std;

//AUDIO SYSTEM MEMBER FUNCTIONS:
//Creates audio subsystem.

Audio_System::Audio_System(Engine * parent_engine, unsigned int sample_rate, unsigned int sample_len)
							: 	Engine_System(parent_engine),
								m_sample_len(sample_len),
								m_audio_buffer_size(sample_len*2),
								m_sample_rate(sample_rate)
{
	cout << "Initting SDL Audio Subsystem..." << std::flush;
	
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("\nProblem initializing SDL Audio Subsystem: %s", SDL_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	cout << "Opening Audio Channels..." << std::flush;

	SDL_memset(&this->m_audio_system_spec, 0, sizeof(this->m_audio_system_spec));

	this->m_audio_system_spec.freq = 44100;
	this->m_audio_system_spec.format = AUDIO_U8;
	this->m_audio_system_spec.channels = 2;
	this->m_audio_system_spec.samples = this->m_audio_buffer_size;
	this->m_audio_system_spec.callback = callback;
	this->m_audio_system_spec.userdata = this;

	if(SDL_OpenAudio(&this->m_audio_system_spec, NULL) < 0)
	{
		SDL_Log("\nProblem initializing opening audio channels: %s", SDL_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	for(int i = 0; i < 16; i++)
	{
		m_synth_channels.push_back(new Synth_Channel(m_audio_system_spec.freq, m_sample_len));
	}

	SDL_PauseAudio(0);
}

//Deletes audio subsystem.
Audio_System::~Audio_System()
{
	SDL_LockAudio();

	for(int i = 0; i < 16; i++)
	{
		delete m_synth_channels[i];
	}

	SDL_CloseAudio();
}

Synth_Channel* Audio_System::get_free_channel(unsigned int instrument)
{
	Synth_Channel* current_channel = nullptr;
	for(int i = 0; i < 16; i++)
	{
		current_channel = m_synth_channels[i];
		if(current_channel->get_active() == false && current_channel->m_current_instrument == instrument)
		{
			return current_channel;
		}
	}

	return nullptr;
}

unsigned int key_octave = 4;

std::map<SDL_Scancode, Synth_Channel*> key_channel;

std::map<SDL_Scancode, Note> key_map = 
{
	{SDL_SCANCODE_Q, 			{B,-1}},
	{SDL_SCANCODE_W,		 	{C, 0}},
	{SDL_SCANCODE_S, 		   {CS, 0}},
	{SDL_SCANCODE_E, 			{D, 0}},
	{SDL_SCANCODE_D, 		   {DS, 0}},
	{SDL_SCANCODE_R, 			{E, 0}},
	{SDL_SCANCODE_T, 			{F, 0}},
	{SDL_SCANCODE_G, 		   {FS, 0}},
	{SDL_SCANCODE_Y, 			{G, 0}},
	{SDL_SCANCODE_H, 		   {GS, 0}},
	{SDL_SCANCODE_U,		 	{A, 0}},
	{SDL_SCANCODE_J, 		   {AS, 0}},
	{SDL_SCANCODE_I, 			{B, 0}},
	{SDL_SCANCODE_O, 			{C, 1}},
	{SDL_SCANCODE_L,		   {CS, 1}},
	{SDL_SCANCODE_P, 			{D, 1}},
	{SDL_SCANCODE_LEFTBRACKET, {DS, 1}},
	{SDL_SCANCODE_RIGHTBRACKET, {E, 1}},
};

void Audio_System::update()
{
	Input_System * input_system = &this->m_parent_engine->m_input;
	Synth_Channel* free_channel = nullptr;

	if 		(input_system->m_key_down[SDL_SCANCODE_1])
	{	
		key_octave = 1;
	}else if(input_system->m_key_down[SDL_SCANCODE_2])
	{
		key_octave = 2;
	}else if(input_system->m_key_down[SDL_SCANCODE_3])
	{
		key_octave = 3;
	}else if(input_system->m_key_down[SDL_SCANCODE_4])
	{
		key_octave = 4;
	}else if(input_system->m_key_down[SDL_SCANCODE_5])
	{
		key_octave = 5;
	}else if(input_system->m_key_down[SDL_SCANCODE_6])
	{
		key_octave = 6;
	}

	for(auto it = key_map.begin(); it != key_map.end(); it++)
	{
		if(input_system->m_key_down[it->first])
		{
			free_channel = get_free_channel(0);
			key_channel[it->first] = free_channel;
			free_channel->set_active(true);
			free_channel->set_note(it->second.mus_note, it->second.octave + key_octave);
		}

		if(input_system->m_key_up[it->first])
		{
			key_channel[it->first]->set_active(false);
			key_channel.erase(it->first);
		}
	}
}

void callback(void * userdata, unsigned char * audio_stream, int len)
{
	Audio_System* audio_system = (Audio_System*)userdata;

	bool is_playing = false;

	memset(audio_stream, 0, len);

	for(int i = 0; i < audio_system->m_synth_channels.size(); i++)
	{
		Sample* current_sample = audio_system->m_synth_channels[i]->get_more_audio();

		if(audio_system->m_synth_channels[i]->get_active())
		{
			is_playing = true;

			SDL_MixAudio(	audio_stream, 
						 	current_sample->m_allocated_memory, 
						 	len, SDL_MIX_MAXVOLUME);	
		}
	}
}

//------------------------------------------

//SAMPLE CLASS MEMBER FUNCTIONS
Sample::Sample(unsigned int sample_rate, unsigned int sample_len)
{
	this->m_sample_rate = sample_rate;
	this->m_sample_len = sample_len;
	this->m_audio_buffer_size = sample_len * 2;
	this->m_allocated_memory = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * this->m_audio_buffer_size));
}

Sample::~Sample()
{
	free(this->m_allocated_memory);
}

void Sample::apply_effect(Sample* original, Effect* effect)
{
	if(m_sample_len != original->m_sample_len) {printf("Trying to store a sample of different size than this sample holds, exiting"); exit(1);}
	if(m_sample_len != effect->m_sample_len) {printf("Trying to apply effect of one size to sample of different size."); exit(1);}

	for(int i = 0; i < m_sample_len; i++)
	{
		*(m_allocated_memory + i * 2) = *(original->m_allocated_memory + i * 2) * (*(effect->m_current_profile + i));
		*(m_allocated_memory + 1 + i * 2) = *(original->m_allocated_memory + 1 + i * 2) * (*(effect->m_current_profile + i));
	}
}

//-----------------------------

//EFFECT CLASS MEMBER FUNCTIONS
Effect::Effect(unsigned int sample_len)
				:m_sample_len(sample_len)
{
	m_current_profile = static_cast<float*>(malloc(sizeof(float) * sample_len));
}

Effect::~Effect()
{
	free(m_current_profile);
}

void Effect::update_effect(unsigned int time_shift)
{
	if(m_type == ATTACK && m_active == true)
	{
		attack_gen(6000, time_shift);
	}
}

void Effect::attack_gen(unsigned int wind_up, unsigned int t)
{
	float slope = 1./wind_up;

	for(int i = 0; i < m_sample_len; i++)
	{
		if(i + t > wind_up) m_current_profile[i] = 1.;
		else
		{
			m_current_profile[i] = (i + t) * slope;
		}
	}

	m_last_t = m_sample_len + t;
}

//

//OSCILLATOR CLASS MEMBER FUNCTIONS
Oscillator::Oscillator(unsigned int sample_rate, unsigned int sample_len)
					   :m_current_sample(sample_rate, sample_len)
{}

Oscillator::~Oscillator()
{}

Sample * Oscillator::update_sample(bool playing, unsigned int freq)
{
	if(playing == true)
	{
		square_wave_gen(255, 1, 
						freq, 
						m_current_sample.m_continuing_phase * (0 + m_phase_correction));
	}
	else
	{
		memset( m_current_sample.m_allocated_memory, '\0', 
				m_current_sample.m_audio_buffer_size);
	}

	return &m_current_sample;
}

void Oscillator::square_wave_gen(	unsigned char max, unsigned char min,
									unsigned int frequency, unsigned int phase_shift)
{
	for(int i = 0; i < m_current_sample.m_sample_len; i++)
	{
		unsigned char value = square_wave(	i, max, min, 
											&m_current_sample.m_continuing_phase, 
											phase_shift, frequency, m_current_sample.m_sample_rate);
		
		*(m_current_sample.m_allocated_memory + i * 2) = value;
		*(m_current_sample.m_allocated_memory + 1 + i * 2) = value;
	}
}	
//--------------------------------

//SYNTH CHANNEL CLASS MEMBER FUNCTIONS

Synth_Channel::Synth_Channel(unsigned int sample_rate, unsigned int sample_len)
						     :	m_oscillator(sample_rate, sample_len),
						     	m_effect(sample_len),
						     	m_sample(sample_rate, sample_len)
{
}

inline void Synth_Channel::set_note(NOTE_NAME new_note, unsigned int octave)
{
	m_current_frequency = get_frequency_note(new_note, octave);
	m_current_note = new_note;
	m_current_octave = octave;
}

Sample* Synth_Channel::get_more_audio()
{
	m_effect.update_effect(m_effect.m_last_t);
	m_oscillator.update_sample(m_active, m_current_frequency);

	m_sample.apply_effect(&m_oscillator.m_current_sample, &m_effect);

	return &m_sample;
}

//-------------------------------

//NON-MEMBER RELATED FUNCTIONS AND DEFINITIONS

std::map<NOTE_NAME, std::string> NOTE_NAME_LABEL = 
{
	{C, "C"},
	{CS, "C#"},
	{D, "D"},
	{DS, "D#"},
	{E, "E"},
	{F, "F"},
	{FS, "F#"},
	{G, "G"},
	{GS, "G#"},
	{A, "A"},
	{AS, "A#"},
	{B, "B"}
};

unsigned char square_wave(	int x, unsigned char max, unsigned char min, unsigned int* carry,
							unsigned int phase, unsigned int frequency, unsigned int sample_rate)
{
	unsigned int wave_size = sample_rate / (2*frequency);
	unsigned int oscillation_size = wave_size * 2;

	//How much along the current oscillation you are, can be between 0 and oscillation_size
	unsigned int position_on_oscillation = (x + phase) % oscillation_size;
	*carry = position_on_oscillation;

	if(position_on_oscillation < wave_size) return max;
	else return min; 
}

unsigned int get_frequency_note(NOTE_NAME note, int octave)
{
	unsigned int perfect_piano_key = octave * 12 + note;

	double exponent = (perfect_piano_key - 57.) / 12.;

	return static_cast<unsigned int>(pow(2., exponent) * 440.);
}

//----------------------------