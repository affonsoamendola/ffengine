/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
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
}

Audio_System::~Audio_System()
{
	Mix_CloseAudio();
	Mix_Quit();
}

Synth::Synth(unsigned int sample_rate)
{
	this->current_sample = malloc(sample_rate * 2);

	current_chunk.allocated = 0;
	current_chunk.abuf = this->current_sample;
	current_chunk.alen = sample_rate * 2;
	current_chunk.volume = 128;
}

Synth::~Synth()
{
	free(this->current_sample);
}

unsigned char* Modulate()

unsigned char* Square_Wave_Gen(	unsigned char * allocated_memory,
								int sample_rate, 
								unsigned char max_r, unsigned char min_r, 
								unsigned char max_l, unsigned char min_l,
								int frequency, int phase_shift)
{

}