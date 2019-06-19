//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h" //Base class

//======================================================================================================================================//
// === Derived classes from this === //
// Weak_Stone
// Static_Spike

//======================================================================================================================================//
// === Character Class === //
class Obstacle : public Entity
{
protected:
	// ========= Motion Members ========= //
	//Colliders
	sf::RectangleShape* _obs_collider;

	Timer cd_action;

public:
	//================================================================//
	// ========== Constructors ========== //
	Obstacle(const sf::Vector2f initPosition);
	Obstacle();

	// ========== Destructors ========== //
	virtual ~Obstacle();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_AllColliders();
	virtual void initialize_animator() = 0;


};

