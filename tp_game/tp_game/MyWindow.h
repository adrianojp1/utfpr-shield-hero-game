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
	MyWindow();
	// ========== Destructors ========== //
	virtual ~MyWindow();

	//================================================================//
	// ========== Initializers ========== //
	void initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom);

	//================================================================//
	// ========== Loop methods ========== //
	void execute();

	//================================================================//
	// ========== View methods ========== //
	void setViewCenter(sf::Vector2f center);
	void moveView(sf::Vector2f offset);

	//================================================================//
	// ========== Log method ========== //
	static void console_log(std::string log);
};

