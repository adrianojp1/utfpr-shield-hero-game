//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Level.h"

const int Level::BACKGROUND_0(0);
const int Level::BACKGROUND_1(1);
const int Level::CONCRETE(2);
const int Level::FRONTGROUND(3);

//======================================================================================================================================//
// === Level methods === //
Level::Level(const std::string level_filePath, sf::Vector2f initPosition, const int nEnemies, const int nObstacles) : Abstract_Entity(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_nTotalEnemies = nEnemies;
	_nTotalObstacles = nObstacles;
	_tilesIds_matrix = NULL;

	serializeLayers(level_filePath);
	initializeEntities();
}

Level::Level()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	_matrixSize = { 0, 0 };
	_playerSpawn = { 0.0f, 0.0f };
	_nTotalEnemies = 0;
	_nTotalObstacles = 0;
	_tilesIds_matrix = NULL;
}

Level::~Level()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_tilesIds_matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < _matrixSize.y; j++)
			{
				delete _tilesIds_matrix[i][j];
			}
			delete _tilesIds_matrix[i];
		}
		delete _tilesIds_matrix;
	}

	if (_orc)
		delete _orc;

	for (Entity* pEnt : _block_list)
	{
		if (pEnt)
			delete pEnt;
	}
	_block_list.clearList();
}

void Level::serializeLayers(const std::string level_filePath)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	std::ifstream level_reader(level_filePath, std::ios::in);
	if (!level_reader)
	{
		std::cerr << "File couldn't be opened!" << std::endl;
		fflush(stdin);
		getchar();
	}

	std::string matrix_line = "";
	std::string id = "";
	std::string::iterator iterator;

	std::getline(level_reader, matrix_line);
	iterator = matrix_line.begin();

	int layerWidth = extractInt(matrix_line, iterator);
	iterator++;
	int layerHeight = extractInt(matrix_line, iterator);
	std::getline(level_reader, matrix_line);
	
	_matrixSize = { layerWidth, layerHeight };

	_tilesIds_matrix = new int** [4];
	
	for (int i = 0; i < 4; i++)
	{
		_tilesIds_matrix[i] = new int* [_matrixSize.y];
		
		for (int j = 0; j < _matrixSize.y; j++)
		{
			std::getline(level_reader, matrix_line);

			if (matrix_line.begin() == matrix_line.end())
			{
				j--;
				continue;
			}

			_tilesIds_matrix[i][j] = new int[_matrixSize.x];

			std::string::iterator iterator = matrix_line.begin();

			for (int k = 0; k < _matrixSize.x; k++)
			{
				_tilesIds_matrix[i][j][k] = extractInt(matrix_line, iterator) - 1;

				if(iterator != matrix_line.end())
					iterator++;
			}
		}
	}
	/*
	//printing first layer
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < _matrixSize.y; j++)
		{
			for (int k = 0; k < _matrixSize.x; k++)
			{
				std::cout << _tilesIds_matrix[i][j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}*/

	level_reader.close();
}

int Level::extractInt(std::string& str, std::string::iterator& it)
{
	std::string id;
	for (id = ""; it != str.end() && *it != ','; it++)
	{
		id += *it;
	}
	return (std::stoi(id));
}

