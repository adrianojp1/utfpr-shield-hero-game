//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Weak_Block.h"

//======================================================================================================================================//
// === Static initializations === //
/*const sf::Vector2f Weak_Block::OriginalSize = sf::Vector2f{ 16.0f, 16.0f };
sf::Vector2f Weak_Block::_realSize = OriginalSize;*/

//======================================================================================================================================//
// === Weak_Block methods === //

Weak_Block::Weak_Block(const sf::Vector2f initPosition, const int id) :
	Obstacle(initPosition, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());

	_current_collider = _collider;
	_current_collider->setPosition(_position);
}

Weak_Block::Weak_Block() : Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Weak_Block::~Weak_Block()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Weak_Block::initialize_animator()
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

//upar rachaduras, tremer e sumir quando _coll_onTop
void Weak_Block::updateAction(const float deltaTime)
{
}

