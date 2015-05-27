#include "BattleShip.h"

BattleShip::BattleShip() : Ship()
{
	ship.setPointCount(3);
	ship.setFillColor(sf::Color(0, 192, 0));

	movementSpeed = 0.1;
}

void BattleShip::Shoot(LaunchedBlaster launchedBlaster)
{
	Bullet bullet;
	bullet.SetColor(sf::Color(0, 192, 0));

	audioManager.Play(SPACE_BLASTER_1_AUDIO_FILE);

	switch (launchedBlaster)
	{
	case LaunchedBlaster::CENTER:
		bullet.SetPosition(GetCenterGunPosition());
		bullet.SetDirection(sf::Vector2f(0.f, -1.f));
		break;

	case LaunchedBlaster::LEFT:
		bullet.SetPosition(GetLeftGunPosition());
		bullet.SetDirection(
			sf::Vector2f((float)cos(210.f * M_PI / 180.0f),
			(float)-sin(210.f * M_PI / 180.0f)));
		break;

	case LaunchedBlaster::RIGHT:
		bullet.SetPosition(GetRightGunPosition());
		bullet.SetDirection(
			sf::Vector2f((float)cos(330.f * M_PI / 180.f),
			(float)-sin(330.f * M_PI / 180.f)));
		break;

	default:
		break;
	}

	launchedBullets.push_back(bullet);
}

bool BattleShip::Collide(std::list<Bullet>* bullets)
{
	std::list<Bullet>::iterator bullet = bullets->begin();
	
	while (bullet != bullets->end())
	{
		bool b1 = MathFunctions::SignedArea(bullet->GetPosition(), GetCenterGunPosition(), GetLeftGunPosition()) < 0.f;
		bool b2 = MathFunctions::SignedArea(bullet->GetPosition(), GetLeftGunPosition(), GetRightGunPosition()) < 0.f;
		bool b3 = MathFunctions::SignedArea(bullet->GetPosition(), GetRightGunPosition(), GetCenterGunPosition()) < 0.f;

		if (b1 && b2 && b3)
		{
			audioManager.Play(EXPLOSION_1_AUDIO_FILE);

			bullet = bullets->erase(bullet);
			return true;
		}

		bullet++;
	}

	return false;
}

sf::Vector2f BattleShip::GetCenterGunPosition()
{
	return sf::Vector2f(GetPosition().x, GetPosition().y - SHIP_RADIUS);
}

sf::Vector2f BattleShip::GetRightGunPosition()
{
	return sf::Vector2f(
		GetPosition().x + (float)(cos(330.f * M_PI / 180.f) * SHIP_RADIUS),
		GetPosition().y + (float)(-sin(330.f * M_PI / 180.f) * SHIP_RADIUS));
}

sf::Vector2f BattleShip::GetLeftGunPosition()
{
	return sf::Vector2f(
		GetPosition().x + (float)(cos(210 * M_PI / 180.f) * SHIP_RADIUS),
		GetPosition().y + (float)(-sin(210 * M_PI / 180.f) * SHIP_RADIUS));
}