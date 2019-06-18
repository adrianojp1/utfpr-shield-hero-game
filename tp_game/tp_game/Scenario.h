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
	sf::RectangleShape* _background;
	sf::Texture* _bgtexture;
	std::vector<Block*> _vBlocks;
	Orc* _orc;
public:
	// ========== Constructors ========== //
	Scenario();
	// ========== Destructors ========== //
	virtual ~Scenario();

	// ========== Initializers ========== //
	virtual void initializeScenario();

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw() const;

	// ========== Players methods ========== //
	virtual void executePlayers(const float deltaTime);
	virtual void drawPlayers() const;

	// ========== State ========== //

	// ========== Sets & Gets ========== //

	// ========== Collision Management ========== //
	virtual void manage_collisions();
	virtual bool check_collision(Entity* ent1, Entity* ent2);
	virtual bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
};