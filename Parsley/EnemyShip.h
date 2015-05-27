#include"Ship.h"

class EnemyShip : public Ship
{
public:
	EnemyShip();

	bool Collide(std::list<Bullet>*);
	void Shoot();
	void Rotate(sf::Vector2f);

private:
	sf::Vector2f shootDirection;
	sf::Clock clock;
};