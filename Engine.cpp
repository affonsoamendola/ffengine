/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine
  
  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include <iostream>

#include "Engine.hpp"
#include "SDL2/SDL.h"

/*
    TODO:
    Better way of counting m_time.
    Does delta_time() actually work as intended, i.e. the time between the last two frames?
*/

//How many frames to do the average framerate counter.
#define AVERAGE_FRAME_T_SAMPLING 60
//What do I consider a dropped frame
#define DROPPED_FRAME_THRESHOLD 15

using namespace std;

//Engine constructor, this is where all systems are initialized along with the main Engine container.
Engine::Engine()
	:	m_graphics(this),
		m_input(this),
		m_gui(this),
    m_audio(this)
{
    cout << "Initting SDL..." << std::flush;

    //Start SDL
    if(SDL_Init(SDL_INIT_TIMER) != 0)
    {
      SDL_Log("\nProblem initializing SDL: %s", SDL_GetError());
      exit(1);
    }

    cout << "Done." << std::endl;
}

Engine::~Engine()
{
  SDL_Quit();
}

void Engine::delay(int ms)
{
  long double start_time = this->get_time();
  while(this->get_time() < start_time + ms * 0.001)
  {
  }
}

//Vector holding the last AVERAGE_FRAME_T_SAMPLING number of frametimes, to calculate the average framerate.
vector<double> average_frame_time = vector<double>(AVERAGE_FRAME_T_SAMPLING, 0.);

//Counter to substitute in new frame times on top of old ones on the vector right above
int current_average = 0;


//Main update function, calls all other updates and keeps track of time and framerate.
void Engine::update()
{
  this->frame_start = SDL_GetPerformanceCounter();

  //Updates()
  this->m_graphics.update();
  this->m_input.update();
  this->m_gui.update();
  this->m_audio.update();

  //The only function that should have a render() is m_graphics, think of it as a separate update
  //On earlier versions, every render function ran on update() but I tought it would be best to keep them separate
  //Think logic update for update() and graphics update for render()
  this->m_graphics.render();

  //Calculate frametime, has long and double versions, I believe this isnt needed.
  this->m_frame_time_l = this->delta_time();
  this->m_frame_time = static_cast<double>(this->m_frame_time_l);
  this->m_fps = 1. / this->m_frame_time;

  //Resets current_average counter.
  if(current_average >= AVERAGE_FRAME_T_SAMPLING) current_average = 0;

  //This whole section just calculates the average frame time and therefor framerate
  average_frame_time[current_average] = this->m_frame_time;

  double sum = 0.;

  for(int i = 0; i < AVERAGE_FRAME_T_SAMPLING; i ++)
  {	
  	sum += average_frame_time[i];
  }

  this->m_avg_frame_time = sum / static_cast<double>(AVERAGE_FRAME_T_SAMPLING);
  this->m_avg_fps = 1. / this->m_avg_frame_time;

  current_average++;

  if(this->m_fps <= this->m_avg_fps*DROPPED_FRAME_THRESHOLD*0.01)
  {
  	this->m_dropped_frames ++;
  }

  //I think this is a bit dangerous, that is why I made m_time a long float, might have to think of a better way
  //of counting global time.
  this->m_time += this->m_frame_time_l;
}

//Returns time between calling and the start of the frame, I think its unnecessary?
//Thoughts, could just remove this and make a calling to m_frametime, to figure out how long the last frame was,
//Might introduce some delay in the physics, but one frame of delay is nothing, cmon.
long double Engine::delta_time()
{
	const unsigned int frame_end = SDL_GetPerformanceCounter();
    const static unsigned int freq = SDL_GetPerformanceFrequency();
    
	return (frame_end - this->frame_start) / static_cast<long double>(freq);
}

//Get how long the software has been up. (uptime)
long double Engine::get_time()
{
	return this->m_time;
}