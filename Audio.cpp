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

#include "Engine.hpp"
#include "Utility.hpp"
#include "Audio.hpp"

#include "SDL2/SDL.h"

using namespace std;

//AUDIO SYSTEM MEMBER FUNCTIONS:
//Creates audio subsystem.

Audio_System::Audio_System(Engine * parent_engine, unsigned int sample_rate,unsigned int audio_buffer_size)
							: 	Engine_System(parent_engine),
								m_audio_buffer_size(audio_buffer_size),
								m_sample_rate(sample_rate),
								m_current_oscillator(sample_rate, audio_buffer_size/2)
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

	SDL_PauseAudio(0);

	cout << "Done." << std::endl;
}

//Deletes audio subsystem.
Audio_System::~Audio_System()
{
	SDL_CloseAudio();
}

void Audio_System::update()
{
	Input_System * input_system = &this->m_parent_engine->m_input;

	if(input_system->m_keyboard_state[SDL_SCANCODE_A])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 440;
	}
	else if (input_system->m_keyboard_state[SDL_SCANCODE_S])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 466;
	}	
	else if (input_system->m_keyboard_state[SDL_SCANCODE_D])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 494;
	}
	else if (input_system->m_keyboard_state[SDL_SCANCODE_F])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 523;
	}	
	else if (input_system->m_keyboard_state[SDL_SCANCODE_G])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 554;
	}
	else if (input_system->m_keyboard_state[SDL_SCANCODE_H])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 587;
	}
	else if (input_system->m_keyboard_state[SDL_SCANCODE_J])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 622;
	}
	else if (input_system->m_keyboard_state[SDL_SCANCODE_K])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 659;
	}
	else if (input_system->m_keyboard_state[SDL_SCANCODE_L])
	{
		this->m_current_oscillator.m_active = true;
		this->m_current_oscillator.m_current_frequency = 698;
	}
	else
	{
		this->m_current_oscillator.m_active = false;
	}

}

void callback(void * userdata, unsigned char * audio_stream, int len)
{
	Audio_System* audio_system = (Audio_System*)userdata;

	audio_system->m_current_oscillator.update_sample();
	SDL_MixAudio(audio_stream, audio_system->m_current_oscillator.m_current_sample.get_phase_shifted_memory(), len, SDL_MIX_MAXVOLUME);	
}

//------------------------------------------

Sample::Sample(unsigned int sample_rate, unsigned int sample_size)
{
	this->m_sample_rate = sample_rate;
	this->m_phased_sample_size = sample_size;
	this->m_total_sample_size = (sample_size + 2);
	this->m_raw_bytes = (sample_size + 2) * 2;
	this->m_allocated_memory = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * this->m_raw_bytes));
}

Sample::~Sample()
{
	free(this->m_allocated_memory);
}

Oscillator::Oscillator(unsigned int sample_rate, unsigned int sample_size)
						:m_current_sample(sample_rate, sample_size)
{}

Oscillator::~Oscillator()
{}

Sample * Oscillator::update_sample()
{
	if(this->m_active == true)
	{
		Square_Wave_Gen(&this->m_current_sample, 255, 1, 
						this->m_current_frequency, 
						this->m_current_sample.m_next_sample_phase * (0 + this->m_phase_correction));
	}
	else
	{
		memset(this->m_current_sample.get_raw_memory(), 1, this->m_current_sample.m_total_sample_size * 2);
		this->m_current_sample.m_phase_shift = 0.;
	}

	return &this->m_current_sample;
}

void Square_Wave_Gen(	Sample* to_fill,
						unsigned char max, unsigned char min,
						int frequency, float phase_shift)
{
	unsigned int wave_size = static_cast<unsigned int>((to_fill->m_sample_rate/frequency)/2);
	
	to_fill->m_is_raw_oscillation = true;
	to_fill->m_oscillation_size = wave_size * 2;
	to_fill->m_phase_shift = phase_shift;

	unsigned int n_oscillations = to_fill->m_phased_sample_size/to_fill->m_oscillation_size;
	to_fill->m_next_sample_phase = static_cast<double>(to_fill->m_phased_sample_size%to_fill->m_oscillation_size)/to_fill->m_oscillation_size + phase_shift;

	if(to_fill->m_next_sample_phase >= 1.) to_fill->m_next_sample_phase -= 1.;
	/*
	printf("n_oscillations %d\n", n_oscillations);
	printf("wave size %d\n", wave_size);
	printf("oscillation size %d\n", to_fill->m_oscillation_size);
	printf("m_phased_sample_size %d\n", to_fill->m_phased_sample_size);
	printf("start phase %f\n", phase_shift);
	printf("end phase %f\n", to_fill->m_next_sample_phase);*/
	for(int i = 0; i < n_oscillations + 2 ; i++)
	{
		memset(to_fill->get_raw_memory() + i * wave_size * 4, max, wave_size * 2 );
		memset(to_fill->get_raw_memory() + wave_size * 2 + i * wave_size * 4, min, wave_size * 2);
	}
}	