#pragma once

#include "Engine_System.hpp"
#include "Graphics.hpp"

#include "Rect.hpp"

#include <vector>

class GUI_Window : public GUI_Object
{
public:
	Point2 m_size;

	void render();

	Recti get_rect();

	GUI_Window(const Recti& local_rect, GUI_System* parent_system);
	~GUI_Window(){};
};

class GUI_Window_Title : public GUI_Object
{
private:
	int m_length;
	std::string m_text;

	Point2 m_local_text_location;
public:
	void render();

	GUI_Window_Title(GUI_Window* parent_window, std::string text, int length, GUI_System* parent_system);
	~GUI_Window_Title(){};
};


class GUI_Button : public GUI_Object
{
public:
	Sprite* current_spr;
	Sprite  idle_spr;
	Sprite  on_hover_spr;
	Sprite  on_click_spr;

	void render();
};