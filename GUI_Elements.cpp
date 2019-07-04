#include "GUI.hpp"
#include "GUI_Elements.hpp"

#include "Rect.hpp"
#include "Engine.hpp"

#include <string>

void GUI_Window::render()
{
	draw_9_seg_square(Recti(2, 3, 44, 44), Point2(8, 8), &this->m_parent_system->m_gui_texture, &this->m_parent_system->m_parent_engine->m_graphics);

	for(int i = 0; i < this->m_elements.size(); i++)
	{
		m_elements[i]->render();
	}
}

void GUI_Window_Title::render()
{
}

GUI_Window::GUI_Window(const Recti& local_rect, const Point2& position, GUI_System* parent_system)
						: 	GUI_Object(position, parent_system),
							m_rect(local_rect)
{}


