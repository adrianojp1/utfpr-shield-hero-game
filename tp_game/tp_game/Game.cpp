//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Game.h"

//======================================================================================================================================//
// === Game methods === //
Game::Game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize();

	main_loop();
}// end constr

Game::~Game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_window)
		delete _window;
	if (_player1)
		delete _player1;

	//Temporary
	if (_background)
		delete _background;
	if (_orc)
		delete _orc;
	for (Block* block : _vBlocks)
	{
		if (block)
			delete block;
	}
	_vBlocks.clear();
}// end destr

void Game::initialize()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Background
	_background = new sf::RectangleShape;
	_bgtexture = NULL;
	gMng::load_n_setTexture(_background, "Media/Background.png", _bgtexture);
	/*_bgtexture.loadFromFile("Media/Background.png");
	_background = new sf::RectangleShape;
	_background->setTexture(&_bgtexture);*/
	_background->setSize(sf::Vector2f((float)_background->getTexture()->getSize().x, (float)_background->getTexture()->getSize().y));
	_background->setOrigin((float)_background->getTexture()->getSize().x / 2, (float)_background->getTexture()->getSize().y / 2);

	_background->setPosition(0.0f, -30.0f);
	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	_window = new Graphical_Manager;
	Entity::setGraphManager(_window);

	_main_menu = new Main_Menu();
	Main_Menu::setpGame(this);

	//Player: initial position (0, 0)
	_player1 = new Player(sf::Vector2f{ -128.0f, 136.0f });
	_player1->setDefenseKey(sf::Keyboard::S);
	_player1->setJumpKey(sf::Keyboard::W);
	_player1->setLeftKey(sf::Keyboard::A);
	_player1->setRightKey(sf::Keyboard::D);

	//Orc: initial position (0, 0)
	_orc = new Orc(sf::Vector2f{ 128.0f, 136.0f });

	//Blocks
	for (int i = -4; i < 0; i++)
	{
		_vBlocks.push_back(new Block(sf::Vector2f(float(Block::size.x * i), 200.0f)));
		_vBlocks.push_back(new Block(sf::Vector2f(float(Block::size.x * i + Block::size.x * 6), 200.0f)));
	}
	//Orc Platform Edges
	_vBlocks.push_back(new Block(sf::Vector2f(float(Block::size.x * 1), 136.0f))); //Left
	_vBlocks.push_back(new Block(sf::Vector2f(float(Block::size.x * 6), 136.0f))); //Right

	_deltaTime = 0.0f;
	Timer::setpDeltaTime(&_deltaTime);

	_main_menu->open();
}// end initialize

void Game::main_loop()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	while (_window->isOpen())
	{
		_deltaTime = _clock.restart().asSeconds(); //Iteration clock
		if (_deltaTime > 1.0f / 20.f)
			_deltaTime = 1.0f / 20.f;

		if (_main_menu->isActive())
		{
			_main_menu->execute(_deltaTime);
		}
		//_pause_menu;
		//_newGame_menu;
		//_saves_menu;
		if(!_main_menu->isActive())
		{
			executeStage(_deltaTime);
		}
		
		_window->execute();

		_window->clear(); //Clear window buffer

		draw(); //Future game drawer: draw all objects

		_window->display(); //Show current frame
	} //end main loop
}
void Game::close()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_window->close();
}
// end main_loop

void Game::execute(float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_player1->execute(deltaTime);
	_orc->execute(deltaTime);

	for (Block* block : _vBlocks) //execute all platforms
	{
		block->execute(deltaTime);
	}
}// end execute

void Game::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_window->draw(*_background);

	if (_main_menu->isActive())
	{
		_main_menu->draw();
	}
	else
	{
		_player1->draw();
		_orc->draw();

		for (Block* block : _vBlocks) //draw all platforms
		{
			block->draw();
		}
	}
}// end draw

//Temporary methods

bool Game::check_collision(Entity* ent1, Entity* ent2)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	sf::Vector2f otherPosition = ent2->getPosition();
	sf::Vector2f otherHalfSize = ent2->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent1->getPosition();
	sf::Vector2f thisHalfSize = ent1->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	sf::Vector2f intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x) ,
								  abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection.x < 0.0f && intersection.y < 0.0f)
	{
		return true;
	}
	return false;
}

bool Game::check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	sf::Vector2f otherPosition = ent2->getPosition();
	sf::Vector2f otherHalfSize = ent2->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent1->getPosition();
	sf::Vector2f thisHalfSize = ent1->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	*intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x) ,
					  abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection->x < 0.0f && intersection->y < 0.0f)
	{
		if (intersection->x > intersection->y) // = (abs(intersectX) < abs(intersectY))
		{							 // pushing on the X axe
			if (delta.x > 0.0f)
			{
				*coll_direction = sf::Vector2f(1.0f, 0.0f);
			}
			else
			{
				*coll_direction = sf::Vector2f(-1.0f, 0.0f);
			}
		}
		else
		{ // pushing on the Y axe
			if (delta.y > 0.0f)
			{
				*coll_direction = sf::Vector2f(0.0f, 1.0f);
			}
			else
			{
				*coll_direction = sf::Vector2f(0.0f, -1.0f);
			}
		}
		return true;
	}
	return false;
}

void Game::push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	push = std::min(std::max(push, 0.0f), 1.0f); // clumping push between 0.0f and 1.0f

	if (intersection->x >intersection->y) // = (abs(intersectX) < abs(intersectY))
	{							 // pushing on the X axe
		if (coll_direction->x > 0.0f)
		{

			ent1->move((intersection->x * (1.0f - push)), 0.0f);
			ent2->move((-intersection->x * push), 0.0f);
		}
		else
		{
			ent1->move((-intersection->x * (1.0f - push)), 0.0f);
			ent2->move((intersection->x * push), 0.0f);
		}
	}
	else
	{ // pushing on the Y axe
		if (coll_direction->y > 0.0f)
		{
			ent1->move(0.0f, (intersection->y * (1.0f - push)));
			ent2->move(0.0f, (-intersection->y * push));
		}
		else
		{
			ent1->move(0.0f, (-intersection->y * (1.0f - push)));
			ent2->move(0.0f, (intersection->y * push));
		}
	}
}

bool Game::check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	if (check_collision(ent1, ent2, intersection, coll_direction))
	{
		push_entities(ent1, ent2, intersection, coll_direction, push);
		return true;
	}
	return false;
}

void Game::executeStage(float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	execute(_deltaTime);

	manage_collisions();
}

void Game::manage_collisions()
{
	sf::Vector2f collisionDirection;
	sf::Vector2f intersection;

	if (_player1->isVulnerable())
	{
		if ((check_collision(static_cast<Entity*>(_player1), static_cast<Entity*>(_orc), &intersection, &collisionDirection)))
		{//Check collision between the ent1 and the orc
			if (_player1->isDefendingInFront(collisionDirection))
			{
				collisionDirection = -collisionDirection;
				push_entities(static_cast<Entity*>(_orc), static_cast<Entity*>(_player1), &intersection, &collisionDirection, 0.0f);
			}
			else
			{
				_player1->takeDmg(_orc->getCollDmg());
			}
		}
	}

	for (Block* block : _vBlocks)
		//Check collision with all blocks
	{
		if (check_collision_n_push(static_cast<Entity*>(_player1), static_cast<Entity*>(block), &intersection, &collisionDirection, 0.0f))
			_player1->onCollision(collisionDirection);
		if (check_collision_n_push(static_cast<Entity*>(_orc), static_cast<Entity*>(block), &intersection, &collisionDirection, 0.0f))
			_orc->onCollision(collisionDirection);
	}
}
