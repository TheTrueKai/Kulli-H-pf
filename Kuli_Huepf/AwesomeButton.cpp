#include "AwesomeButton.h"



AwesomeButton::AwesomeButton()
{
	highlightEnabled = false;
	clicked = false;
}


AwesomeButton::~AwesomeButton()
{
}

void AwesomeButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

void AwesomeButton::update(float mouseX, float mouseY)
{
	const bool mouseOver = shape.getGlobalBounds().contains(mouseX, mouseY);
	if (highlightEnabled)
	{
		if (mouseOver)
		{
			shape.setFillColor(highlightColor);
		}
		else
		{
			shape.setFillColor(normalColor);
		}
	}

	clicked = (mouseOver && (sf::Mouse::isButtonPressed(sf::Mouse::Left)));
}

bool AwesomeButton::isClicked() const
{
	return clicked;
}

void AwesomeButton::setNormalColor(const sf::Color & color)
{
	normalColor = color;
}

void AwesomeButton::setHighlightColor(const sf::Color & color)
{
	highlightColor = color;
}

void AwesomeButton::enableHighlight(bool state)
{
	highlightEnabled = state;
}
