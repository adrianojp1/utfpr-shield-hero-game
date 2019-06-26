//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Level.h"

#include "Stage.h"
#include "Vertical_Stage.h"
#include "Horizontal_Stage.h"

//======================================================================================================================================//
// === Statics Initialization === //
const int Level::nLayers(5);

//======================================================================================================================================//
// === Level methods === //
Level::Level(std::string level_tiles_filePath, sf::Vector2f initPosition, Stage* pStage) : Abstract_Entity(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_pStage = pStage;
	_tilesIds_matrix = NULL;
	_finished = false;

	_nTotalObstacles = 5;
	_nTotalEnemies = 5;

	serializeTiles(level_tiles_filePath);
	initializeEntities();

	_playersProps.setCharacterSize(50);
	_playersProps.setPosition(_position + sf::Vector2f{ 70.0f, 30.0f });
	_playersProps.setFont(*gMng::normal_text_ft);
	_playersProps.setFillColor(sf::Color(50, 150, 0));
	_playersProps.setOutlineColor(sf::Color::Black);
	_playersProps.setOutlineThickness(2.0f);
}

Level::Level()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	_matrixSize = { 0, 0 };
	_playerSpawn = { 0.0f, 0.0f };
	_nTotalEnemies = 0;
	_nTotalObstacles = 0;
	_viewCenter = { 0.0f, 0.0f };
	_realSize = { 0.0f, 0.0f };
	_tilesIds_matrix = NULL;
}

Level::~Level()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_tilesIds_matrix)
	{
		for (int i = 0; i < nLayers; i++)
		{
			for (int j = 0; j < _matrixSize.y; j++)
			{
				delete _tilesIds_matrix[i][j];
			}
			delete _tilesIds_matrix[i];
		}
		delete _tilesIds_matrix;
	}


	_enemy_list.delete_enemies();
	_obstacle_list.delete_obstacles();
	_projectile_list.delete_projectiles();

	for (int i = 0; i < 4; i++)
	{
		_tile_list[i].delete_tiles();
	}

	for (sf::RectangleShape* pR : _levelEnd)
	{
		if (pR)
			delete pR;
	}
	_levelEnd.clear();
}

