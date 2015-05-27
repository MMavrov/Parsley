#include"Engine.h"

Engine::Engine()
{
	window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Lt. Parsley's adventures");

	audioManager.Stream(AMBIENCE_AUDIO_FILE);
	audioManager.Play(AMBIENCE_AUDIO_FILE);

	parsley = new BattleShip();
	parsley->SetPosition(sf::Vector2f(
		(float)(WINDOW_SIZE.x / 2),
		(float)(WINDOW_SIZE.y - 100)));

	InitializeEnemyShip();

	font.loadFromFile("sewer.ttf");

	text.setFont(font);
	text.setCharacterSize(20);
	text.setColor(sf::Color(192, 192, 192));

	frames.setFont(font);
	frames.setCharacterSize(24);
	frames.setColor(sf::Color(192, 192, 192));

	score = 0;
}

Engine::~Engine()
{
	delete parsley;

	std::list<EnemyShip*>::iterator enemy = enemyShips.begin();

	while (enemy != enemyShips.end())
	{
		delete (*enemy);
		enemy++;
	}
}

void Engine::Run()
{
	while (window.isOpen())
	{
		if (!gameOver)
		{
			audioManager.Update();
			window.clear();

			HandleParsleyExistence();
			HandleEnemiesExistence();

			sf::Event event;
			if (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
						window.close();

					else if (event.key.code == sf::Keyboard::W)
						((BattleShip*)parsley)->Shoot(LaunchedBlaster::CENTER);

					else if (event.key.code == sf::Keyboard::A)
						((BattleShip*)parsley)->Shoot(LaunchedBlaster::LEFT);

					else if (event.key.code == sf::Keyboard::D)
						((BattleShip*)parsley)->Shoot(LaunchedBlaster::RIGHT);
				}
			}

			text.setString("Use arrows to move.\nUse W, A and D to shoot.\nEsc to exit.\nScore: " + std::to_string(score));
			window.draw(text);
			
			/*frames.setPosition(sf::Vector2f(670.f, 0.f));
			frames.setString("FPS: " + std::to_string(1.f / clock.restart().asSeconds()));
			window.draw(frames);*/
		}
		else
		{
			window.clear();

			text.setPosition(sf::Vector2f(100.f, 100.f));
			text.setCharacterSize(100);
			text.setString("GAME OVER!");
			window.draw(text);

			sf::Event event;
			if (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}

			audioManager.Update();
		}
		
		window.display();
	}
}

void Engine::HandleParsleyMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		parsley->Move(MovementDirection::MOVE_UP);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		parsley->Move(MovementDirection::MOVE_RIGHT);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		parsley->Move(MovementDirection::MOVE_DOWN);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		parsley->Move(MovementDirection::MOVE_LEFT);
}

void Engine::HandleParsleyExistence()
{
	HandleParsleyMovement();
	parsley->Draw(window);

	for (EnemyShip* enemy : enemyShips)
	{
		if (parsley->Collide(enemy->GetBullets()))
			gameOver = true;
	}
}

void Engine::HandleEnemiesExistence()
{
	if (enemyShips.size() < NUMBER_OF_ENEMIES)
	{
		InitializeEnemyShip();
	}
	else
	{
		std::list<EnemyShip*>::iterator enemy = enemyShips.begin();

		while (enemy != enemyShips.end())
		{
			if ((*parsley->GetBullets()).size() > 0 && (*enemy)->Collide(parsley->GetBullets()))
			{
				enemy = enemyShips.erase(enemy);
				score++;
				
			}
			else if ((*enemy)->GetPosition().x > WINDOW_SIZE.x || (*enemy)->GetPosition().y > WINDOW_SIZE.y)
			{
				enemy = enemyShips.erase(enemy);
			}
			else
			{
				(*enemy)->Draw(window);
				(*enemy)->Rotate(((BattleShip*)parsley)->GetPosition());
				(*enemy)->Move(MovementDirection::MOVE_DOWN);
				(*enemy)->Shoot();

				enemy++;
			}
		}
	}
}

void Engine::InitializeEnemyShip()
{
	const int range_from = 0;
	const int range_to = WINDOW_SIZE.x;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr(range_from, range_to);

	EnemyShip* enemy = new EnemyShip();
	enemy->SetPosition(sf::Vector2f(distr(generator), -30.f));

	enemyShips.push_back(enemy);
}