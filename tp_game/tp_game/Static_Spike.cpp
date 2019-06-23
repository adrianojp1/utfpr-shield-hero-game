//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Static_Spike.h"

//======================================================================================================================================//
// === Static initializations === //
/*const sf::Vector2f Static_Spike::OriginalSize = sf::Vector2f{ 16.0f, 16.0f };
sf::Vector2f Static_Spike::_realSize = OriginalSize;*/

//======================================================================================================================================//
// === Static_Spike methods === //

Static_Spike::Static_Spike(const sf::Vector2f initPosition, const int id) :
	Obstacle(initPosition, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());

	_current_collider = _collider;
	_current_collider->setPosition(_position);
}

Static_Spike::Static_Spike() : Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Static_Spike::~Static_Spike()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Static_Spike::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	Animation* pAnime = new Animation(gMng::tileset_texture, 1, 0.0f);

	sf::Vector2i TileRectPosition = getTileRectPos(_id);
	pAnime->setCanvasRect(sf::IntRect(TileRectPosition, sf::Vector2i{ OriginalSize }));
	pAnime->initializeSprite();

	(*_animator) << pAnime;
	(*_animator).setCurrentAnime(0);
	_animator->getCurrentAnime()->getpSprite()->setPosition(_position);
}

void Static_Spike::updateAction(const float deltaTime)
{
}