void Level::initializeEntities()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	sf::Vector2f block_realSize = Block::size * gMng::textures_scale;

	_playerSpawn = { block_realSize * sf::Vector2i{ 3, 8 } +_position};
	setPlayersSpawnPoint();
	movePlayersToSpawn();

	Block* pBlock = NULL;
	int id;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _matrixSize.y; j++)
		{
			for (int k = 0; k < _matrixSize.x; k++)
			{
				id = _tilesIds_matrix[i][j][k];
				if (id != -1)
				{
					pBlock = new Block(block_realSize * sf::Vector2i{ k, j } +_position, _tilesIds_matrix[i][j][k]);
					_all_EntList.includeEntity(pBlock);
				}
			}
		}
	}

	for (int j = 0; j < _matrixSize.y; j++)
	{
		for (int k = 0; k < _matrixSize.x; k++)
		{
			id = _tilesIds_matrix[CONCRETE][j][k];
			if (id != -1)
			{
				pBlock = new Block(block_realSize * sf::Vector2i{ k, j } +_position, _tilesIds_matrix[CONCRETE][j][k]);
				_all_EntList.includeEntity(pBlock);
				_block_list.includeEntity(pBlock);
			}
		}
	}

	_orc = new Orc(block_realSize * sf::Vector2i{ 10, 8 } + _position);
	_all_EntList.includeEntity(_orc);
	_all_EntList.includeEntity(_pPlayer1);
	if (_pPlayer2)
		_all_EntList.includeEntity(_pPlayer2);

	for (int j = 0; j < _matrixSize.y; j++)
	{
		for (int k = 0; k < _matrixSize.x; k++)
		{
			id = _tilesIds_matrix[FRONTGROUND][j][k];
			if (id != -1)
			{
				pBlock = new Block(block_realSize * sf::Vector2i{ k, j } +_position, _tilesIds_matrix[FRONTGROUND][j][k]);
				_all_EntList.includeEntity(pBlock);
			}
		}
	}
}

void Level::setPlayersSpawnPoint()
{
	_pPlayer1->setCurrSpawnPoint(_playerSpawn);
	if (_pPlayer2)
		_pPlayer2->setCurrSpawnPoint(_playerSpawn);
}

void Level::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	executePlayers(deltaTime);

	_orc->execute(deltaTime);

	for (Entity* pEnt : _block_list)
	{
		pEnt->execute(deltaTime);
	}

	manage_collisions();
}

void Level::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//_pGraphMng->draw(*_background);

	
	for (Entity* pEnt : _all_EntList)
	{
		pEnt->draw();
	}

	//drawPlayers();
}

void Level::executePlayers(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_pPlayer1->execute(deltaTime);
	if (_pPlayer2)
		_pPlayer2->execute(deltaTime);

	std::cout << "Player1 hp: " << _pPlayer1->getHp();
	if (_pPlayer2)
		std::cout << " | " << "Player2 hp: " << _pPlayer2->getHp();
	std::cout << std::endl;
}

void Level::drawPlayers() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_pPlayer1->draw();
	if (_pPlayer2)
		_pPlayer2->draw();
}

void Level::movePlayersToSpawn()
{
	_pPlayer1->setPosition(_playerSpawn);
	if (_pPlayer2)
		_pPlayer2->setPosition(_playerSpawn);
}

void Level::setTiles_ids_matrix(int*** matrix)
{
	_tilesIds_matrix = matrix;
}

int*** Level::getTiles_ids_matrix()
{
	return _tilesIds_matrix;
}

void Level::setMatrixSize(sf::Vector2i size)
{
	_matrixSize = size;
}

sf::Vector2i Level::getMatrixSize() const
{
	return _matrixSize;
}

void Level::manage_collisions()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	sf::Vector2f collisionDirection;
	sf::Vector2f intersection;

	for (Entity* pEnt : _block_list)
		//Check collision with all blocks
	{
		if (check_collision_n_push(static_cast<Entity*>(_pPlayer1), pEnt, &intersection, &collisionDirection, 0.0f))
			_pPlayer1->onCollision(collisionDirection);
		if (_pPlayer2)
		{
			if (check_collision_n_push(static_cast<Entity*>(_pPlayer2), pEnt, &intersection, &collisionDirection, 0.0f))
				_pPlayer2->onCollision(collisionDirection);
		}
		if (check_collision_n_push(static_cast<Entity*>(_orc), pEnt, &intersection, &collisionDirection, 0.0f))
			_orc->onCollision(collisionDirection);
	}

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
}

bool Level::check_collision(Entity* ent1, Entity* ent2)
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

bool Level::check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction)
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

void Level::push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

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

bool Level::check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (check_collision(ent1, ent2, intersection, coll_direction))
	{
		push_entities(ent1, ent2, intersection, coll_direction, push);
		return true;
	}
	return false;
}
