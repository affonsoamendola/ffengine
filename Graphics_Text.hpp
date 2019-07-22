#pragma once
/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include <string>
#include <map>

#include "Color.hpp"
#include "Rect.hpp"

class Texture;
class Font;
class Graphics_System;

//Default size space is the space of a character.
const int TEXT_DEFAULT_SPACE_SIZE = -1;

enum ALIGNMENT
{
	LEFT,
	CENTRALIZED,
	RIGHT,
	JUSTIFIED
};

struct Font_Options
{
	unsigned int m_font_id = -1;
	Color m_color = {255, 255, 255, 255};

	Recti m_margin = {0, 0, 0, 0};

	int m_letter_spacing = 0;
	int m_line_spacing = 0;
	int m_space_size = TEXT_DEFAULT_SPACE_SIZE;

	ALIGNMENT m_alignment;
};

//Declaration of Font Graphics Subsystem.
class Font_Subsystem
{
public:
	Graphics_System* m_parent_system;
	std::map<unsigned int, Font*> m_font_textures;

	Font_Subsystem(Graphics_System* parent_system);
	~Font_Subsystem();

	Font* get_font(unsigned int font_id){ return m_font_textures[font_id];}

	void load_font(unsigned int font_id, std::string file_location, Recti character_size);
	void unload_font(unsigned int font_id);
};

//Defines what is a font, which is a collection of a texture and a size of character.
struct Font
{
	Font_Subsystem* m_parent_font_system;
	std::string m_font_location;
	Texture* m_texture;
	Recti m_char_size;

	Font(std::string file_location, Recti char_size, Font_Subsystem* parent_system);
	~Font();
};