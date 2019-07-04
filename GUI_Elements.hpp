#pragma once

#include "Engine_System.hpp"
#include "Graphics.hpp"

#include "Rect.hpp"

#include <vector>

class GUI_Window : public GUI_Object
{
private:
	Recti m_rect;
public:
	void render();

	GUI_Window(const Recti& local_rect, const Point2& position, GUI_System* parent_system);
	~GUI_Window(){};
};

class GUI_Window_Title : public GUI_Object
{
private:
	int m_length;
	std::string m_text;
public:
	void render();

	GUI_Window_Title(const std::string text, int length, GUI_System* parent_system);
	~GUI_Window_Title(){};
};
