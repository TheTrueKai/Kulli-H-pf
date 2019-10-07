#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Field.h"
#include "RulesPage.h"

class Engine
{
public:
	Engine();
	~Engine();

public:
	void hideConsole(bool state);
	void initialize();
	void run();

private:
	void update(float deltaT);
	void render() const;
	void handleEvents(sf::Event eEvent);


private:
	sf::RenderWindow* pWindow;
	Field* pField;
	RulesPage* pRules;
	unsigned int nWidth;
	unsigned int nHeight;
	float button_timer;
};

