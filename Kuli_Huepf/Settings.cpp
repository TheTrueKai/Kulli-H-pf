#include "Settings.h"

const unsigned int Settings::WIDTH = sf::VideoMode::getDesktopMode().width;
const unsigned int Settings::HEIGHT = sf::VideoMode::getDesktopMode().height;
const unsigned int Settings::FPS = 30;
const unsigned int Settings::PEN_AMOUNT = 7;
const unsigned int Settings::PEN_WIDTH = (unsigned int)(Settings::WIDTH / 17);
const unsigned int Settings::PEN_HEIGHT = (unsigned int)(Settings::HEIGHT / 1.5);

const std::string Settings::TITLE = "Kuli Huepf";
const std::string Settings::BG_TEXTURE = "textures/table2.jpg";
const std::string Settings::FONT = "fonts/SFPixelate.ttf";
const std::string Settings::RULES = "textures/Rules_Dark.png";
const std::string Settings::RELOAD_TEXTURE = "textures/refresh.png";
const std::string Settings::LOGO = "textures/Logo.png";
const std::string Settings::RULES_BUTTON = "textures/RulesButton.png";
const std::string Settings::RETURN_BUTTON = "textures/returnButton.png";
const std::string Settings::EXIT_BUTTON = "textures/Exit.png";