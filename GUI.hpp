#pragma once

#include "Engine_System.hpp"
#include "Graphics.hpp"

#include "Rect.hpp"

#include <vector>

class GUI_System;

class GUI_Object
{
private:
	bool m_is_base = false;
public:
	GUI_System* m_parent_system = nullptr; 

	std::vector<GUI_Object*> m_elements;
	GUI_Object* m_parent_object = nullptr;

	Point2 m_global_position = {0, 0};
	Point2 m_local_position = {0, 0};

	GUI_Object(const Point2& position, GUI_System* parent_system);
	GUI_Object(GUI_Object* parent_object, const Point2& local_position, GUI_System* parent_system);

	~GUI_Object();

	GUI_Object * get_base();

	void virtual render(){printf("RENDERING OBJECT\n");}

	void virtual on_update(){}

	void virtual on_hover(){}
	void virtual on_click(){}
};

class GUI_System : public Engine_System
{
public:
	std::vector<GUI_Object*> m_object_list;
	Texture m_gui_texture;

	void update();

	void render();

	GUI_System(Engine * parent_engine);
	~GUI_System();
};