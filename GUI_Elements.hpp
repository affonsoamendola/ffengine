#pragma once

#include "Engine_System.hpp"
#include "Graphics.hpp"

#include "Rect.hpp"

#include <vector>

class GUI_Window : public GUI_Object
{
public:
	Recti m_rect;

	void render();

	GUI_Window(const Recti& local_rect, const Point2& position, GUI_System* parent_system);
	~GUI_Window(){};
};

class GUI_Window_Title : public GUI_Object
{
private:
	int m_length;
	std::string m_text;

	Point2 m_text_location;

public:
	void render();

	GUI_Window_Title(GUI_Window* parent_window, std::string text, int length, GUI_System* parent_system);
	~GUI_Window_Title(){};
};
