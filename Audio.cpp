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
#include "SDL2/SDL_mixer.h"

using namespace std;

//Testing wave playing
Sample test_sample(440);
Mix_Chunk chunk;

//AUDIO SYSTEM MEMBER FUNCTIONS:
//Creates audio subsystem.
Audio_System::Audio_System(Engine * parent_engine)
							: Engine_System(parent_engine)
{
	cout << "Initting Audio Mixer..." << std::flush;
	
	if(Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3 != MIX_INIT_MP3)
	{
		SDL_Log("\nProblem initializing SDL_Mixer: %s", Mix_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	cout << "Opening Audio Channels..." << std::flush;
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		SDL_Log("\nProblem Opening Audio Channels: %s", Mix_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	Square_Wave_Gen(	&test_sample,
						255, 30,
						1, 0.);
	
	chunk = test_sample.get_chunk();

	Mix_PlayChannel(-1, &chunk, -1);
}

//Deletes audio subsystem.
Audio_System::~Audio_System()
{
	Mix_CloseAudio();
	Mix_Quit();
}

void Audio_System::update()
{}

//------------------------------------------

Sample::Sample(unsigned int sample_size)
{
	this->m_phased_sample_size = sample_size;
	this->m_total_sample_size = sample_size + 2;
	this->m_allocated_memory = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * (sample_size+2) * 2));
}

Sample::~Sample()
{
	free(this->m_allocated_memory);
}

Synth::Synth(unsigned int sample_size)
{}

Synth::~Synth()
{}

Oscillator::Oscillator(unsigned int sample_size)
{}

Oscillator::~Oscillator()
{}

void Square_Wave_Gen(	Sample* to_fill,
						unsigned char max, unsigned char min,
						int frequency, float phase_shift)
{
	unsigned int wave_size = static_cast<unsigned int>((to_fill->m_phased_sample_size/frequency)/2);
	
	to_fill->m_oscillation_size = (to_fill->m_phased_sample_size/frequency);
	to_fill->m_phase_shift = phase_shift;

	for(int i = 0; i < frequency + 2 ; i++)
	{
		memset(to_fill->get_raw_memory() + i * wave_size * 2, max, wave_size);
		memset(to_fill->get_raw_memory() + wave_size + i * wave_size * 2, min, wave_size);
	}
}	