//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Block.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f Block::OriginalSize = sf::Vector2f{ 16.0f, 16.0f };
sf::Vector2f Block::_realSize = OriginalSize;

//======================================================================================================================================//
// === Block methods === //

Block::Block(const sf::Vector2f initPosition, const int id) :
	Entity(initPosition, true, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());
	
	_current_collider = _collider;
	_current_collider->setPosition(_position);
}

Block::Block() : Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Block::~Block()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Block::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	Animation* pAnime = new Animation(gMng::tileset_texture, 1, 0.0f);

	sf::Vector2i blockRectPosition = sf::Vector2i{_id % 24, _id / 24 } * OriginalSize;
	pAnime->setCanvasRect(sf::IntRect(blockRectPosition, sf::Vector2i{ OriginalSize }));
	pAnime->initializeSprite();

	(*_animator) << pAnime;
	(*_animator).setCurrentAnime(0);
	_animator->getCurrentAnime()->getpSprite()->setPosition(_position);
}

void Block::execute(float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Block::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (this->isActive())
	{
		Entity::_pGraphMng->draw(*(_animator->getCurrentAnime()->getpSprite()));
		if (gMng::COLLISION_DBG)
			Entity::_pGraphMng->draw(*(_current_collider));
	}
}

void Block::setBlockRealSize(const sf::Vector2f realSize)
{
	_realSize = realSize;
}

const sf::Vector2f Block::getBlockRealSize()
{
	return _realSize;
}
