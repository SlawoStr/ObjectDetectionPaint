#include "Application.h"

int main()
{
	sf::Vector2f windowSize(1000.f, 1000.0f);
	Application app(windowSize);
	app.run();
}