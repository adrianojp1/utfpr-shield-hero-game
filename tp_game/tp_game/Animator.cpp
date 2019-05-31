//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Animator.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Entity.h"

//======================================================================================================================================//
// === Animator methods === //
Animator::Animator(Entity* pEntity)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_pEntity = pEntity;
	_currentAnime = NULL;

} // end constr (parameters)

Animator::Animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_pEntity = NULL;
	_currentAnime = NULL;
} // end constr (no parameters)

Animator::~Animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	for (Animation* anime : _vAnimes)
	{
		if (anime)
			delete anime;
	}
	_vAnimes.clear();
} // end destr

void Animator::updateAnimation(float deltaTime, bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_currentAnime->updateAnimation(deltaTime, facingRight);
	_currentAnime->getpSprite()->setPosition(_pEntity->getPosition());
} // end updateSprite

void Animator::setCurrentAnime(const int i)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_currentAnime = _vAnimes[i];
}

Animation* Animator::getCurrentAnime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _currentAnime;
}

void Animator::add_anime(Animation* pAnim)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (pAnim)
		_vAnimes.push_back(pAnim);
}

void Animator::operator<<(Animation* pAnim)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (pAnim)
		this->add_anime(pAnim);
}

Animation* Animator::operator[](int i)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _vAnimes[i];
}