void Level::serializeTiles(const std::string level_filePath)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	std::ifstream level_reader(level_filePath, std::ios::in);
	if (!level_reader)
	{
		std::cerr << "File couldn't be opened!" << std::endl;
		fflush(stdin);
		getchar();
	}

	jumpToNext_number(level_reader);
	serializeDimensions(level_reader);

	_tilesIds_matrix = new int** [nLayers];
	for (int i = 0; i < nLayers; i++)
	{
		_tilesIds_matrix[i] = new int* [_matrixSize.y];
		
		jumpToNext_number(level_reader);
		serializeLayer(level_reader, _tilesIds_matrix[i]);
	}
	/*
	//printing first layer
	for (int i = 0; i < nLayers; i++)
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

void Level::serializeLayer(std::ifstream& level_reader, int** matrix)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	std::string layer_string = getNumberSequenceStr(level_reader);
	std::string::iterator iterator = layer_string.begin();

	for (int j = 0; j < _matrixSize.y; j++)
	{
		matrix[j] = new int[_matrixSize.x];

		for (int k = 0; k < _matrixSize.x; k++)
		{
			matrix[j][k] = extractNextInt(layer_string, iterator) - 1;
		}
	}
}

void Level::serializeDimensions(std::ifstream& level_reader)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	std::string sizeString = getNumberSequenceStr(level_reader);
	std::string::iterator it = sizeString.begin();

	_matrixSize.x = extractNextInt(sizeString, it);
	_matrixSize.y = extractNextInt(sizeString, it);
}

std::string Level::getNumberSequenceStr(std::ifstream& level_reader)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	std::string str_layer = "";
	std::string new_line = "";

	jumpToNext_number(level_reader);

	while (std::isdigit(level_reader.peek()) && !level_reader.eof())
	{
		std::getline(level_reader, new_line);
		str_layer += new_line;
	}

	return str_layer;
}

void Level::jumpToNext_number(std::ifstream& level_reader)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	while (!(std::isdigit(level_reader.peek()) || level_reader.eof()))
	{
		level_reader.ignore(1);
	}
}

void Level::jumpLine(std::ifstream& level_reader)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if(!level_reader.eof())
		level_reader.ignore('\n');
}

int Level::extractNextInt(std::string& str, std::string::iterator& it)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	typedef std::string::size_type pos;

	pos firstNumberPos = it - str.begin();
	pos nextCommaPos = str.find(',', firstNumberPos);
		
	pos numberLenght = 0;
	if (nextCommaPos == str.npos)
		numberLenght = str.end() - it;
	else
		numberLenght = nextCommaPos - firstNumberPos;

	int id = std::stoi(str.substr(firstNumberPos, numberLenght));
	
	it += numberLenght; //jump the number
	if (it != str.end()) //jump the comma if there's one
		it++;

	return id;
}

const sf::Vector2f Level::getRealPosition(const sf::Vector2i pos_inLayer) const
{
	return (Tile::getRealSize() * pos_inLayer + _position);
}

void Level::initializeEntities()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	int id = -1;
	sf::Vector2i pos_inMatrix = { 0, 0 };
	_boss_spawn = NULL;

	_realSize = Tile::getRealSize() * _matrixSize;
	_viewCenter = (_realSize / 2.0f) + _position - (Tile::getRealSize() / 2.0f);

	_levelRect.setSize(_realSize);
	_levelRect.setOrigin(_realSize / 2.0f);
	_levelRect.setPosition(_viewCenter);

	sf::RectangleShape* new_level_end = NULL;
	Tile* pTile = NULL;

	for (int j = 0; j < _matrixSize.y; j++)
	{
		for (int k = 0; k < _matrixSize.x; k++)
		{
			id = _tilesIds_matrix[POSITIONS][j][k];
			if (id != -1)
			{
				switch (id)
				{
				case PLAYER_SP:
					_playerSpawn = getRealPosition({ k, j });
					break;

				case ENEMY_SP:
					_enemiesSpawns.push_back({ k, j });
					break;

				case SPIKE_SP:
					_spikeSpawns.push_back({ k, j });
					break;

				case Dispenser_SP:
					_dispenserSpawns.push_back({ k, j });
					break;

				case LEVEL_END:
					new_level_end = new sf::RectangleShape(Tile::getRealSize());
					new_level_end->setOrigin(new_level_end->getSize() / 2.0f);
					new_level_end->setPosition(getRealPosition({ k, j }));
					_levelEnd.push_back(new_level_end);
					break;

				case BOSS_SP:
					_boss_spawn = new sf::Vector2f(getRealPosition({ k, j }));
					break;

				default:
					break;
				}
			}
		}
	}
	


	Enemy* pEnemy = NULL;
	for (unsigned int i = 0; i < _enemiesSpawns.size(); i++)
	{
		if (rand() % 4 > 0) {
			pos_inMatrix = _enemiesSpawns[i];
			pEnemy = _pStage->get_an_enemy(getRealPosition(pos_inMatrix));
			_enemy_list.includeEnemy(pEnemy);
		}
	}
	
	if (_boss_spawn)
	{
		pEnemy = new Boss(*_boss_spawn);
		_enemy_list.includeEnemy(pEnemy);
	}

	Obstacle* pObstacle = NULL;
	for (unsigned int i = 0; i < _spikeSpawns.size(); i++)
	{
		if (rand() % 4 > 0)
		{
			pos_inMatrix = _spikeSpawns[i];
			pObstacle = _pStage->get_spike(getRealPosition(pos_inMatrix));
			_obstacle_list.includeObstacle(pObstacle);
		}
	}
	
	for (unsigned int i = 0; i < _dispenserSpawns.size(); i++)
	{
		if (rand() % 4 > 0)
		{
			pos_inMatrix = _dispenserSpawns[i];

			bool facingRight = false;
			if (_tilesIds_matrix[CONCRETE][pos_inMatrix.y][pos_inMatrix.x - 1] == -1)
				facingRight = false;
			else if (_tilesIds_matrix[CONCRETE][pos_inMatrix.y][pos_inMatrix.x + 1] == -1)
				facingRight = true;

			pObstacle = static_cast<Obstacle*>(new Dispenser(getRealPosition(pos_inMatrix), facingRight));
			_obstacle_list.includeObstacle(pObstacle);

			//Kill the concrete tile at that position
			_tilesIds_matrix[CONCRETE][pos_inMatrix.y][pos_inMatrix.x] = -1;
		}
	}

	for (int j = 0; j < _matrixSize.y; j++)
	{
		for (int k = 0; k < _matrixSize.x; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				id = _tilesIds_matrix[i][j][k];
				if (id != -1)
				{
					pTile = new Tile(getRealPosition({ k, j }), _tilesIds_matrix[i][j][k]);
					_tile_list[i].includeTile(pTile);
				}
			}
		}
	}

	/* Include all entities on the general list */
	for(int i = 0; i < 2; i++)
		for (Tile* pT : _tile_list[i])
			_all_level_ents.includeEntity(static_cast<Entity*>(pT));
	for (Obstacle* pO : _obstacle_list)
		_all_level_ents.includeEntity(static_cast<Entity*>(pO));
	for (Enemy* pE : _enemy_list)
		_all_level_ents.includeEntity(static_cast<Entity*>(pE));
	for (Tile* pT : _tile_list[CONCRETE])
		_all_level_ents.includeEntity(static_cast<Entity*>(pT));
	_all_level_ents.includeEntity(static_cast<Entity*>(_pPlayer1));
	if(_pPlayer2)
		_all_level_ents.includeEntity(static_cast<Entity*>(_pPlayer2));
	for(Tile* pT : _tile_list[FOREGROUND])
		_all_level_ents.includeEntity(static_cast<Entity*>(pT));
}

