#ifndef __BULLET_CLASS_DEFINED__
#define __BULLET_CLASS_DEFINED__

#include<SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	~Bullet();

	bool Draw(sf::RenderWindow&);
	void SetDirection(sf::Vector2f);
	void SetPosition(float, float);
	void SetPosition(sf::Vector2f);
	void SetColor(sf::Color);
	sf::Vector2f GetPosition();
	
private:
	sf::CircleShape bullet;
	sf::Vector2f direction;
	unsigned char screenWraps;
	bool IsOutOfScreen(sf::Vector2u);
};

#endif