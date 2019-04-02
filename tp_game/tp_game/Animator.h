#pragma once
#include <SFML\Graphics.hpp>


class Animator
{
private:
	//Frame control
	unsigned int _frameCounter;
	const unsigned int _nFrames;

	//Time control
	float _totalTime;
	const float _switchTime;

	sf::IntRect _canvasRect;
	sf::Texture _texture;
	sf::RectangleShape* _pSprite;

public:
	Animator();
	~Animator();
};

