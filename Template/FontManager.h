#pragma once
#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

// Core Libraries
#include <iostream>
#include <string>
#include <unordered_map>

// SDL Libraries
#include<SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Config.h"

class FontManager
{
public:
	static FontManager& Instance()
	{
		static FontManager instance;
		return instance;
	}

	bool load(const std::string& file_name, const std::string& id, int size, int style = TTF_STYLE_NORMAL);
	bool textToTexture(const std::string& text, const std::string& font_id, const std::string& texture_id, SDL_Color colour = { 0, 0, 0, 255 });
	TTF_Font* getFont(const std::string& id);
	void clean();

	void displayFontMap();

private:
	FontManager() = default;
	~FontManager() = default;

	bool m_exists(const std::string& id);

	std::unordered_map<std::string, TTF_Font*> m_fontMap;
};


#endif /* defined(__FONT_MANAGER__) */
