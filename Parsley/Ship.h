#include<SFML/Graphics.hpp>
#include<list>
#include"Bullet.h"
#include"MathFunctions.h"
#include"AudioManager.h"

#define _USE_MATH_DEFINES
#include<math.h>

#ifndef __SHIP_CLASS_DEFINED__
#define __SHIP_CLASS_DEFINED__

enum MovementDirection
{
	MOVE_UP,
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT
};

class Ship
{
public:
	Ship();

	void Draw(sf::RenderWindow&);	
	void SetPosition(sf::Vector2f);
	sf::Vector2f GetPosition();
	void Move(MovementDirection);
	std::list<Bullet>* GetBullets();

	virtual bool Collide(std::list<Bullet>*) = 0;

protected:
	sf::CircleShape ship;
	std::list<Bullet> launchedBullets;
	
	static AudioManager audioManager;

	const float SHIP_RADIUS = 30.f;
	const std::string SPACE_BLASTER_1_AUDIO_FILE = "SpaceBlaster_01.wav";
	const std::string SPACE_BLASTER_2_AUDIO_FILE = "SpaceBlaster_02.wav";
	const std::string EXPLOSION_1_AUDIO_FILE = "Explosion_01.wav";
	const std::string EXPLOSION_2_AUDIO_FILE = "Explosion_02.wav";

	float movementSpeed;
};

#endif