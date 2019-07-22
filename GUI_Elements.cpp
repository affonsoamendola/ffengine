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

//GUI_WINDOW CLASS MEMBER FUNCTIONS:
//Creates a new Window. At rect local_rect
GUI_Window::GUI_Window(const Recti& local_rect, GUI_System* parent_system)
						: 	GUI_Object(local_rect.p0(), parent_system),
							m_size(local_rect.size())
{}

//Gets this window's rect.
Recti GUI_Window::get_rect()
{

	return Recti(m_local_position, m_local_position + m_size); 
}

//Draws this window.
void GUI_Window::render()
{
	m_graphics_system->draw_9_seg_square(get_rect(), Point2(8, 8), &m_parent_system->m_gui_texture);

	//Calls base render after rendered child stuff
	GUI_Object::render();
}
//-------------------------

//GUI_WINDOW_TITLE CLASS MEMBER FUNCTIONS:
//Creates a new Window_Title Object.
GUI_Window_Title::GUI_Window_Title(GUI_Window* parent_window, std::string text, int length, GUI_System* parent_system)
						:	GUI_Object(parent_window, Point2(0,0), parent_system),
							m_text(text),
							m_length(length)
{
	Recti parent_rect = parent_window->get_rect();

	int window_center = parent_rect.width()/2;

	m_local_text_location  = Point2(window_center - text.length()*4/2, 0);

	m_local_position = Point2(window_center - length*4/2, 0);
}

//Draws this object.
void GUI_Window_Title::render()
{
	m_graphics_system->blit_texture(	&m_parent_system->m_gui_texture, 
											Recti({4, 8}).move({24, 0}), 
											get_global_position() + Point2(-1*4, 0) );

	m_graphics_system->blit_texture(	&m_parent_system->m_gui_texture, 
											Recti({4, 8}).move({32, 0}), 
											get_global_position() + Point2(m_length*4, 0) );

	for(int i = 0; i < m_length; i++)
	{
		m_graphics_system->blit_texture(	&m_parent_system->m_gui_texture, 
												Recti({4, 8}).move({28, 0}), 
												get_global_position() + Point2(i, 0) * 4);
	}


	Point2 global_text_location = get_global_position(m_local_text_location);
	m_graphics_system->draw_text(	global_text_location[0], global_text_location[1], 
									m_text, Color(255, 255, 255, 255), m_graphics_system->m_font_ss->get_font(1));
}

//-------------------------

//Useful GUI_Objects custom functions
int close_GUI_Object_base(GUI_Object * parent_object, void * userdata)
{
	delete parent_object->get_base();
}

