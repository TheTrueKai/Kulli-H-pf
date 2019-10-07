#include "Engine.h"
#include <Windows.h>
#include <iostream>




Engine::Engine()
{
	pWindow = nullptr;
	pField = nullptr;
	pRules = nullptr;
	button_timer = 0.0f;
}


Engine::~Engine()
{
	delete pWindow;
	pWindow = nullptr;
	delete pField;
	pField = nullptr;
	delete pRules;
	pRules = nullptr;
}

void Engine::hideConsole(bool state)
{
	HWND console = GetConsoleWindow();
	if (state)
		ShowWindow(console, SW_HIDE);
	else
		ShowWindow(console, SW_SHOW);
}

void Engine::initialize()
{
	pWindow = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], Settings::TITLE, sf::Style::Close |sf::Style::Fullscreen);
	pWindow->setVerticalSyncEnabled(true);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	pField = new Field();
	pRules = new RulesPage();
}

void Engine::run()
{
	if (pWindow == nullptr)
	{
		initialize();
	}

	sf::Event eEvent;
	sf::Clock cClock;

	while (pWindow->isOpen())
	{
		while (pWindow->pollEvent(eEvent))
		{
			handleEvents(eEvent);
		}

		update(cClock.restart().asSeconds());

		pWindow->clear(sf::Color(78,78,78));
		render();
		pWindow->display();

	}
	pWindow->close();
}

void Engine::update(float deltaT)
{
	pField->setMousePosition(sf::Mouse::getPosition(*pWindow));
	pRules->setMousePosition(sf::Mouse::getPosition(*pWindow));

	button_timer += deltaT;

	if (pField->isActive())
	{
		pField->update(deltaT);

		if (pField->isExitButtonPressed())
		{
			pWindow->close();
			return;
		}

		if (pField->isRulesButtonPressed() && button_timer > 0.2f)
		{
			button_timer = 0.0f;
			pRules->activate();
			pField->deactivate();
			pField->reset();
		}
	}
	else if(pRules->isActive())
	{
		pRules->update(deltaT);

		if (pRules->isReturnButtonPressed() && button_timer > 0.2f)
		{
			pField->activate();
			pRules->deactivate();
			button_timer = 0.0f;
		}
	}
}

void Engine::render() const
{
	if (pField->isActive())
	{
		pWindow->draw(*pField);
	}
	else if(pRules->isActive())
	{
		pWindow->draw(*pRules);
	}
}

void Engine::handleEvents(sf::Event eEvent)
{
	if (eEvent.type == sf::Event::Closed)
	{
		pWindow->close();
		return;
	}

	if (eEvent.type == sf::Event::KeyPressed)
	{
		if (eEvent.key.code == sf::Keyboard::Escape)
		{
			pWindow->close();
			return;
		}

		if (eEvent.key.code == sf::Keyboard::Q)
		{
			if (pField->isActive())
			{
				pRules->activate();
				pField->deactivate();
				pField->reset();
			}
			else
			{
				pRules->deactivate();
				pField->activate();
			}
		}
	}

	pField->handleEvents(eEvent);
}