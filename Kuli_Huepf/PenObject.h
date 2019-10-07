#pragma once
#include "Renderable.h"
#include <string>
#include <memory>

class PenObject : public Renderable
{
public:
	PenObject();
	~PenObject();

	// Geerbt über Renderable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void update(float deltaT) override;

	virtual void handleEvents(sf::Event sfEvent) override;

	virtual void render() const override;

public:
	void setTexture(sf::Texture* pTexture);

	void setPosition(const sf::Vector2f& pos);
	const sf::Vector2f getPosition() const;

	void setSize(const sf::Vector2f& size);
	const sf::Vector2f getSize() const;

	void setColor(const sf::Color color);
	const sf::Color getColor() const;

	bool contains(const sf::Vector2i& point);

	void move(const sf::Vector2f& amt);
	sf::RectangleShape getCopyOfShape() const;

	void setPenFieldIndex(int index);
	int getPenFieldIndex() const;

	void setMoveDirectionLeft(bool state);
	bool isMoveDirectionLeft() const;

public:
	static const std::string PEN_TEXTURE_B; 
	static const std::string PEN_TEXTURE_A; 

private:
	std::shared_ptr<sf::RectangleShape> pShape;
	int penFieldIndex;
	bool leftDirection;
};

