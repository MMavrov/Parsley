#include"Ship.h"

Ship::Ship()
{
	ship.setRadius(SHIP_RADIUS);
	ship.setOrigin(sf::Vector2f(SHIP_RADIUS, SHIP_RADIUS));

	audioManager.Load(SPACE_BLASTER_1_AUDIO_FILE);
	audioManager.Load(SPACE_BLASTER_2_AUDIO_FILE);
	audioManager.Load(EXPLOSION_1_AUDIO_FILE);
	audioManager.Load(EXPLOSION_2_AUDIO_FILE);
}

void Ship::SetPosition(sf::Vector2f position)
{
	ship.setPosition(position.x, position.y);
}

sf::Vector2f Ship::GetPosition()
{
	return sf::Vector2f(ship.getPosition().x, ship.getPosition().y);
}

void Ship::Draw(sf::RenderWindow& window)
{
	window.draw(ship);

	if (launchedBullets.size() > 0)
	{
		std::list<Bullet>::iterator bullet = launchedBullets.begin();
		while (bullet != launchedBullets.end())
		{
			if (!bullet->Draw(window))
				bullet = launchedBullets.erase(bullet);
			else
				bullet++;
		}
	}
}

void Ship::Move(MovementDirection direction)
{
	sf::Vector2f vector;

	switch (direction)
	{
	case MovementDirection::MOVE_UP:
		vector.x = 0;
		vector.y = -movementSpeed;

		ship.move(vector);
		break;

	case MovementDirection::MOVE_RIGHT:
		vector.x = movementSpeed;
		vector.y = 0;

		ship.move(vector);
		break;

	case MovementDirection::MOVE_DOWN:
		vector.x = 0;
		vector.y = movementSpeed;

		ship.move(vector);
		break;

	case MovementDirection::MOVE_LEFT:
		vector.x = -movementSpeed;
		vector.y = 0;

		ship.move(vector);
		break;
	}
}

std::list<Bullet>* Ship::GetBullets()
{
	return &launchedBullets;
}

AudioManager Ship::audioManager;
