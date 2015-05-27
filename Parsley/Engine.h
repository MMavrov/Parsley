#include<SFML/Graphics.hpp>
#include"AudioManager.h"
#include"BattleShip.h"
#include"EnemyShip.h"
#include <random>

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	sf::RenderWindow window;
	AudioManager audioManager;
	sf::Text text;
	sf::Text frames;
	sf::Font font;

	bool gameOver = false;
	int score;
	Ship* parsley;
	std::list<EnemyShip*> enemyShips;
	sf::Clock clock;

	void HandleParsleyMovement();
	void HandleParsleyExistence();
	void HandleEnemiesExistence();

	void InitializeEnemyShip();

	const int NUMBER_OF_ENEMIES = 2;
	const sf::Vector2u WINDOW_SIZE = sf::Vector2u(800, 600);
	const std::string AMBIENCE_AUDIO_FILE = "Ambience.wav";
};