//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Level.h"

//======================================================================================================================================//
// === Statics Initialization === //
const int Level::nLayers(5);

//======================================================================================================================================//
// === Level methods === //
Level::Level(const std::string level_tiles_filePath, sf::Vector2f initPosition, const int nEnemies, const int nObstacles) : Abstract_Entity(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_nTotalEnemies = nEnemies;
	_nTotalObstacles = nObstacles;
	_tilesIds_matrix = NULL;
	
	serializeTiles(level_tiles_filePath);
	initializeEntities();
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

	for (Enemy* pEne : _enemy_list)
	{
		if (pEne)
			delete pEne;
	}
	_enemy_list.clear();

	for (Tile* pT : _collisiveTile_list)
	{
		if (pT)
			delete pT;
	}
	_collisiveTile_list.clear();
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

	Tile* pTile = NULL;
	int id;

	_realSize = Tile::getRealSize() * _matrixSize;
	_viewCenter = (_realSize / 2.0f) + _position - (Tile::getRealSize() / 2.0f);

	for (int j = 0; j < _matrixSize.y; j++)
	{
		for (int k = 0; k < _matrixSize.x; k++)
		{
			for (int i = 0; i < 2; i++)
			{
				id = _tilesIds_matrix[i][j][k];
				if (id != -1)
				{
					pTile = new Tile(getRealPosition({ k, j }), _tilesIds_matrix[i][j][k]);
					_all_EntList.includeEntity(pTile);
				}
			}

			id = _tilesIds_matrix[CONCRETE][j][k];
			if (id != -1)
			{
				pTile = new Tile(getRealPosition({ k, j }), _tilesIds_matrix[CONCRETE][j][k]);
				_all_EntList.includeEntity(pTile);
				_collisiveTile_list.includeTile(pTile);
			}

			id = _tilesIds_matrix[POSITIONS][j][k];
			if (id != -1)
			{
				switch (id)
				{
				case PLAYER_SP:
					_playerSpawn = getRealPosition({ k, j });
					break;

				case ENEMY_SP:
					_enemiesSpawns.push_back(getRealPosition({ k, j }));
					break;

				case OBSTACLE_SP:
					_obstaclesSpawns.push_back(getRealPosition({ k, j }));
					break;

				case LEVEL_END:
					_levelEnd.setSize(Tile::getRealSize());
					_levelEnd.setOrigin(_levelEnd.getSize() / 2.0f);
					_levelEnd.setPosition(getRealPosition({ k, j }));
					break;

				default:
					break;
				}
			}
		}
	}

	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < _nTotalEnemies; i++)
	{
		Enemy* pEnemy = static_cast<Enemy*>(new Orc(_enemiesSpawns[rand() % _enemiesSpawns.size()]));
		_enemy_list.includeEnemy(static_cast<Enemy*>(pEnemy));
		_all_EntList.includeEntity(static_cast<Entity*>(pEnemy));
	}

	_all_EntList.includeEntity(_pPlayer1);
	if (_pPlayer2)
		_all_EntList.includeEntity(_pPlayer2);

	for (int j = 0; j < _matrixSize.y; j++)
	{
		for (int k = 0; k < _matrixSize.x; k++)
		{
			id = _tilesIds_matrix[FOREGROUND][j][k];
			if (id != -1)
			{
				pTile = new Tile(getRealPosition({ k, j }), _tilesIds_matrix[FOREGROUND][j][k]);
				_all_EntList.includeEntity(pTile);
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

void Level::start()
{
	setPlayersSpawnPoint();
	movePlayersToSpawn();

	_pGraphMng->setViewCenter(_viewCenter);
}

void Level::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	executePlayers(deltaTime);
	_enemy_list.execute_enemies(deltaTime);

	manage_collisions();
}

void Level::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	for (Entity* pEnt : _all_EntList)
	{
		pEnt->draw();
	}
}

void Level::executePlayers(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_pPlayer1->execute(deltaTime);
	if (_pPlayer2)
		_pPlayer2->execute(deltaTime);
	/*
	std::cout << "Player1 hp: " << _pPlayer1->getHp();
	if (_pPlayer2)
		std::cout << " | " << "Player2 hp: " << _pPlayer2->getHp();
	std::cout << std::endl;*/
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

	Collision_Manager* cMng = cMng::getInstance();

	cMng->collide(_pPlayer1, &_collisiveTile_list);
	cMng->collide(_pPlayer2, &_collisiveTile_list);

	cMng->collide(&_enemy_list, &_collisiveTile_list);

	cMng->collide(_pPlayer1, &_enemy_list);
	cMng->collide(_pPlayer2, &_enemy_list);
}