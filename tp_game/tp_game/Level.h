#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Abstract_Entity.h" //base class
#include "CEnt_List.h"
#include "Player.h"
#include "Orc.h"
#include "Block.h"

//======================================================================================================================================//
// === Stage Class === //
class Level : public Abstract_Entity
{
private:
	//Temp
	CEnt_List _block_list;
	CEnt_List _enemy_list;
	Orc* _orc;
	//
	
	//Lists
	CEnt_List _all_EntList;
	//

	//Tiles
	sf::Vector2i _matrixSize;
	int*** _tilesIds_matrix;
	sf::Vector2f _playerSpawn;
	int _nTotalEnemies;
	int _nTotalObstacles;
	std::vector<sf::Vector2f> _enemiesSpawns;
	std::vector<sf::Vector2f> _obstaclesSpawns;
	//

public:
	// ========== Constructors ========== //
	Level(const std::string level_filePath, sf::Vector2f initPosition, const int nEnemies, const int nObstacles);
	Level();
	// ========== Destructors ========== //
	virtual ~Level();

	// ========== Initializers ========== //
	virtual void serializeTiles(const std::string level_filePath);
	virtual void serializeLayer(std::ifstream& level_reader, int** matrix);
	virtual void serializeDimensions(std::ifstream& level_reader);
	virtual std::string getNumberSequenceStr(std::ifstream& level_reader);
	virtual void jumpToNext_number(std::ifstream& level_reader);
	virtual void jumpLine(std::ifstream& level_reader);
	virtual int extractNextInt(std::string& str, std::string::iterator& it);
	
	virtual void initializeEntities();
	virtual void setPlayersSpawnPoint();

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	// ========== Players methods ========== //
	virtual void executePlayers(const float deltaTime);
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
	virtual bool check_collision(Entity* ent1, Entity* ent2);
	virtual bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);

private:
	static const int BACKGROUND_0;
	static const int BACKGROUND_1;
	static const int CONCRETE;
	static const int FRONTGROUND;
};