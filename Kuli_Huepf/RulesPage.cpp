#include "RulesPage.h"
#include "Settings.h"


RulesPage::RulesPage()
{
	pRulesTexture = new sf::Texture();
	pRulesTexture->loadFromFile(Settings::RULES);


	pReturnButtonTexture = new sf::Texture();
	pReturnButtonTexture->loadFromFile(Settings::RETURN_BUTTON);

	initializeReturnButton();

	rules.setTexture(pRulesTexture);
	rules.setSize(sf::Vector2f((float)Settings::WIDTH, (float)Settings::HEIGHT / 1.3f));
	rules.setPosition(sf::Vector2f(0.0f,0.0f));
}


RulesPage::~RulesPage()
{
	delete pRulesTexture;
	pRulesTexture = nullptr;

	delete pReturnButtonTexture;
	pReturnButtonTexture = nullptr;
}

void RulesPage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rules);
	target.draw(returnButton);
}

void RulesPage::update(float deltaT)
{
	returnButton.update((float)mousePosition.x, (float)mousePosition.y);

	if (returnButton.isClicked())
	{

	}
}

void RulesPage::handleEvents(sf::Event sfEvent)
{
}

void RulesPage::render() const
{
}


bool RulesPage::isReturnButtonPressed() const
{
	return returnButton.isClicked();
}

void RulesPage::initializeReturnButton()
{
	returnButton.shape.setTexture(pReturnButtonTexture);
	returnButton.shape.setSize(sf::Vector2f(Settings::WIDTH / 5.0f, Settings::WIDTH / 15.0f));
	returnButton.shape.setPosition(sf::Vector2f(Settings::WIDTH - returnButton.shape.getSize().x - Settings::PEN_WIDTH * 1.5f, Settings::HEIGHT - returnButton.shape.getSize().y * 1.2));

	returnButton.setNormalColor(sf::Color(107, 168, 50));
	returnButton.setHighlightColor(sf::Color(50, 146, 168));
	returnButton.enableHighlight(true);
}
