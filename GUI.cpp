#include "GUI.hpp"
#include "GUI_Elements.hpp"

#include "Rect.hpp"
#include "Engine.hpp"
#include <string>

GUI_System::GUI_System(	Engine * parent_engine) 
						: 	Engine_System(parent_engine),
							m_gui_texture("gui.png", parent_engine->m_graphics)

{
	GUI_Window* Test = new GUI_Window(Recti({49, 49}).move(Point2({30, 20})), this);
	new GUI_Window_Title(Test, "Window", 6, this);
}

GUI_System::~GUI_System()
{
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		delete this->m_object_list[i];
	}
}

void GUI_System::update()
{
}

void GUI_System::render()
{
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		this->m_object_list[i]->render();
	}
}

GUI_Object::GUI_Object(	const Point2& position, GUI_System* parent_system)
{
	this->m_is_base = true;

	this->m_parent_system = parent_system;
	this->m_graphics_system = &this->m_parent_system->m_parent_engine->m_graphics;

	this->m_parent_system->m_object_list.push_back(this);

	this->m_local_position = position;
}

GUI_Object::GUI_Object(	GUI_Object* parent_object, const Point2& local_position, GUI_System* parent_system)
{
	this->m_is_base = false;
	
	this->m_parent_object = parent_object;
	this->m_parent_object->m_elements.push_back(this);

	this->m_parent_system = parent_system;
	this->m_graphics_system = &this->m_parent_system->m_parent_engine->m_graphics;

	this->m_local_position = local_position;
}

GUI_Object::~GUI_Object()
{
	for(int i = 0; i < this->m_elements.size(); i++)
	{
		delete this->m_elements[i];
	}
}

GUI_Object* GUI_Object::get_base()
{
	GUI_Object* current_object = this;
	
	while(!(current_object->m_is_base))
	{
		current_object = current_object->m_parent_object;
	}

	return current_object;
}

Point2 GUI_Object::get_global_position(const Point2& local_position)
{
	Point2 current_position(0, 0);
	
	GUI_Object* current_object = this;

	current_position += local_position;
	
	while(!(current_object->m_is_base))
	{
		current_object = current_object->m_parent_object;
		current_position += current_object->m_local_position;
		
	}

	return current_position;
}

Point2 GUI_Object::get_global_position()
{
	return this->get_global_position(this->m_local_position);
}




