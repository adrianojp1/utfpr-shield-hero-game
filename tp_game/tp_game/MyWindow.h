#pragma once

//======================================================================================================================================//
// === MyWindow Class === //
class MyWindow : public sf::RenderWindow
{
private:
	//Pointer for dynamic allocation
	sf::View* pView;

public:
	//================================================================//
	// ========== Constructors ========== //
	MyWindow(float viewZoom, sf::Vector2u windowRatio, unsigned int ratioMultiplier);
	MyWindow();
	// ========== Destructors ========== //
	~MyWindow();

	//================================================================//
	// ========== Initializers ========== //
	void initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom);

	//================================================================//
	// ========== Loop methods ========== //
	void execute();

	static void console_log(std::string log);
};

