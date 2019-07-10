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

Sample::Sample(unsigned int sample_size)
{}
Sample::~Sample()
{}

Synth::Synth(unsigned int sample_size)
			: m_current_sample(sample_size)
{
}

Synth::~Synth()
{}

Oscillator::Oscillator(unsigned int sample_size)
{
	this->m_allocated_memory = static_cast<unsigned char *>(malloc(sample_size * 2));
	this->m_sample_size = sample_size;
}

Oscillator::~Oscillator()
{
	free(this->m_allocated_memory);
}

void Square_Wave_Gen(	unsigned char* sample_location,
						int sample_size,
						unsigned char max, unsigned char min,
						int frequency, float phase_shift)
{
	unsigned int wave_size = static_cast<unsigned int>((sample_size/frequency)/2);
	unsigned int phase_shift_sample = static_cast<unsigned int>(phase_shift * wave_size * 2);

	printf("WAVE SIZE %u\n", wave_size);
	printf("phase_shift_sample %u\n", phase_shift_sample);

	for(int i = 0; i < frequency-1; i++)
	{
		memset(sample_location + i * wave_size * 2 + phase_shift_sample, max, wave_size);
		memset(sample_location + wave_size + i * wave_size * 2 + phase_shift_sample, min, wave_size);
	}
}	