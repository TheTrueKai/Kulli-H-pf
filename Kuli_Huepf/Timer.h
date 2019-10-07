#pragma once
#include "Renderable.h"

class Timer : public Renderable
{
public:
	Timer();
	~Timer();

	// Geerbt über Renderable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void update(float deltaT) override;
	virtual void handleEvents(sf::Event sfEvent) override;
	virtual void render() const override;


public:
	void setFont(sf::Font* font);

	void setPosition(const sf::Vector2f& pos);
	const sf::Vector2f& getPosition() const;

	void setColor(const sf::Color& color);
	void setSize(float size);

	void start();
	void stop();
	void reset();

private:
	sf::Text* pText;
	sf::Clock timer;
	bool stopped;
};

