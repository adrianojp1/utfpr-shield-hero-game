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
Animator::Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, Entity* pEntity)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_nFrames = nFrames;
	_switchTime = switchTime;

	_currentTime = 0.0f;
	_frameCounter = 0;

	_pEntity = pEntity;

	initializeSprite_n_Texture(texture_filePath);

} // end constr (parameters)

Animator::Animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_nFrames = 0;
	_switchTime = 0;
	_currentTime = 0.0f;
	_frameCounter = 0;
	_pSprite = NULL;
	_pEntity = NULL;
	_pTexture = NULL;
} // end constr (no parameters)

Animator::~Animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
} // end destr

void Animator::initializeSprite_n_Texture(std::string texture_filePath)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_pSprite = new sf::RectangleShape;
	_pTexture = NULL;
	//_pSprite->setSize(sf::Vector2f{ _pSprite->getTexture()->getSize().x * 4.0f, _pSprite->getTexture()->getSize().y * 4.0f });
	gMng::load_n_setTexture(_pSprite, texture_filePath, _pTexture);
	
	sf::Vector2u textureSize = _pSprite->getTexture()->getSize();
	//Set canvas borders
	_canvasRect.width = (int)(textureSize.x / _nFrames);
	_canvasRect.height = (int)(textureSize.y);
	_canvasRect.top = 0;

	_pSprite->setSize(sf::Vector2f((float)_canvasRect.width, (float)_canvasRect.height));
	_pSprite->setOrigin(_pSprite->getSize() / 2.0f);

} // end initializeTexture

void Animator::updateSprite(float deltaTime, bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_currentTime += deltaTime;

	updateFrame();
	updateSpriteDirection(facingRight);

	_pSprite->setTexture(_pTexture);
	_pSprite->setTextureRect(_canvasRect);
	_pSprite->setPosition(_pEntity->getPosition());
} // end updateSprite

void Animator::setFrameCounter(unsigned int frameCounter)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_frameCounter = frameCounter;
}

unsigned int Animator::getSpriteCounter() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _frameCounter;
}

void Animator::setnFrames(unsigned int nFrames)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_nFrames = nFrames;
}

unsigned int Animator::getnFrames() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _nFrames;
}

void Animator::setCurrentTime(float currentTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_currentTime = currentTime;
}

float Animator::getCurrentTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _currentTime;
}

void Animator::setSwitchTime(float switchTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_switchTime = switchTime;
}

float Animator::getSwitchTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _switchTime;
}

void Animator::setpSprite(sf::RectangleShape* pSprite)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_pSprite = pSprite;
}

sf::RectangleShape* Animator::getpSprite() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _pSprite;
}

sf::Vector2f Animator::getSpriteSize() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return sf::Vector2f( (float)_canvasRect.width, (float)_canvasRect.height );
}

void Animator::updateFrame()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Enough time to change the frame
	if (_currentTime >= _switchTime)
	{
		_currentTime -= _switchTime; //Discount the time
		_frameCounter++;

		//The animation is over
		if (_frameCounter >= _nFrames)
		{
			_frameCounter = 0;
		}
	}
} // end updateFrame

void Animator::updateSpriteDirection(bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (facingRight)
	{
		_canvasRect.left = _frameCounter * _canvasRect.width;
		_canvasRect.width = abs(_canvasRect.width);
	}
	else
	{
		_canvasRect.left = (_frameCounter + 1) * abs(_canvasRect.width);
		_canvasRect.width = -abs(_canvasRect.width);
	}
} // end updateSpriteDirection