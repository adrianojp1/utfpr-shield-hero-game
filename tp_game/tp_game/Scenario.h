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
class Scenario : public Abstract_Entity
{
private:
	//sf::RectangleShape* _background;
	//sf::Texture* _bgtexture;
	CEnt_List _block_list;
	CEnt_List _enemy_list;
	Orc* _orc;

	CEnt_List _all_EntList;
	int** _background;
	int** _concreteBlocks;
	sf::Vector2u _matrixSize;
public:
	// ========== Constructors ========== //
	Scenario();
	// ========== Destructors ========== //
	virtual ~Scenario();

	// ========== Initializers ========== //
	virtual void initializeScenario();

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	// ========== Players methods ========== //
	virtual void executePlayers(const float deltaTime);
	virtual void drawPlayers() const;

	// ========== State ========== //

	// ========== Sets & Gets ========== //
	//_block_ids_matrix
	void setBlock_id_matrix(int** matrix);
	int** getBlock_id_matrix();
	//_matrixSize
	void setMatrixSize(sf::Vector2u size);
	sf::Vector2u getMatrixSize();

	// ========== Collision Management ========== //
	virtual void manage_collisions();
	virtual bool check_collision(Entity* ent1, Entity* ent2);
	virtual bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
};