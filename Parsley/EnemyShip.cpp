#include "EnemyShip.h"

EnemyShip::EnemyShip() : Ship()
{
	ship.setPointCount(5);
	ship.setFillColor(sf::Color(192, 0, 0));

	movementSpeed = 0.01;
}

void EnemyShip::Shoot()
{
	if (clock.getElapsedTime().asSeconds() > 2)
	{
		audioManager.Play(SPACE_BLASTER_2_AUDIO_FILE);

		Bullet bullet;
		sf::Vector2f position = GetPosition();

		bullet.SetPosition(
			position.x + (shootDirection.x * SHIP_RADIUS),
			position.y + (shootDirection.y * SHIP_RADIUS));
		bullet.SetDirection(shootDirection);
		bullet.SetColor(sf::Color(192, 0, 0));

		launchedBullets.push_back(bullet);
		
		clock.restart();
	}
}

void EnemyShip::Rotate(sf::Vector2f target)
{
	sf::Vector2f newShootDirection = MathFunctions::Normalize(target - GetPosition());
	
	float shipRotation = atan2f(newShootDirection.y, newShootDirection.x) * (180.f / M_PI);

	ship.setRotation(shipRotation + 90);

	shootDirection = newShootDirection;
}

bool EnemyShip::Collide(std::list<Bullet>* bullets)
{
	std::list<Bullet>::iterator bullet = bullets->begin();
	while (bullet != bullets->end())
	{
		// Intersect with the bounding circle works for now
		sf::Vector2f distance = GetPosition() - bullet->GetPosition();
		float magnitudeOfDistanceSquared = distance.x * distance.x + distance.y * distance.y;
		auto maximumCollidingDistanceBetweenBoundings = (SHIP_RADIUS + 3.f) * (SHIP_RADIUS + 3.f);

		if (magnitudeOfDistanceSquared <= maximumCollidingDistanceBetweenBoundings)
		{
			audioManager.Play(EXPLOSION_2_AUDIO_FILE);

			bullet = bullets->erase(bullet);
			return true;
		}

		bullet++;
	}

	return false;
}