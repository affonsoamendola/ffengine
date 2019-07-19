/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include <string>

#include "Graphics_Text.hpp"
#include "Graphics.hpp"

Font::Font(	std::string file_location, Recti char_size, Font_Subsystem* parent_system)
			:	m_parent_font_system(parent_system),
				m_font_location(file_location),
				m_char_size(char_size)
{
	m_texture = new Texture(m_font_location, *m_parent_font_system->m_parent_system);
}

Font::~Font()
{
	delete m_texture;
}

Font_Subsystem::Font_Subsystem(Graphics_System* parent_system)
				:m_parent_system(parent_system)
{
	load_font()
}

Font_Subsystem::~Font_Subsystem()
{
	for(int i = 0; i < m_font_textures.size(); i ++)
	{
		unload_font(i);
	}
}	

void Font_Subsystem::load_font(unsigned int font_id, std::string file_location, Recti character_size)
{
	m_font_textures[font_id] = new Font(file_location, character_size, this);
}

void Font_Subsystem::unload_font(unsigned int font_id)
{
	delete m_font_textures[font_id];
	m_font_textures.erase(font_id);
}