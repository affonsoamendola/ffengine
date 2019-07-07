/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include "Graphics.hpp"
#include "Engine.hpp"
#include "Utility.hpp"
#include "Rect.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_image.h"

using namespace std;

//Creates a new Texture object from a file location.
Texture::Texture(string file_location, Graphics_System& g_system)
{
	//DEBUG.
	cout << "Loading texture at: " << file_location << "..." << std::flush;
	
	this->m_surface = IMG_Load(file_location.c_str());
	//Load texture
	if(this->m_surface == nullptr)
	{
		SDL_Log("\nFailure opening image file: %s", SDL_GetError());
		exit(1);
	}

	this->m_texture = SDL_CreateTextureFromSurface(g_system.m_renderer, this->m_surface);

	if(this->m_texture == nullptr)
	{
		SDL_Log("\nFailure creating texture: %s", SDL_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	this->m_rect = Recti({0, 0}, Point2(this->m_surface->w, this->m_surface->h));

	//Basic setups for SDL texture for color and alpha mods and blending
	if(SDL_SetTextureColorMod(this->m_texture, 255, 255, 255) == -1) 	SDL_Log("\nTexture Color Modulation Not Supported on this renderer");
	if(SDL_SetTextureAlphaMod(this->m_texture, 255) == -1) 				SDL_Log("\nTexture Alpha Modulation Not Supported on this renderer");
	SDL_SetTextureBlendMode(this->m_texture, SDL_BLENDMODE_BLEND);
}

//Destroy texture.
Texture::~Texture()
{
	//Frees the surface that was in heap.
	SDL_FreeSurface(this->m_surface);
}

//Creates and initializes a new Graphics Subsystem for the parent engine.
Graphics_System::Graphics_System(Engine * parent_engine) : Engine_System(parent_engine)
{
	this->m_screen_pixels.reserve(this->m_screen_width * this->m_screen_height * 4); //Reserves the screen array.
	this->m_default_font.reserve(768); //Reserves the binary font location.

	cout << "Initting SDL..." << std::flush;

	//Start SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("\nProblem initializing SDL: %s", SDL_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	cout << "Initting SDL_Image..." << std::flush;

	//Start SDL_Image
	int imgFlags = IMG_INIT_PNG;
 	if( !( IMG_Init(imgFlags) & imgFlags) )
 	{
		SDL_Log("\nProblem initializing SDL_Image: %s", IMG_GetError());
		exit(1);		
 	}

	cout << "Done." << std::endl;
	
	cout << "Creating Window..." << std::flush;

	//Creates window, wight size m_screen_surface width x height
	this->m_window = SDL_CreateWindow	(	"Fofonso's SDL Engine",
											SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
											this->m_screen_surface_width, this->m_screen_surface_height,
											SDL_WINDOW_SHOWN
										);

	if(m_window == NULL)
	{
		SDL_Log("\nProblem creating SDL Window: %s", SDL_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	//Creates renderer
	this->m_renderer = SDL_CreateRenderer	( 	this->m_window,
												-1,
												SDL_RENDERER_ACCELERATED
											);

	cout << "Creating SDL Renderer..." << std::flush;

	if(m_renderer == NULL)
	{
		SDL_Log("Problem creating SDL Renderer: %s", SDL_GetError());
		exit(1);
	}

	cout << "Done." << std::endl;

	SDL_RendererInfo info;
	SDL_GetRendererInfo(this->m_renderer, &info);

	cout << "Renderer Type: " << info.name << endl;

	//Creates screen texture.
	this->m_screen_surface = SDL_CreateTexture	(	this->m_renderer,
													SDL_PIXELFORMAT_ARGB8888,
													SDL_TEXTUREACCESS_STREAMING,
													this->m_screen_width, this->m_screen_height
												);
	SDL_SetTextureBlendMode(this->m_screen_surface, SDL_BLENDMODE_BLEND);

	//Loads the default binary font.
	this->load_default_font("8x8Font.fnt");

	//Loads the tiny text font.
	this->load_tiny_font("4x6Font.png");

	//Loads fallback texture, Dopefish Lives, Hail Carmack.
	this->load_texture("dopefish.png");

	SDL_ShowCursor(0);
}

Graphics_System::~Graphics_System()
{
	delete this->m_tiny_text_font;

	//Free all textures
	for(int i = 0; i < this->m_texture_holder.size(); i++)
	{
		delete this->m_texture_holder[i];
	}

	//Quit everything.
	SDL_DestroyRenderer(this->m_renderer);
	SDL_DestroyWindow(this->m_window);
	IMG_Quit();
	SDL_Quit();
}

void Graphics_System::load_default_font(string font_location)
{
	load_bin_file(font_location, &this->m_default_font);
}

void Graphics_System::load_tiny_font(string font_location)
{
	this->m_tiny_text_font = new Texture(font_location, *this);
}

//update before rendering
void Graphics_System::update(){};

//Main render function, this clears the screen and draws things to it.
void Graphics_System::render()
{
	//Calls GUI Subsystem Render Function, draws the GUI
	this->m_parent_engine->m_gui.render();

	//Draws the cursor
	if(this->m_show_mouse) this->draw_cursor();
	//Draws FPS Counter
	if(this->m_show_fps) 
		this->draw_text(this->m_screen_width - 40, 0, this->m_parent_engine->m_avg_fps, COLOR_RED);
	//Draws FrameTime Counter
	if(this->m_show_frame_time)
	{ 
		this->draw_text(this->m_screen_width - 40, 8, this->m_parent_engine->m_avg_frame_time * 1000, COLOR_RED);
		this->draw_text(this->m_screen_width - 40, 16, this->m_parent_engine->m_dropped_frames, COLOR_RED);
	}
	//Flushes screen surface data to screen texture.
	//m_screen_pixels -> m_screen_surface
    SDL_UpdateTexture	(	this->m_screen_surface,
    						NULL,
    						&(this->m_screen_pixels[0]),
    						this->m_screen_width * 4
    					);

    //Sends texture to renderer
    SDL_RenderCopy(this->m_renderer, this->m_screen_surface, NULL, NULL);

    //Shows on screen
    SDL_RenderPresent(this->m_renderer);


   	//Clears screen for next frame.
	SDL_SetRenderDrawColor(this->m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
	SDL_RenderClear(this->m_renderer);
	this->clear_screen();
}

void Graphics_System::set_pixel(unsigned int x, unsigned int y, Color color)
{
	//Sets a pixel on screen, does screen space clipping with this if.
	if(x < this->m_screen_width && y < this->m_screen_height && x >= 0 && y >= 0)
	{
		const unsigned int offset = ( this->m_screen_width * 4 * y) + x * 4;

		this->m_screen_pixels[ offset + 0 ] = color.b;    // b
	    this->m_screen_pixels[ offset + 1 ] = color.g;    // g
	    this->m_screen_pixels[ offset + 2 ] = color.r;    // r
	    this->m_screen_pixels[ offset + 3 ] = color.a;    // a
	}
}

void Graphics_System::clear_screen()
{
	//Clears screen_pixels
	fill(this->m_screen_pixels.begin(), this->m_screen_pixels.begin() + this->m_screen_width * this->m_screen_height * 4, 0);
}

void Graphics_System::clear_screen(Color color)
{
	//Sets a screen of a determined color (kind of slow)
	for(int x = 0; x < this->m_screen_width; x ++)
	{
		for(int y = 0; y < this->m_screen_height; y ++)
		{
			this->set_pixel(x, y, color);
		}
	}
}

void Graphics_System::load_texture(std::string image_location)
{
	//Loads a new texture on the Texture holder
	Texture* new_texture = new Texture(image_location, *this);

	this->m_texture_holder.push_back(new_texture);
}

void Graphics_System::draw_binary_image(unsigned int x, unsigned int y, 
										unsigned int size_x, unsigned int size_y, 
										std::vector<char> image_location, Color color)
{
	//Draws a binary image (Font mostly)
	for(int y_c = 0; y_c < size_y; y_c ++)
	{
		for(int x_c = 0; x_c < size_x; x_c ++)
		{
			if(image_location[y_c] & (0x80 >> x_c)) 
			{
				this->set_pixel(x + x_c, y + y_c, color);
			}
		}
	}
}

void Graphics_System::draw_cursor()
{
	const std::vector<char>* current_cursor;

	if(this->m_parent_engine->m_input.m_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
		current_cursor = &CURSOR_CLICK;
	else
		current_cursor = &CURSOR;

	draw_binary_image(	(this->m_parent_engine->m_input.m_mouse_x / this->m_pixel_scale) - 4, 
						(this->m_parent_engine->m_input.m_mouse_y / this->m_pixel_scale) - 4,
						8, 8,
						*current_cursor, COLOR_WHITE);
}

void Graphics_System::draw_char(unsigned int x, unsigned int y, char character, Color color)
{
	unsigned int offset = (unsigned int)((character-32) * 8);

	this->draw_binary_image(x, y, 8, 8, std::vector<char>(this->m_default_font.begin()+offset, this->m_default_font.begin()+offset+8), color);
}

void Graphics_System::draw_tiny_char(unsigned int x, unsigned int y, char character, Color color)
{
	unsigned int offset = (unsigned int)((character-32));

	unsigned int tex_x = offset % 32;
	unsigned int tex_y = offset / 32;

	Color original_mod = this->m_tiny_text_font->get_color_mod();

	this->m_tiny_text_font->set_color_mod(color);

	this->blit_texture(this->m_tiny_text_font, Recti({4, 6}).move(Point2(tex_x * 4, tex_y * 6)), Point2(x, y));

	this->m_tiny_text_font->set_color_mod(original_mod);
}

void Graphics_System::draw_text(unsigned int x, unsigned int y, string char_string, Color color)
{
	for(int i = 0; i < char_string.length(); i++)
	{
		this->draw_char(x + 8 * i, y, char_string[i], color);
	}
}

void Graphics_System::draw_text(unsigned int x, unsigned int y, int value, Color color)
{
	char buffer[32];

	sprintf(buffer, "%d", value);

	this->draw_text(x, y, string(buffer), color);
}

void Graphics_System::draw_text(unsigned int x, unsigned int y, double value, Color color)
{
	char buffer[32];

	sprintf(buffer, "%g", value);

	this->draw_text(x, y, string(buffer), color);
}

void Graphics_System::draw_tiny_text(unsigned int x, unsigned int y, std::string char_string, Color color)
{
	for(int i = 0; i < char_string.length(); i++)
	{
		this->draw_tiny_char(x + 4 * i, y, char_string[i], color);
	}
}

void Graphics_System::draw_tiny_text(unsigned int x, unsigned int y, int value, Color color)
{
	char buffer[32];

	sprintf(buffer, "%d", value);

	this->draw_tiny_text(x, y, string(buffer), color);
}

void Graphics_System::draw_tiny_text(unsigned int x, unsigned int y, double value, Color color)
{
	char buffer[32];

	sprintf(buffer, "%g", value);

	this->draw_tiny_text(x, y, string(buffer), color);
}

void Graphics_System::blit_texture(const Texture* to_render, const Recti& src, const Point2& dst)
{
	SDL_Rect src_sdl = src.to_SDL();

	Recti scaled = src.scale(this->m_pixel_scale);

	SDL_Rect dst_sdl;

	dst_sdl.x = dst[0] * this->m_pixel_scale;
	dst_sdl.y = dst[1] * this->m_pixel_scale;
	dst_sdl.w = scaled.width();
	dst_sdl.h = scaled.height();

	SDL_RenderCopy(this->m_renderer, to_render->m_texture, &src_sdl, &dst_sdl);
}

void Graphics_System::blit_texture(const Texture* to_render, const Point2& dst)
{
	this->blit_texture(to_render, to_render->m_rect, dst);
}

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
