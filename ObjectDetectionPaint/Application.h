#pragma once
#include "SFML/Graphics.hpp"
#include "PythonConnector.h"

enum class MouseState
{
	DRAWING,
	CLEARING,
	NOTHING
};

class Application
{
public:
	Application(sf::Vector2f windowSize);
	void run();
private:
	void pollEvent();
	void draw();
	void predict(char predictType);
	void update();
private:
	sf::RenderWindow window;
	// State to control drawing 
	MouseState mState;
	// Dont update window if any action wasnt made
	bool isUpdated;
	// Settings for drawing
	float circleradius;
	// PythonConnector for predictions
	PythonConnector connector;
	// Current drawing color
	sf::Color brushColor;
	// Texture
	sf::Texture test;
};