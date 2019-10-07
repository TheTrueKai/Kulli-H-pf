#include "Field.h"



Field::Field()
{
	pPenTextureA = new sf::Texture();
	pPenTextureB = new sf::Texture();
	pReloadTexture = new sf::Texture();
	pRulesButtonTexture = new sf::Texture();
	pExitTexture = new sf::Texture();
	pFont = new sf::Font();

	pPenTextureA->loadFromFile(PenObject::PEN_TEXTURE_A);
	pPenTextureB->loadFromFile(PenObject::PEN_TEXTURE_B);
	pReloadTexture->loadFromFile(Settings::RELOAD_TEXTURE);
	pRulesButtonTexture->loadFromFile(Settings::RULES_BUTTON);
	pExitTexture->loadFromFile(Settings::EXIT_BUTTON);

	pPenTextureA->setSmooth(true);
	pPenTextureB->setSmooth(true);
	pReloadTexture->setSmooth(true);

	pFont->loadFromFile(Settings::FONT);
	initializeTimer();
	initializeReloadButton();
	initializeRulesButton();
	initializeExitButton();

	for (unsigned int i = 0; i < Settings::PEN_AMOUNT - 1; i++)
	{	
		penObjects.push_back(PenObject());
	}
	resetPens();
	generatePenField();

	activePenIndex = -1;
	firstMove = true;
}


Field::~Field()
{
	delete pPenTextureA;
	pPenTextureA = nullptr;

	delete pPenTextureB;
	pPenTextureB = nullptr;

	delete pFont;
	pFont = nullptr;

	delete pReloadTexture;
	pReloadTexture = nullptr;

	delete pRulesButtonTexture;
	pRulesButtonTexture = nullptr;

	delete pExitTexture;
	pExitTexture = nullptr;
}

void Field::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(timer);
	//target.draw(*pInfoText);
	target.draw(reloadButton);
	target.draw(rulesButton);
	target.draw(exitButton);

	for (const sf::RectangleShape& rs : penFields)
	{
		target.draw(rs);
	}

	for (const PenObject& pen : penObjects)
	{
		target.draw(pen);
	}

	if (activePenIndex != -1)
	{
		target.draw(penObjects[activePenIndex]);
	}

}

void Field::update(float deltaT)
{
	if (activePenIndex == -1)
	{
		exitButton.update((float)mousePosition.x, (float)mousePosition.y);

		reloadButton.update((float)mousePosition.x, (float)mousePosition.y);
		handleReloadButton();

		rulesButton.update((float)mousePosition.x, (float)mousePosition.y);
	}
	if (isFinished())
	{
		timer.stop();
	}

	timer.update(deltaT);


	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		movePen();
		return;
	}


	if (activePenIndex == -1)
	{
		for (int i = 0; i < Settings::PEN_AMOUNT - 1; i++)
		{
			if (penObjects[i].contains(mousePosition))
			{
				activePenIndex = i;
				//exit out of the loop
				i = Settings::PEN_AMOUNT;
			}
		}
	}
	else
	{
		if (firstMove)
		{
			timer.reset();
			timer.start();
			firstMove = false;
		}

		penObjects[activePenIndex].move(sf::Vector2f((float)mousePosition.x - mousePosition_old.x, (float)mousePosition.y - mousePosition_old.y));
	}
	
	mousePosition_old = mousePosition;
}

void Field::handleEvents(sf::Event sfEvent)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		reset();
	}
}

void Field::render() const
{
}


void Field::reset()
{
	resetPens();
	timer.stop();
	timer.reset();
	firstMove = true;
}

bool Field::isRulesButtonPressed() const
{
	return rulesButton.isClicked();
}

bool Field::isExitButtonPressed() const
{
	return exitButton.isClicked();
}

void Field::resetPens()
{
	for (unsigned int i = 0; i < Settings::PEN_AMOUNT - 1; i++)
	{
		if (i < 3)
		{
			penObjects[i].setPosition(getPositionFromIndex(i));
			penObjects[i].setTexture(pPenTextureA);
			penObjects[i].setPenFieldIndex(i);
			penObjects[i].setMoveDirectionLeft(false);
		}
		else
		{
			penObjects[i].setPosition(getPositionFromIndex(i + 1));
			penObjects[i].setTexture(pPenTextureB);
			penObjects[i].setPenFieldIndex(i + 1);
			penObjects[i].setMoveDirectionLeft(true);
		}

		penObjects[i].setSize(sf::Vector2f((float)Settings::PEN_WIDTH, (float)Settings::PEN_HEIGHT));
	}
}

void Field::movePen()
{
	if (activePenIndex == -1)
		return;

	int penFieldIndex = getPenFieldFromPosition();
	
	//Check If Its on no field at all and just move it back
	if (penFieldIndex == -1)
	{
		penFieldIndex = penObjects[activePenIndex].getPenFieldIndex();
	}

	//check if the field is full
	for (unsigned int i = 0; i < Settings::PEN_AMOUNT - 1; i++)
	{
		if (i != activePenIndex && penObjects[i].getPenFieldIndex() == penFieldIndex)
		{
			penFieldIndex = penObjects[activePenIndex].getPenFieldIndex();
		}
	}
	
	//Check if the move is valid
	int moveAmount = penFieldIndex - penObjects[activePenIndex].getPenFieldIndex();
	if (penObjects[activePenIndex].isMoveDirectionLeft())
	{
		if (moveAmount < -2 || moveAmount > 0)
		{
			penFieldIndex = penObjects[activePenIndex].getPenFieldIndex();
		}
	} 
	else
	{
		if (moveAmount > 2 || moveAmount < 0)
		{
			penFieldIndex = penObjects[activePenIndex].getPenFieldIndex();
		}
	}

	//Move the pen to the pen-field
	penObjects[activePenIndex].setPosition(getPositionFromIndex(penFieldIndex));
	penObjects[activePenIndex].setPenFieldIndex(penFieldIndex);


	//reset the activePenIndex
	activePenIndex = -1;
}

