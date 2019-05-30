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
	initialize();

	main_loop();
}// end constr

Game::~Game()
{
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
	//Background
	_background = new sf::RectangleShape;
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
	_player1 = new Player(sf::Vector2f{ -128.0f, 0.0f });

	//Orc: initial position (0, 0)
	_orc = new Enemy(sf::Vector2f{ 128.0f, 0.0f });

	//Blocks
	for (int i = -4; i < 0; i++)
	{
		_vBlocks.push_back(new Block(sf::Vector2f(float(Block::size.x * i), 200.0f)));
		_vBlocks.push_back(new Block(sf::Vector2f(float(Block::size.x * i + Block::size.x * 6), 200.0f)));
	}

	_deltaTime = 0.0f;
	Timer::setpDeltaTime(&_deltaTime);

	_main_menu->open();
}// end initialize

void Game::main_loop()
{
	while (_window->isOpen())
	{
		_deltaTime = _clock.restart().asSeconds(); //Iteration clock
		if (_deltaTime > 1.0f / 20.f)
			_deltaTime = 1.0f / 20.f;

		_main_menu->execute(_deltaTime);

		executeStage(_deltaTime);

		_window->execute();

		_window->clear(); //Clear window buffer

		draw(); //Future game drawer: draw all objects

		_window->display(); //Show current frame
	} //end main loop
}
void Game::close()
{
	_window->close();
}
// end main_loop

void Game::execute(float deltaTime)
{
	_player1->execute(deltaTime);
	_orc->execute(deltaTime);

	for (Block* block : _vBlocks) //execute all platforms
	{
		block->execute(deltaTime);
	}
}// end execute

void Game::draw() const
{
	_window->draw(*_background);

	_main_menu->draw();

	_player1->draw();
	_orc->draw();

	for (Block* block : _vBlocks) //draw all platforms
	{
		block->draw();
	}
}// end draw

//Temporary methods
bool Game::checkCollision(Entity* player, Entity* block, sf::Vector2f* collisionDirection, float push)
{
	sf::Vector2f otherPosition = block->getPosition();
	sf::Vector2f otherHalfSize = block->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = player->getPosition();
	sf::Vector2f thisHalfSize = player->getCollider()->getSize() / 2.0f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f); // clumping push between 0.0f and 1.0f

		if (intersectX > intersectY) // = (abs(intersectX) < abs(intersectY))
		{							 // pushing on the X axe
			if (deltaX > 0.0f)
			{

				player->move((intersectX * (1.0f - push)), 0.0f);
				block->move((-intersectX * push), 0.0f);

				*collisionDirection = sf::Vector2f(1.0f, 0.0f);
			}
			else
			{
				player->move((-intersectX * (1.0f - push)), 0.0f);
				block->move((intersectX * push), 0.0f);

				*collisionDirection = sf::Vector2f(-1.0f, 0.0f);
			}
		}
		else
		{ // pushing on the Y axe
			if (deltaY > 0.0f)
			{
				player->move(0.0f, (intersectY * (1.0f - push)));
				block->move(0.0f, (-intersectY * push));

				*collisionDirection = sf::Vector2f(0.0f, 1.0f);
			}
			else
			{
				player->move(0.0f, (-intersectY * (1.0f - push)));
				block->move(0.0f, (intersectY * push));

				*collisionDirection = sf::Vector2f(0.0f, -1.0f);
			}
		}
		return true;
	}
	return false;
}
void Game::executeStage(float deltaTime)
{
	execute(_deltaTime); //Future game executor: execute all objects

	sf::Vector2f collisionDirection;

	//Check collision between the player and the orc
	if (_player1->isDefending())
	{
		if (checkCollision(static_cast<Entity*>(_player1), static_cast<Entity*>(_orc), &collisionDirection, 1.0f))
			_player1->onCollision(collisionDirection);
	}
	else
	{
		if (checkCollision(static_cast<Entity*>(_player1), static_cast<Entity*>(_orc), &collisionDirection, 0.5f))
			_player1->onCollision(collisionDirection);
	}

	for (Block* block : _vBlocks)
		//Check collision with all blocks
	{
		if (checkCollision(static_cast<Entity*>(_player1), static_cast<Entity*>(block), &collisionDirection, 0.0f))
			_player1->onCollision(collisionDirection);
		if (checkCollision(static_cast<Entity*>(_orc), static_cast<Entity*>(block), &collisionDirection, 0.0f))
			_orc->onCollision(collisionDirection);
	}
}