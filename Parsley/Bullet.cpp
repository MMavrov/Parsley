#include"Bullet.h"

const float BULLET_RADIUS = 3.f;
const float BULLET_SPEED_SLOW = 1.f / 30.f;

// Use when the enemies have to be 'stronger'
const float BULLET_SPEED_FAST = 1.f / 10.f;

const unsigned char ALLOWED_SCREEN_WRAPS = 3;

Bullet::Bullet()
{
	bullet.setRadius(BULLET_RADIUS);
	screenWraps = 0;
}

Bullet::~Bullet()
{
}

bool Bullet::Draw(sf::RenderWindow& window)
{
	if (IsOutOfScreen(window.getSize()))
	{	
		////If you are annoyed by all those bullets fying around
		//return false;
		
		sf::Vector2f oldPosition = bullet.getPosition();

		if (oldPosition.x <= 0)
			bullet.setPosition(sf::Vector2f(window.getSize().x, oldPosition.y));
		else if (oldPosition.x >= window.getSize().x)
			bullet.setPosition(sf::Vector2f(0, oldPosition.y));
		else if (oldPosition.y <= 0)
			bullet.setPosition(sf::Vector2f(oldPosition.x, window.getSize().y));
		else if (oldPosition.y >= window.getSize().y)
			bullet.setPosition(sf::Vector2f(oldPosition.x, 0));
		
		screenWraps++;

		if (ALLOWED_SCREEN_WRAPS == screenWraps)
			return false;
	}

	bullet.move(direction);

	window.draw(bullet);
	return true;
}

void Bullet::SetDirection(sf::Vector2f bulletDirection)
{
	direction = bulletDirection * BULLET_SPEED_SLOW;
}

void Bullet::SetPosition(float x, float y)
{
	bullet.setPosition(x - BULLET_RADIUS, y - BULLET_RADIUS);
}

void Bullet::SetColor(sf::Color color)
{
	bullet.setFillColor(color);
}

void Bullet::SetPosition(sf::Vector2f position)
{
	bullet.setPosition(position.x - BULLET_RADIUS, position.y - BULLET_RADIUS);
}

sf::Vector2f Bullet::GetPosition()
{
	return sf::Vector2f(
		bullet.getPosition().x + BULLET_RADIUS, 
		bullet.getPosition().y + BULLET_RADIUS);
}

bool Bullet::IsOutOfScreen(sf::Vector2u size)
{
	if (bullet.getPosition().x < 0.f 
		|| bullet.getPosition().x > size.x
		|| bullet.getPosition().y < 0.f 
		|| bullet.getPosition().y > size.y)
		return true;

	return false;
}