#pragma once
/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

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
	Graphics_System* m_graphics_system = nullptr;

	std::vector<GUI_Object*> m_elements;
	GUI_Object* m_parent_object = nullptr;

	Point2 m_local_position = {0, 0};

	GUI_Object(const Point2& position, GUI_System* parent_system);
	GUI_Object(GUI_Object* parent_object, const Point2& local_position, GUI_System* parent_system);

	~GUI_Object();

	GUI_Object * get_base();
	Point2 get_global_position();
	Point2 get_global_position(const Point2& local_position);

	//Sets this objects parent.
	inline void set_parent(GUI_Object * parent_object){this->m_parent_object = parent_object;}
	
	//Adds an object to this objects children list.
	inline void add_child(GUI_Object * child_object){this->m_elements.push_back(child_object);}

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