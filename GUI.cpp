#include "GUI.hpp"

#include "Rect.hpp"
#include "Engine.hpp"

GUI_Object::GUI_Object(	const Point2& position, GUI_System* parent_system)
{
	this->m_is_base = true;

	this->m_parent_system = parent_system;

	this->m_parent_system->m_object_list.push_back(this);

	this->m_global_position = position;
}

GUI_Object::GUI_Object(	GUI_Object* parent_object, const Point2& local_position, GUI_System* parent_system)
{
	this->m_is_base = false;
	
	this->m_parent_object = parent_object;
	this->m_parent_object->m_elements.push_back(this);

	this->m_parent_system = parent_system;

	this->m_local_position = local_position;
	this->m_global_position = this->m_parent_object->m_global_position + local_position;
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

GUI_Window::GUI_Window(const Recti& local_rect, const Point2& position, GUI_System* parent_system)
						: 	GUI_Object(position, parent_system),
							m_rect(local_rect)
{}

Recti square_top_left = 	Recti(0, 0, 1, 1);
Recti square_top =			Recti(0, 0, 1, 1).move(Point2(1, 0));
Recti square_top_right = 	Recti(0, 0, 1, 1).move(Point2(2, 0));
Recti square_left = 		Recti(0, 0, 1, 1).move(Point2(0, 1));
Recti square_center =		Recti(0, 0, 1, 1).move(Point2(1, 1));
Recti square_right = 		Recti(0, 0, 1, 1).move(Point2(2, 1));
Recti square_bot_left =		Recti(0, 0, 1, 1).move(Point2(0, 2));
Recti square_bot = 			Recti(0, 0, 1, 1).move(Point2(1, 2));
Recti square_bot_right = 	Recti(0, 0, 1, 1).move(Point2(2, 2));

void draw_9_seg_square(	const Recti& window_rect, const Point2& seg_size, 
						const Texture* window_texture_holder,
						Graphics_System* graphics_system)
{
	int window_width = window_rect.width() / seg_size[0];
	int window_height = window_rect.height() / seg_size[1];

	Recti current_square;
	Point2 current_position;

	for(int w = 0; w < window_width; w++)
	{
		for(int h = 0; h < window_height; h++)
		{
			if 	   (w == 0 && h == 0) 			   					current_square = square_top_left;
			else if(w == 0 && h == window_height-1) 				current_square = square_bot_left;
			else if(w == window_width-1 && h == 0) 			 		current_square = square_top_right;
			else if(w == window_width-1 && h == window_height-1) 	current_square = square_bot_right;
			else if(w == 0) 										current_square = square_left;
			else if(w == window_width-1) 							current_square = square_right;
			else if(h == 0) 										current_square = square_top;
			else if(h == window_height-1) 							current_square = square_bot;
			else 													current_square = square_center;
			
			if(w == window_width-1 && h == window_height-1)		current_position = window_rect.p1() - seg_size;
			else if(w == window_width-1)						current_position = Point2(window_rect.p1()[0] - seg_size[0], window_rect.p0()[1] + h*seg_size[1]);
			else if(h == window_height-1)						current_position = Point2(window_rect.p0()[0] + w*seg_size[0], window_rect.p1()[1] - seg_size[1]);
			else 												current_position = window_rect.p0() + Point2(w*seg_size[0], h*seg_size[1]);
			
			graphics_system->blit_texture(	window_texture_holder,
											current_square * seg_size,
											current_position);

			if(w == window_width-1 && h == window_height-1)
			{
				current_position = window_rect.p0() + Point2(w*seg_size[0], h*seg_size[1]);
				current_square = Recti(square_center.p0() * seg_size, square_center.p0() * seg_size + Point2(window_rect.width() % seg_size[0], window_rect.height() % seg_size[1])  );
				
				graphics_system->blit_texture(	window_texture_holder,
												current_square,
												current_position);

				current_position = window_rect.p0() + Point2(window_rect.width() - seg_size[0], h*seg_size[1]);
				current_square = Recti(square_right.p0() * seg_size, square_right.p0() * seg_size + Point2(seg_size[0], window_rect.height() % seg_size[1])  );
				
				graphics_system->blit_texture(	window_texture_holder,
								current_square,
								current_position);

				current_position = window_rect.p0() + Point2(w*seg_size[0], window_rect.height() - seg_size[1]);
				current_square = Recti(square_bot.p0() * seg_size, square_bot.p0() * seg_size + Point2(window_rect.width() % seg_size[0], seg_size[1])  );
				
				graphics_system->blit_texture(	window_texture_holder,
								current_square,
								current_position);
			}
			else if(w == window_width-1)
			{
				current_position = window_rect.p0() + Point2(w*seg_size[0], h*seg_size[1]);
				
				if(h == 0)
					current_square = Recti(square_top.p0() * seg_size, square_top.p0() * seg_size + Point2(window_rect.width() % seg_size[0], seg_size[1])  );
				else
					current_square = Recti(square_center.p0() * seg_size, square_center.p0() * seg_size + Point2(window_rect.width() % seg_size[0], seg_size[1])  );
			
				graphics_system->blit_texture(	window_texture_holder,
												current_square,
												current_position);
			}		
			else if(h == window_height-1)
			{
				current_position = window_rect.p0() + Point2(w*seg_size[0], h*seg_size[1]);
				
				if(w == 0)
					current_square = Recti(square_left.p0() * seg_size, square_left.p0() * seg_size + Point2(seg_size[0], window_rect.height() % seg_size[1])  );
				else
					current_square = Recti(square_center.p0() * seg_size, square_center.p0() * seg_size + Point2(seg_size[0], window_rect.height() % seg_size[1])  );

				graphics_system->blit_texture(	window_texture_holder,
												current_square,
												current_position);
			}		
		}
	}
}

void GUI_Window::render()
{
	draw_9_seg_square(Recti(2, 3, 44, 44), Point2(8, 8), &this->m_parent_system->m_gui_texture, &this->m_parent_system->m_parent_engine->m_graphics);
}

GUI_System::GUI_System(	Engine * parent_engine) 
						: 	Engine_System(parent_engine),
							m_gui_texture("gui.png", parent_engine->m_graphics)

{
	new GUI_Window(Recti({32, 32}), Point2({20, 0}), this);
}

GUI_System::~GUI_System()
{
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		delete this->m_object_list[i];
	}
}

void GUI_System::update()
{}

void GUI_System::render()
{
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		this->m_object_list[i]->render();
	}
}