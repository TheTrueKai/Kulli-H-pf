#pragma once
#include "Renderable.h"
#include "AwesomeButton.h"

class RulesPage : public Renderable
{
public:
	RulesPage();
	~RulesPage();

	// Geerbt über QPage
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void update(float deltaT) override;
	virtual void handleEvents(sf::Event sfEvent) override;
	virtual void render() const override;

	void setMousePosition(const sf::Vector2i & mousePos)
	{
		mousePosition = mousePos;
	}

	bool isReturnButtonPressed() const;

private:
	void initializeReturnButton();

private:
	sf::Texture* pReturnButtonTexture;
	sf::Texture* pRulesTexture;
	sf::RectangleShape rules;
	AwesomeButton returnButton;
	sf::Vector2i mousePosition;
};

