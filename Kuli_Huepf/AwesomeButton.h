#pragma once
#include "Renderable.h"

class AwesomeButton : public sf::Drawable
{
public:
	AwesomeButton();
	~AwesomeButton();

	// Geerbt über Renderable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update(float mouseX, float mouseY);

	bool isClicked() const;

	void setNormalColor(const sf::Color& color);
	void setHighlightColor(const sf::Color& color);

	void enableHighlight(bool state);

public:
	sf::RectangleShape shape;

private:
	sf::Color normalColor;
	sf::Color highlightColor;
	bool clicked;
	bool highlightEnabled;
};

