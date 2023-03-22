/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include "GUI.hpp"
#include "GUI_Elements.hpp"

#include "Rect.hpp"
#include "Engine.hpp"
#include <string>

/*
	TODO:
	Make drawing GUI_Object's children a task for the default GUI_Object Render function, and call it AFTER
		drawing the inherited object render.
	Make more GUI_Object types,
		Text boxes
		Buttons
		Scrolling panels
		Input textboxes
*/

//GUI SYSTEM CLASS MEMBER FUNCTIONS:

//Creates the GUI Subsystem.
GUI_System::GUI_System(	Engine * parent_engine) 
						: 	Engine_System(parent_engine),
							m_gui_texture("gui.png", parent_engine->m_graphics)

{
	GUI_Window* Test = new GUI_Window(Recti({49, 49}).move(Point2({30, 20})), this);
	GUI_Window_Title* test_win = new GUI_Window_Title(Test, "Testing", 6, this);
	test_win->set_on_click(close_GUI_Object_base, nullptr);
}

//Destroys the GUI Subsystem
GUI_System::~GUI_System()
{
	//Destroys all GUI_Objects
	//And since this calls their destructors, destroys every child of every GUI Object
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		delete this->m_object_list[i];
	}
}

//Standard Update Function, called every frame.
void GUI_System::update()
{}

//Render function, called first on the render sequence.
void GUI_System::render()
{
	for(int i = 0; i < m_object_list.size(); i++)
	{
		m_object_list[i]->render();
	}
}

//-----------------------------------------------

//GUI OBJECT CLASS MEMBER FUNCTIONS:

//Creates a GUI Object,
//In this case, creates a BASE GUI Object, that is, this is inserted in the GUI_System object List,
//This Object's Render and Update function are called one every frame, first update(), then render(),
//Then this objects Children Render and Update are called, and then it's children render and update, and so
//on and so forth.
GUI_Object::GUI_Object(	const Point2& position, GUI_System* parent_system)
{
	m_is_child = false;

	m_parent_system = parent_system;
	m_graphics_system = &m_parent_system->m_parent_engine->m_graphics;

	m_parent_system->m_object_list.push_back(this);
	m_object_id = m_parent_system->m_object_list.size() - 1;

	m_local_position = position;
}

//Creates a GUI Object,
//In this case, a CHILD GUI Object, this is NOT inserted in the GUI_System object list, rather it is inserted
//In its parents elements list. Its render and update will be called after its parents.
GUI_Object::GUI_Object(	GUI_Object* parent_object, const Point2& local_position, GUI_System* parent_system)
{
	m_is_child = true;
	
	m_parent_system = parent_system;
	m_graphics_system = &m_parent_system->m_parent_engine->m_graphics;

	parent_object->add_child(this);

	m_local_position = local_position;
}

//Destroys GUI Object.
GUI_Object::~GUI_Object()
{
	if(m_is_child)
	{
		m_parent_object->remove_child(this);
	}
	else
	{
		m_parent_system->remove_base_object(this);
	}

	//Kills all children.
	for(int i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}
}

//Travels the GUI_Object Parent-Child tree until it finds a base, then returns it.
GUI_Object* GUI_Object::get_base()
{
	GUI_Object* current_object = this;
	
	while(current_object->m_is_child)
	{
		current_object = current_object->m_parent_object;
	}

	return current_object;
}

//Returns global position for a local position in relation to this Objects PARENTS global position.
//
//						l local pos
//						|
//						|
//	parents pos	p-------|
//				|
// 	origin	o---|       
//
//	The above would return like (12, -6) with origin being (0, 0), ana as such, would be off the top of the screen.
// 	REMEMBER SCREEN COORDINATES ARE (0,0) on -!-TOP LEFT-!-
Point2 GUI_Object::get_global_position(const Point2& local_position)
{
	Point2 current_position(0, 0);
	
	GUI_Object* current_object = this;

	current_position += local_position;
	
	while(current_object->m_is_child)
	{
		current_object = current_object->m_parent_object;
		current_position += current_object->m_local_position;
		
	}

	return current_position;
}

//Get the global position of this object. basically calls the above with this objects local position in
//relation to its parents, as such gets its global position.
Point2 GUI_Object::get_global_position()
{

	return get_global_position(m_local_position);
}

//Sets up a custom on_click function that will be called with the second argument being a void * to userdata
//Basically will call on_click_custom(this, userdata);
inline void GUI_Object::set_on_click(	int (*on_click_custom)(GUI_Object* target_object, void* userdata), 
										void * userdata)
{
	m_on_click_custom = on_click_custom;
	m_on_click_custom_userdata = userdata;
}
	
//Called once every frame, should be reserved for drawing
void GUI_Object::render()
{
	//Calls the custom render function for this  object
	if(m_render_custom != nullptr) m_render_custom(this, m_render_custom_userdata);

	//Draws GUI Object children.
	for(int i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->render();
	}
}

//Called once every frame
void GUI_Object::update()
{
	//Calls the custom update function for this object
	if(m_update_custom != nullptr) m_update_custom(this, m_update_custom_userdata);
}

//Called every frame theres a mouse over this object.
void GUI_Object::on_hover()
{
	//Calls the custom on_hover function for this object.
	if(m_on_hover_custom != nullptr) m_on_hover_custom(this, m_on_hover_custom_userdata);
}

//Called when theres a mouse click on this object.
void GUI_Object::on_click()
{
	//Callse the custom on_click function for this object.
	if(m_on_click_custom != nullptr) m_on_click_custom(this, m_on_click_custom_userdata);
}

//------------------------------------------

