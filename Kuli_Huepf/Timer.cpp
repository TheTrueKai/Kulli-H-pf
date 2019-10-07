#include "Timer.h"
#include <string>


Timer::Timer()
{
	pText = new sf::Text();
	pText->setString("Time: 00:00s");
	stopped = true;
}


Timer::~Timer()
{
	delete pText;
	pText = nullptr;
}

void Timer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*pText);
}

void Timer::update(float deltaT)
{
	if (stopped)
	{
		return;
	}

	float time = timer.getElapsedTime().asSeconds();
	std::string time_str;
	if (time < 10)
	{
		time_str = "Time: 0" + std::to_string((int)time);
	}
	else
	{
		time_str = "Time: " + std::to_string((int)time);
	}
	time_str += ":";
	time_str += std::to_string((int)((time - (int)time) * 100));
	time_str += "s";

	pText->setString(time_str);
}

void Timer::handleEvents(sf::Event sfEvent)
{
}

void Timer::render() const
{
}

void Timer::setFont(sf::Font * font)
{
	pText->setFont(*font);
}

void Timer::setPosition(const sf::Vector2f & pos)
{
	pText->setPosition(pos);
}

const sf::Vector2f & Timer::getPosition() const
{
	return pText->getPosition();
}

void Timer::setColor(const sf::Color & color)
{
	pText->setFillColor(color);
}

void Timer::setSize(float size)
{
	pText->setCharacterSize(size);
}

void Timer::start()
{
	stopped = false;
	timer.restart();
}

void Timer::stop()
{
	stopped = true;
}

void Timer::reset()
{
	timer.restart();
	pText->setString("Time: 00:00s");
}
