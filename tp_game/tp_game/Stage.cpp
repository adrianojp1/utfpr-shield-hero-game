//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Stage.h"

//======================================================================================================================================//
// === Stage methods === //

Stage::Stage(Player* pP1, Player* pP2) : Abstract_Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	_pPlayer1 = pP1;
	_pPlayer2 = pP2;

	initializeStage();
}
/*
Stage::Stage() : Abstract_Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 1 | ");

	_pPlayer1 = NULL;
	_pPlayer2 = NULL;
}
*/
Stage::~Stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

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
}

void Stage::initializeStage()
{
	//Background
	_background = new sf::RectangleShape;
	_bgtexture = NULL;
	gMng::load_n_setTexture(_background, "Media/Background.png", _bgtexture);
	_background->setSize(sf::Vector2f((float)_background->getTexture()->getSize().x, (float)_background->getTexture()->getSize().y));
	_background->setOrigin((float)_background->getTexture()->getSize().x / 2.0f, (float)_background->getTexture()->getSize().y / 2.0f);
	_background->setPosition(0.0f, -30.0f);

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
}

void Stage::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	executePlayers(deltaTime);
	
	_orc->execute(deltaTime);

	for (Block* block : _vBlocks) //execute all platforms
	{
		block->execute(deltaTime);
	}

	manage_collisions();
}

void Stage::draw() const
{
	_pGraphMng->draw(*_background);

	_pPlayer1->draw();
	if (_pPlayer2)
		_pPlayer2->draw();

	_orc->draw();

	for (Block* block : _vBlocks) //draw all platforms
	{
		block->draw();
	}
}

void Stage::executePlayers(const float deltaTime)
{
	_pPlayer1->execute(deltaTime);
	if (_pPlayer2)
		_pPlayer2->execute(deltaTime);

	std::cout << "Player1 hp: " << _pPlayer1->getHp();
	if(_pPlayer2)
		std::cout << " | " << "Player2 hp: " << _pPlayer2->getHp();
	std::cout << std::endl;
}

void Stage::drawPlayers() const
{
	_pPlayer1->draw();
	if (_pPlayer2)
		_pPlayer2->draw();
}

void Stage::setPlayer1(Player* pP1)
{
	if (pP1)
		_pPlayer1 = pP1;
}

Player* Stage::getPlayer1()
{
	return _pPlayer1;
}

void Stage::setPlayer2(Player* pP2)
{
	if (pP2)
		_pPlayer2 = pP2;
}

Player* Stage::getPlayer2()
{
	return _pPlayer2;
}

void Stage::manage_collisions()
{
	sf::Vector2f collisionDirection;
	sf::Vector2f intersection;

	if (_pPlayer1->isVulnerable() && (check_collision(static_cast<Entity*>(_pPlayer1), static_cast<Entity*>(_orc), &intersection, &collisionDirection)))
	{ //Check collision between the ent1 and the orc
		if (_pPlayer1->isDefendingInFront(collisionDirection))
		{
			collisionDirection = -collisionDirection;
			push_entities(static_cast<Entity*>(_orc), static_cast<Entity*>(_pPlayer1), &intersection, &collisionDirection, 0.0f);
		}
		else
		{
			_pPlayer1->takeDmg(_orc->getCollDmg());
		}
	}

	if (_pPlayer2)
	{
		if (_pPlayer2->isVulnerable() && (check_collision(static_cast<Entity*>(_pPlayer2), static_cast<Entity*>(_orc), &intersection, &collisionDirection)))
		{ //Check collision between the ent1 and the orc
			if (_pPlayer2->isDefendingInFront(collisionDirection))
			{
				collisionDirection = -collisionDirection;
				push_entities(static_cast<Entity*>(_orc), static_cast<Entity*>(_pPlayer2), &intersection, &collisionDirection, 0.0f);
			}
			else
			{
				_pPlayer2->takeDmg(_orc->getCollDmg());
			}
		}
	}

	for (Block* block : _vBlocks)
		//Check collision with all blocks
	{
		if (check_collision_n_push(static_cast<Entity*>(_pPlayer1), static_cast<Entity*>(block), &intersection, &collisionDirection, 0.0f))
			_pPlayer1->onCollision(collisionDirection);
		if (_pPlayer2)
		{
			if (check_collision_n_push(static_cast<Entity*>(_pPlayer2), static_cast<Entity*>(block), &intersection, &collisionDirection, 0.0f))
				_pPlayer2->onCollision(collisionDirection);
		}
		if (check_collision_n_push(static_cast<Entity*>(_orc), static_cast<Entity*>(block), &intersection, &collisionDirection, 0.0f))
			_orc->onCollision(collisionDirection);
	}
}

bool Stage::check_collision(Entity* ent1, Entity* ent2)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	sf::Vector2f otherPosition = ent2->getPosition();
	sf::Vector2f otherHalfSize = ent2->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent1->getPosition();
	sf::Vector2f thisHalfSize = ent1->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	sf::Vector2f intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x),
								 abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection.x < 0.0f && intersection.y < 0.0f)
	{
		return true;
	}
	return false;
}

bool Stage::check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	sf::Vector2f otherPosition = ent2->getPosition();
	sf::Vector2f otherHalfSize = ent2->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent1->getPosition();
	sf::Vector2f thisHalfSize = ent1->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	*intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x),
					 abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection->x < 0.0f && intersection->y < 0.0f)
	{
		if (intersection->x > intersection->y) // = (abs(intersectX) < abs(intersectY))
		{									   // pushing on the X axe
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

void Stage::push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	push = std::min(std::max(push, 0.0f), 1.0f); // clumping push between 0.0f and 1.0f

	if (intersection->x > intersection->y) // = (abs(intersectX) < abs(intersectY))
	{									   // pushing on the X axe
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

bool Stage::check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	if (check_collision(ent1, ent2, intersection, coll_direction))
	{
		push_entities(ent1, ent2, intersection, coll_direction, push);
		return true;
	}
	return false;
}