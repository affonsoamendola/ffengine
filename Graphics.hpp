#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Rect.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"

#include "Engine_System.hpp"

class Engine;

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

class Texture;

class Graphics_System : public Engine_System
{
private:
	std::vector<char> m_default_font;
	std::vector<unsigned char> m_screen_pixels; //APPARENTLY stored in BGRA, take that into account allways

	void load_default_font(std::string font_location);

public:
	std::vector<Texture*> m_texture_holder;

	const unsigned int m_screen_width = 320;
	const unsigned int m_screen_height = 200;

	const unsigned int m_pixel_scale = 4;

	const unsigned int m_screen_surface_width = m_screen_width * m_pixel_scale;
	const unsigned int m_screen_surface_height = m_screen_height * m_pixel_scale;

	double m_fps = 0.;
	double m_frame_time = 0.;

	bool m_show_mouse = true;
	bool m_show_fps = true;
	bool m_show_frame_time = true;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	SDL_Texture* m_screen_surface;

	Graphics_System(Engine * engine);
	~Graphics_System();

	void update();
	void render();

	void set_pixel(unsigned int x, unsigned int y, Color color);
	void get_pixel(unsigned int x, unsigned int y);

	void clear_screen();
	void clear_screen(Color color);

	void load_texture(std::string image_location);

	void draw_cursor();

	void draw_binary_image(unsigned int x, unsigned int y, unsigned int size_x, unsigned int size_y, std::vector<char> image_location, Color color);
	void draw_char(unsigned int x, unsigned int y, char character, Color color);

	void draw_text(unsigned int x, unsigned int y, std::string char_string, Color color);
	void draw_text(unsigned int x, unsigned int y, int value, Color color);
	void draw_text(unsigned int x, unsigned int y, double value, Color color);

	void blit_texture(const Texture* to_render, const Recti& src, const Point2& dst);
	void blit_texture(const Texture* to_render, const Point2& dst);
};

class Texture
{
private:
	Color m_color_mod = {255, 255, 255, 255};
public:
	SDL_Surface* m_surface = nullptr;
	SDL_Texture* m_texture = nullptr;

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

	Texture(std::string file_location, Graphics_System& g_system);
	~Texture();
};

const Color COLOR_RED = {255, 0, 0, 255};
const Color COLOR_GREEN = {0, 255, 0, 255};
const Color COLOR_BLUE = {0, 0, 255, 255};
const Color COLOR_BLACK = {0, 0, 0, 255};
const Color COLOR_WHITE = {255, 255, 255, 255};

const std::vector<char> CURSOR 	     = 	{0,		 	 0,          0, 0b00011000, 0b00011000,          0,          0, 0};
const std::vector<char> CURSOR_HOVER = 	{0, 0b00100100, 0b01100110, 0b00011000, 0b00011000, 0b01100110, 0b00100100, 0};
const std::vector<char> CURSOR_CLICK = 	{0, 0b00100100, 0b01100110,          0,          0, 0b01100110, 0b00100100, 0};