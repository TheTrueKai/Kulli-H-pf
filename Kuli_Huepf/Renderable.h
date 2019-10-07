#pragma once
#include <SFML\Graphics.hpp>

class Renderable : public sf::Drawable
{
public:
	explicit Renderable()
	{
		active = true;
	}

	virtual void update(float deltaT) = 0;
	virtual void handleEvents(sf::Event sfEvent) = 0;
	virtual void render() const = 0;

public:
	bool isActive() const
	{
		return active;
	}
	void activate() { active = true; }
	void deactivate() { active = false; }

private:
	bool active;
};