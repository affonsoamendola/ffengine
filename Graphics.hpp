#pragma once
/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

//TOOD:
//Make a proper cursor texture.
//Make a better texture holder system.

#include <string>
#include <memory>
#include <vector>

#include "Rect.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"

#include "Engine_System.hpp"

class Engine;

//Definition of what a Color object is,
//a bunch of uint8s, defaults to opaque black.
class Color
{
public:
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	Color(unsigned char t_r = 0, unsigned char t_g = 0, unsigned char t_b = 0) : r(t_r), g(t_g), b(t_b) {}
	Color(unsigned char t_r, unsigned char t_g, unsigned char t_b, unsigned char t_a) : r(t_r), g(t_g), b(t_b), a(t_a) {}
};

//Forward dec, Graphics_System needs to know what a Texture is.
class Texture;

//Declaration of Graphics Engine Subsystem.
class Graphics_System : public Engine_System
{
private:
	std::vector<char> m_default_font; //Default binary font location in memory
	std::vector<unsigned char> m_screen_pixels; //APPARENTLY stored in BGRA, take that into account always
public:
	std::vector<Texture*> m_texture_holder; //List of all loaded textures.

	Texture * m_tiny_text_font;

	const unsigned int m_screen_width = 320;
	const unsigned int m_screen_height = 200;

	const unsigned int m_pixel_scale = 4; 	//When rendering, will draw a square of m_pixel_scale by m_pixel_scale instead of 1x1 pixels
											//Basically zooms in on pixel art and is pixel perfect, side effect, 320x200 game will be on a MUCH bigger screen.	

	const unsigned int m_screen_surface_width = m_screen_width * m_pixel_scale;
	const unsigned int m_screen_surface_height = m_screen_height * m_pixel_scale;

	double m_fps = 0.;
	double m_frame_time = 0.;

	bool m_show_mouse = true;
	bool m_show_fps = true;
	bool m_show_frame_time = true;

	SDL_Window* m_window; //SDL window of the game.
	SDL_Renderer* m_renderer; //SDL renderer of the game.

	SDL_Texture* m_screen_surface;	//Texture holding the FINAL screen surface. (Dont mess with this.)

	Graphics_System(Engine * engine);
	~Graphics_System();

	void update();
	void render();

	void set_pixel(unsigned int x, unsigned int y, Color color);
	void get_pixel(unsigned int x, unsigned int y);

	void clear_screen();
	void clear_screen(Color color);

	void load_texture(std::string image_location);

	void load_default_font(std::string font_location);
	void load_tiny_font(std::string font_location);

	void draw_cursor();

	void draw_binary_image(unsigned int x, unsigned int y, unsigned int size_x, unsigned int size_y, std::vector<char> image_location, Color color);
	void draw_wave(	unsigned char * wave, const Point2& screen_location, int channel, 
					unsigned int start_point, unsigned int height, unsigned int length, Color color);
	void draw_char(unsigned int x, unsigned int y, char character, Color color);
	void draw_tiny_char(unsigned int x, unsigned int y, char character, Color color);

	void draw_text(unsigned int x, unsigned int y, std::string char_string, Color color);
	void draw_text(unsigned int x, unsigned int y, int value, Color color);
	void draw_text(unsigned int x, unsigned int y, double value, Color color);

	void draw_tiny_text(unsigned int x, unsigned int y, std::string char_string, Color color);
	void draw_tiny_text(unsigned int x, unsigned int y, int value, Color color);
	void draw_tiny_text(unsigned int x, unsigned int y, double value, Color color);

	void draw_9_seg_square(	const Recti& window_rect, const Point2& seg_size, 
							const Texture* window_texture_holder);

	void blit_texture(const Texture* to_render, const Recti& src, const Point2& dst);
	void blit_texture(const Texture* to_render, const Point2& dst);
};

//Declaration of what is a texture
class Texture
{
private:

	Color m_color_mod = {255, 255, 255, 255}; //Color and alpha tint of the texture.
public:
	SDL_Surface* m_surface = nullptr; //Pixel surface of the Texture.
	SDL_Texture* m_texture = nullptr; //The actual texture.

	Recti m_rect = {{0, 0}, {0, 0}};
	
	inline void set_opacity(unsigned char opacity)
	{
		this->m_color_mod.a = opacity;
		SDL_SetTextureAlphaMod(this->m_texture, this->m_color_mod.a);
	}
	inline double get_opacity(){return this->m_color_mod.a;}

	inline void set_color_mod(Color color)
	{
		this->m_color_mod.r = color.r;
		this->m_color_mod.g = color.g;
		this->m_color_mod.b = color.b;
		SDL_SetTextureColorMod(this->m_texture, color.r, color.g, color.b);
	}
	inline Color get_color_mod(){return this->m_color_mod;}

	Texture get_sub_texture(Recti rect);

	Texture(std::string file_location, Graphics_System& g_system);
	~Texture();
};

//Dec of what is a sprite, need to mess around more with this, currently I dont think this is used.
struct Sprite
{
	Texture* m_texture_sheet;

	Color m_color_mod = {255, 255, 255, 255}; 

	Recti m_texture_sheet_rect;

	inline void set_color_mod(Color color)
	{
		this->m_color_mod.r = color.r;
		this->m_color_mod.g = color.g;
		this->m_color_mod.b = color.b;
	}
	inline Color get_color_mod(){return this->m_color_mod;}

	Sprite(Texture* m_texture_sheet, const Recti& m_texture_sheet_rect);
	~Sprite();
};

//Some default colors
const Color COLOR_RED = {255, 0, 0, 255};
const Color COLOR_GREEN = {0, 255, 0, 255};
const Color COLOR_BLUE = {0, 0, 255, 255};
const Color COLOR_BLACK = {0, 0, 0, 255};
const Color COLOR_WHITE = {255, 255, 255, 255};

//while I dont make a cursor texture, here is a cursor.
const std::vector<char> CURSOR 	     = 	{0,		 	 0,          0, 0b00011000, 0b00011000,          0,          0, 0};
const std::vector<char> CURSOR_HOVER = 	{0, 0b00100100, 0b01100110, 0b00011000, 0b00011000, 0b01100110, 0b00100100, 0};
const std::vector<char> CURSOR_CLICK = 	{0, 0b00100100, 0b01100110,          0,          0, 0b01100110, 0b00100100, 0};

//Definitions of the 9 segments of the rect for draw_9_seg
const Recti square_top_left = 	Recti(0, 0, 1, 1);
const Recti square_top =		Recti(0, 0, 1, 1).move(Point2(1, 0));
const Recti square_top_right = 	Recti(0, 0, 1, 1).move(Point2(2, 0));
const Recti square_left = 		Recti(0, 0, 1, 1).move(Point2(0, 1));
const Recti square_center =		Recti(0, 0, 1, 1).move(Point2(1, 1));
const Recti square_right = 		Recti(0, 0, 1, 1).move(Point2(2, 1));
const Recti square_bot_left =	Recti(0, 0, 1, 1).move(Point2(0, 2));
const Recti square_bot = 		Recti(0, 0, 1, 1).move(Point2(1, 2));
const Recti square_bot_right = 	Recti(0, 0, 1, 1).move(Point2(2, 2));

