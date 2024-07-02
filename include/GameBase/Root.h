#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

class Root
{
public:
	Root() = default;
	virtual ~Root() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual sf::FloatRect getBounds() const = 0;
	virtual void resetPosition(float x, float y) = 0;
	virtual sf::Vector2f getPosition() const = 0;
private:

};

