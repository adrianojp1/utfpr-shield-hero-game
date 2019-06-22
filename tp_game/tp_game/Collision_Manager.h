#pragma once
//======================================================================================================================================//
// === Classes Declaration === //
class Entity;

//======================================================================================================================================//
// === Collision_Manager Class === //
class Collision_Manager
{
private:
	static Collision_Manager* _instance;

private:
	//================================================================//
	// ========== Constructors ========== //
	Collision_Manager();
public:
	// ========== Destructors ========== //
	virtual ~Collision_Manager();

	// ========== Singleton ========== //
	static Collision_Manager* getInstance();

	// ========== Collision Management ========== //
	virtual bool check_collision(Entity* ent1, Entity* ent2);
	virtual bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
};

