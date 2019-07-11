#pragma once
/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include "Graphics.hpp"
#include "Input.hpp"
#include "GUI.hpp"
#include "Audio.hpp"

//Basically holds the entire Game Engine state (Basically a global, should only be one around.)
class Engine
{
private:
	long double m_time = 0.;
public:
	bool m_is_running = true;

	unsigned int frame_start;

	double m_fps = 0.;
	long double m_frame_time_l = 0.;
	double m_frame_time = 0.;
	double m_avg_fps = 0.;
	double m_avg_frame_time = 0.;

	int m_dropped_frames = 0;

	Graphics_System m_graphics;
	Input_System m_input;
	GUI_System m_gui;
	Audio_System m_audio;

	Engine();
	~Engine();

	void update();
	long double delta_time();
	long double get_time();

	void delay(int ms);
};