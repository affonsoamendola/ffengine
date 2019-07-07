#include "GUI.hpp"
#include "GUI_Elements.hpp"

#include "Rect.hpp"
#include "Engine.hpp"

#include <string>

void GUI_Window::render()
{
	draw_9_seg_square(Recti(2, 3, 44, 44), Point2(8, 8), &this->m_parent_system->m_gui_texture, this->m_graphics_system);

	for(int i = 0; i < this->m_elements.size(); i++)
	{
		m_elements[i]->render();
	}
}

void GUI_Window_Title::render()
{
	this->m_graphics_system->draw_tiny_text(this->m_text_location[0], this->m_text_location[1], this->m_text, Color(255, 255, 255, 255));
}

GUI_Window::GUI_Window(const Recti& local_rect, const Point2& position, GUI_System* parent_system)
						: 	GUI_Object(position, parent_system),
							m_rect(local_rect)
{
}

GUI_Window_Title::GUI_Window_Title(GUI_Window* parent_window, std::string text, int length, GUI_System* parent_system)
						:	GUI_Object(parent_window, Point2(0,0), parent_system),
							m_text(text),
							m_length(length)
{
	Recti parent_rect = parent_window->m_rect;

	int window_center = parent_rect.width()/2;

	this->m_text_location  = Point2(window_center - text.length()/2, 0);

	this->m_local_position = Point2(window_center - length/2, 0);
}


