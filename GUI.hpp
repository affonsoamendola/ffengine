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
	bool m_is_child = false;

	int (*m_render_custom)(GUI_Object * parent_object, void * userdata) = nullptr;
	void * m_render_custom_userdata = nullptr;

	int (*m_update_custom)(GUI_Object * parent_object, void * userdata) = nullptr;
	void * m_update_custom_userdata = nullptr;

	int (*m_on_click_custom)(GUI_Object * parent_object, void * userdata) = nullptr;
	void * m_on_click_custom_userdata = nullptr;

	int (*m_on_hover_custom)(GUI_Object * parent_object, void * userdata) = nullptr;
	void * m_on_hover_custom_userdata = nullptr;

public:
	unsigned int m_object_id = -1;

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
	inline void set_parent(GUI_Object * parent_object){m_parent_object = parent_object;}

	//Sets this objects on_click function.
	inline void set_on_click(int (*on_click_custom)(GUI_Object* parent_object, void*), 
							 void * userdata);
	
	//Adds an object to this objects children list.
	inline void add_child(GUI_Object * child_object)
	{
		child_object->m_parent_object = this;
		m_elements.push_back(child_object);
		child_object->m_object_id = m_elements.size() - 1;
	}

	inline void remove_child(GUI_Object * child_object)
	{
		m_elements.erase(m_elements.begin() + child_object->m_object_id);
		
		for(int i = 0; i < m_elements.size(); i++)
		{
			m_elements[i]->m_object_id = i;
		}
	}

	void virtual render();
	void virtual update();

	void virtual on_hover();
	void virtual on_click();
};

class GUI_System : public Engine_System
{
public:
	std::vector<GUI_Object*> m_object_list;
	Texture m_gui_texture;

	void update();

	void render();

	inline void remove_base_object(GUI_Object * base_object)
	{
		m_object_list.erase(m_object_list.begin() + base_object->m_object_id);
		
		for(int i = 0; i < m_object_list.size(); i++)
		{
			m_object_list[i]->m_object_id = i;
		}
	}

	GUI_System(Engine * parent_engine);
	~GUI_System();
};