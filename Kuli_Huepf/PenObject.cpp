#include "PenObject.h"

const std::string PenObject::PEN_TEXTURE_B = "textures/BlueKuli.png";
const std::string PenObject::PEN_TEXTURE_A = "textures/GreenKuli.png";

PenObject::PenObject()
{
	pShape = std::make_shared<sf::RectangleShape>();
	penFieldIndex = -1;
	leftDirection = false;
}


PenObject::~PenObject()
{
}

void PenObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*pShape);
}

void PenObject::update(float deltaT)
{
}

void PenObject::handleEvents(sf::Event sfEvent)
{
	
}

void PenObject::render() const
{
}

void PenObject::setTexture(sf::Texture * pTexture)
{
	pShape->setTexture(pTexture);
}

void PenObject::setPosition(const sf::Vector2f & pos)
{
	pShape->setPosition(pos);
}

const sf::Vector2f PenObject::getPosition() const
{
	return pShape->getPosition();
}

void PenObject::setSize(const sf::Vector2f & size)
{
	pShape->setSize(size);
}

const sf::Vector2f PenObject::getSize() const
{
	return pShape->getSize();
}

void PenObject::setColor(const sf::Color color)
{
	pShape->setFillColor(color);
}

const sf::Color PenObject::getColor() const
{
	return pShape->getFillColor();
}

bool PenObject::contains(const sf::Vector2i & point)
{
	const sf::Vector2f& pos = pShape->getPosition();
	const sf::Vector2f& size = pShape->getSize();
	return (point.x > pos.x && point.x < pos.x + size.x && point.y > pos.y && point.y < pos.y + size.y);
}

void PenObject::move(const sf::Vector2f & amt)
{
	pShape->move(amt);
}

sf::RectangleShape PenObject::getCopyOfShape() const
{
	return *pShape;
}

void PenObject::setPenFieldIndex(int index)
{
	penFieldIndex = index;
}

int PenObject::getPenFieldIndex() const
{
	return penFieldIndex;
}

void PenObject::setMoveDirectionLeft(bool state)
{
	leftDirection = state;
}

bool PenObject::isMoveDirectionLeft() const
{
	return leftDirection;
}