void Level::setPlayersSpawnPoint()
{
	_pPlayer1->setCurrSpawnPoint(_playerSpawn);
	if (_pPlayer2)
		_pPlayer2->setCurrSpawnPoint(_playerSpawn);
}

void Level::start()
{
	setPlayersSpawnPoint();
	movePlayersToSpawn();

	setViewToCenter();

	Projectile::setProjList(&_projectile_list);
	Projectile::setEntList(&_all_level_ents);
}

void Level::setViewToCenter()
{
	_pGraphMng->setViewCenter(_viewCenter);
}

void Level::spawnBoss(sf::Vector2f pos)
{
	Boss* pBoss = new Boss(pos);
	_enemy_list.includeEnemy(pBoss);
}

void Level::check_endLevel()
{
	cMng* collMng = cMng::getInstance();
	for (sf::RectangleShape* endTile : _levelEnd)
	{
		if (collMng->intersects(_pPlayer1, endTile) || (_pPlayer2 && collMng->intersects(_pPlayer2, endTile)))
			_finished = true;
	}
}

bool Level::was_finished()
{
	return _finished;
}

void Level::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	check_endLevel();
	check_playersInScreen();

	executePlayers(deltaTime);
	_enemy_list.execute_enemies(deltaTime);
	_obstacle_list.execute_obstacles(deltaTime);
	_projectile_list.execute_projectiles(deltaTime);

	manage_collisions();

	updatePlayersDrawables();
	_enemy_list.update_drawables();
	_obstacle_list.update_drawables();
	_projectile_list.update_drawables();
}

void Level::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_all_level_ents.draw_entities();
	drawPlayersProps();
}

void Level::executePlayers(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_pPlayer1->execute(deltaTime);
	if (_pPlayer2)
		_pPlayer2->execute(deltaTime);
	
	/*std::cout << "Player1 hp: " << _pPlayer1->getHp();
	if (_pPlayer2)
		std::cout << " | " << "Player2 hp: " << _pPlayer2->getHp();
	std::cout << std::endl;*/
}

void Level::updatePlayersDrawables()
{
	_pPlayer1->updateAnime_n_Collider();
	if (_pPlayer2)
		_pPlayer2->updateAnime_n_Collider();
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

void Level::check_playersInScreen()
{
	cMng* colMng = cMng::getInstance();
	if (!colMng->intersects(_pPlayer1, &_levelRect))
		_pPlayer1->die();
	if (_pPlayer2 && !colMng->intersects(_pPlayer2, &_levelRect))
		_pPlayer2->die();
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

void Level::drawPlayersProps()
{
	int hp = _pPlayer1->getHp();
	if (hp < 0)
		hp = 0;
	std::string str = "HP 1: " + std::to_string(hp) + '\n';
	if (_pPlayer2)
	{
		int hp = _pPlayer2->getHp();
		if (hp < 0)
			hp = 0;
			str += "HP 2: " + std::to_string(hp) + '\n';
	}
	_playersProps.setString(str);
	_pGraphMng->draw(_playersProps);
}

void Level::manage_collisions()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	Collision_Manager* cMng = cMng::getInstance();

	cMng->collide(_pPlayer1, &_tile_list[CONCRETE]);
	cMng->collide(_pPlayer2, &_tile_list[CONCRETE]);
	cMng->collide(_pPlayer1, &_enemy_list);
	cMng->collide(_pPlayer2, &_enemy_list);
	cMng->collide(_pPlayer1, &_obstacle_list);
	cMng->collide(_pPlayer2, &_obstacle_list);
	cMng->collide(_pPlayer1, &_projectile_list);
	cMng->collide(_pPlayer2, &_projectile_list);

	cMng->collide(&_enemy_list, &_tile_list[CONCRETE]);
	cMng->collide(&_enemy_list, &_obstacle_list);
	cMng->collide(&_enemy_list, &_projectile_list);
}