int Field::getPenFieldFromPosition()
{
	for (unsigned int i = 0; i < Settings::PEN_AMOUNT; i++)
	{
		if (penFields[i].getGlobalBounds().contains(sf::Vector2f((float)mousePosition.x, (float)mousePosition.y)))
		{
			return i;
		}
	}
	return -1;
}

void Field::generatePenField()
{
	const float penPosY = (Settings::HEIGHT - Settings::PEN_HEIGHT) / 2.0f;
	for (unsigned int i = 0; i < Settings::PEN_AMOUNT; i++)
	{
		sf::RectangleShape penfield;
		penfield.setSize(sf::Vector2f((float)Settings::PEN_WIDTH * 1.5f, (float)Settings::PEN_HEIGHT));
		penfield.setOutlineThickness(15);
		penfield.setPosition(getPositionFromIndex(i));
		penfield.move(sf::Vector2f(Settings::PEN_WIDTH * -0.25f,0));

		if (i < 3)
		{
			penfield.setFillColor(sf::Color(107, 168, 50));
			penfield.setOutlineColor(sf::Color(50, 146, 168));
		}
		else if(i > 3)
		{
			penfield.setFillColor(sf::Color(50, 146, 168));
			penfield.setOutlineColor(sf::Color(107, 168, 50));
		}
		else
		{
			penfield.setFillColor(sf::Color(78,78,78));
			penfield.setOutlineColor(sf::Color(245, 155, 66));
		}

		penFields.push_back(penfield);
	}
}

sf::Vector2f Field::getPositionFromIndex(int index) const
{
	const float penPosY = (Settings::HEIGHT - Settings::PEN_HEIGHT) / 2.0f;
	sf::Vector2f pos((index + 1) * 2 * (float)Settings::PEN_WIDTH, penPosY);

	return pos;
}

bool Field::isFinished()
{
	for (int i = 0; i < Settings::PEN_AMOUNT - 1; i++)
	{
		int current_index = penObjects[i].getPenFieldIndex();

		if (current_index == 3)
			return false;

		if (current_index < 3 && !penObjects[i].isMoveDirectionLeft())
			return false;

		if (current_index > 3 && penObjects[i].isMoveDirectionLeft())
			return false;
	}

	return true;
}

void Field::initializeTimer()
{
	timer.setFont(pFont);
	timer.setPosition(sf::Vector2f(Settings::PEN_WIDTH * 1.5f, Settings::HEIGHT / 20.0f));
	timer.setSize(Settings::HEIGHT / 20.0f);
	timer.setColor(sf::Color::White);
}

void Field::initializeReloadButton()
{
	reloadButton.shape.setTexture(pReloadTexture);
	reloadButton.shape.setSize(sf::Vector2f(Settings::WIDTH / 15.0f, Settings::WIDTH / 15.0f));
	reloadButton.shape.setPosition(sf::Vector2f(Settings::WIDTH / 2 - reloadButton.shape.getSize().x * 0.5, Settings::HEIGHT - reloadButton.shape.getSize().y * 1.2));

	reloadButton.setNormalColor(sf::Color::White);
	reloadButton.setHighlightColor(sf::Color(50, 146, 168));
	reloadButton.enableHighlight(true);
}

void Field::initializeRulesButton()
{
	rulesButton.shape.setTexture(pRulesButtonTexture);
	rulesButton.shape.setSize(sf::Vector2f(Settings::WIDTH / 5.0f, Settings::WIDTH / 15.0f));
	rulesButton.shape.setPosition(sf::Vector2f(Settings::WIDTH - rulesButton.shape.getSize().x - Settings::PEN_WIDTH * 1.5f, Settings::HEIGHT - rulesButton.shape.getSize().y * 1.2));

	rulesButton.setNormalColor(sf::Color(107, 168, 50));
	rulesButton.setHighlightColor(sf::Color(50, 146, 168));
	rulesButton.enableHighlight(true);
}

void Field::initializeExitButton()
{
	exitButton.shape.setTexture(pExitTexture);
	exitButton.shape.setSize(sf::Vector2f(Settings::WIDTH / 15.0f, Settings::WIDTH / 15.0f));
	exitButton.shape.setPosition(sf::Vector2f(Settings::WIDTH - exitButton.shape.getSize().x, 0.0f));

	exitButton.setNormalColor(sf::Color(107, 168, 50));
	exitButton.setHighlightColor(sf::Color(50, 146, 168));
	exitButton.enableHighlight(true);
}

void Field::handleReloadButton()
{
	if (reloadButton.isClicked())
	{
		reset();
	}
}
