#pragma once

//======================================================================================================================================//
// === MyWindow Class === //
class MyWindow
{
private:
	//Pointers for dynamic allocation
	sf::RenderWindow* pWindow;
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
	void initializeWindow(sf::Vector2u size, std::string title);
	void initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom);

	//================================================================//
	// ========== Loop methods ========== //
	void execute();

	// ========== Window methods redefinitions ========== //
	bool isOpen();
	bool pollEvent(sf::Event& event);
	void close();
	void clear();
	void display();
	//Draw overloads
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	void draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);
	void draw(const sf::VertexBuffer& vertexBuffer, const sf::RenderStates& states = sf::RenderStates::Default);
	void draw(const sf::VertexBuffer& vertexBuffer, std::size_t firstVertex, std::size_t vertexCount, const sf::RenderStates& states = sf::RenderStates::Default);
};

