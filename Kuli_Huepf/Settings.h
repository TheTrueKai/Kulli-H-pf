#pragma once
#define exco extern constexpr
#include <SFML\Graphics.hpp>
#include <string>


//namespace Settings
//{
//
//	exco unsigned int FPS = 30;
//	exco unsigned int WIDTH = 2800;
//	exco unsigned int HEIGHT = 1800;
//	exco char* TITLE = "Kuli Huepf";
//	exco unsigned int MAP_WIDTH = 24;
//	exco unsigned int MAP_HEIGHT = 24;
//	exco unsigned int PEN_AMOUNT = 7;
//	exco unsigned int PEN_WIDTH = (unsigned int)(WIDTH / 17);
//	exco unsigned int PEN_HEIGHT = (unsigned int)(HEIGHT / 1.5);
//	exco char* BG_TEXTURE = "textures/table2.jpg";
//	exco char* FONT = "fonts/SFPixelate.ttf";
//	exco char* RULES = "textures/Rules_Dark.png";
//}

class Settings
{
public:
	static const unsigned int WIDTH;
	static const unsigned int HEIGHT;
	static const unsigned int FPS;
	static const unsigned int PEN_AMOUNT;
	static const unsigned int PEN_WIDTH;
	static const unsigned int PEN_HEIGHT;

	static const std::string TITLE;
	static const std::string BG_TEXTURE;
	static const std::string FONT;
	static const std::string RULES;
	static const std::string RELOAD_TEXTURE;
	static const std::string LOGO;
	static const std::string RULES_BUTTON;
	static const std::string RETURN_BUTTON;
	static const std::string EXIT_BUTTON;
};

