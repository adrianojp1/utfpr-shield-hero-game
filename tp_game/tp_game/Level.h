#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Abstract_Entity.h" //base class

//Entities
#include "Player.h"
#include "Tile.h"
//Enemies
#include "Orc.h"
#include "BlackSkeleton.h"
#include "WhiteSkeleton.h"
//Obstacles
#include "Dynamic_Spike.h"
#include "Ghost_Tile.h"
//

//Lists
#include "CEnt_List.h"
#include "Enemy_List.h"
#include "Obstacle_List.h"
#include "Tile_List.h"
//
//======================================================================================================================================//
// === Stage Class === //
class Level : public Abstract_Entity
{
private:
	sf::Vector2f _viewCenter;

	//Lists
	CEnt_List _all_EntList;
	Enemy_List _enemy_list;
	Obstacle_List _obstacle_list;
	Tile_List _collisiveTile_list;
	//
	
	//Totals
	int _nTotalEnemies;
	int _nTotalObstacles;
	//

	//Tiles
	sf::Vector2i _matrixSize;
	int*** _tilesIds_matrix;
	//

	sf::Vector2f _realSize;

	//Positions
	sf::Vector2f _playerSpawn;
	sf::RectangleShape _levelEnd;
	std::vector<sf::Vector2f> _enemiesSpawns;
	std::vector<sf::Vector2f> _obstaclesSpawns;
	//

public:
	// ========== Constructors ========== //
	Level(std::string level_tiles_filePath, sf::Vector2f initPosition, const int nEnemies, const int nObstacles);
	Level();
	// ========== Destructors ========== //
	virtual ~Level();

	// ========== Initializers ========== //
	//Serializers
	virtual void serializeTiles(const std::string level_filePath);
	virtual void serializeLayer(std::ifstream& level_reader, int** matrix);
	virtual void serializeDimensions(std::ifstream& level_reader);
	virtual std::string getNumberSequenceStr(std::ifstream& level_reader);
	virtual void jumpToNext_number(std::ifstream& level_reader);
	virtual void jumpLine(std::ifstream& level_reader);
	virtual int extractNextInt(std::string& str, std::string::iterator& it);
	virtual const sf::Vector2f getRealPosition(const sf::Vector2i pos_inLayer) const;
	//

	virtual void initializeEntities();
	virtual void setPlayersSpawnPoint();
	virtual void start();
	virtual void setViewToCenter();
	//virtual void finish();

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	// ========== Players methods ========== //
	virtual void executePlayers(const float deltaTime);
	virtual void updatePlayersDrawables();
	virtual void drawPlayers() const;
	virtual void movePlayersToSpawn();

	// ========== State ========== //

	// ========== Sets & Gets ========== //
	//_block_ids_matrix
	void setTiles_ids_matrix(int*** matrix);
	int*** getTiles_ids_matrix();
	//_matrixSize
	void setMatrixSize(sf::Vector2i size);
	sf::Vector2i getMatrixSize() const;

	// ========== Collision Management ========== //
	virtual void manage_collisions();

private:
	enum Layers
	{
		BACKGROUND_0,
		BACKGROUND_1,
		CONCRETE,
		FOREGROUND,
		POSITIONS
	};
	static const int nLayers;

#define PLAYER_SP	168
#define ENEMY_SP	169
#define OBSTACLE_SP 193
#define LEVEL_END	192
};