#include"Ship.h"

enum LaunchedBlaster
{
	CENTER,
	LEFT,
	RIGHT
};

class BattleShip : public Ship
{
public:
	BattleShip();

	bool Collide(std::list<Bullet>*);
	void Shoot(LaunchedBlaster);

private:
	sf::Vector2f GetCenterGunPosition();
	sf::Vector2f GetLeftGunPosition();
	sf::Vector2f GetRightGunPosition();
};