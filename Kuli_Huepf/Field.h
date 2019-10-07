#pragma once
#include "PenObject.h"
#include "Timer.h"
#include "AwesomeButton.h"
#include "Settings.h"
#include <vector>

class Field : public Renderable
{
public:
	Field();
	virtual ~Field();

	// Geerbt über Renderable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void update(float deltaT) override;
	virtual void handleEvents(sf::Event sfEvent) override;
	virtual void render() const override;

	void setMousePosition(const sf::Vector2i & mousePos)
	{
		mousePosition = mousePos;
	}

	void reset();
	bool isRulesButtonPressed() const;
	bool isExitButtonPressed() const;

private:
	void resetPens();
	int getPenFieldFromPosition();
	void generatePenField();
	void movePen();
	sf::Vector2f getPositionFromIndex(int index) const;
	bool isFinished();

	void initializeTimer();
	void initializeReloadButton();
	void initializeRulesButton();
	void initializeExitButton();

	void handleReloadButton();

private:
	sf::Texture* pPenTextureA;
	sf::Texture* pPenTextureB;
	sf::Texture* pReloadTexture;
	sf::Texture* pRulesButtonTexture;
	sf::Texture* pExitTexture;
	sf::Font* pFont;
	AwesomeButton reloadButton;
	AwesomeButton rulesButton;
	AwesomeButton exitButton;

	std::vector<PenObject> penObjects;
	std::vector<sf::RectangleShape> penFields;
	int activePenIndex;

	sf::Vector2i mousePosition;
	sf::Vector2i mousePosition_old;

	Timer timer;
	bool firstMove;
};

