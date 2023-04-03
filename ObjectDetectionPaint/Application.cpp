#include "Application.h"
#include <iostream>

Application::Application(sf::Vector2f windowSize) : window(sf::VideoMode((unsigned)windowSize.x, (unsigned)windowSize.y), "Paint", sf::Style::None),mState(MouseState::NOTHING),isUpdated(true)
{
	window.setFramerateLimit(144);
	this->circleradius = 2.0f;
	// Set brush color
	brushColor = sf::Color::White;
	// Texture
	test.create(window.getSize().x, window.getSize().y);
}

void Application::run()
{
	while (window.isOpen())
	{
		pollEvent();
		if (isUpdated)
		{
			window.clear();
			update();
			draw();
			window.display();
			isUpdated = false;
		}
	}
}

void Application::pollEvent()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::R)
			{
				window.clear(sf::Color::Black);
				test.update(window);
				isUpdated = true;
			}
			if (e.key.code == sf::Keyboard::P)
			{
				predict('D');
			}
			if (e.key.code == sf::Keyboard::O)
			{
				predict('O');
			}
			if (e.key.code == sf::Keyboard::Add)
			{
				circleradius += 0.5f;
			}
			else if (e.key.code == sf::Keyboard::Subtract)
			{
				circleradius -= 0.5f;
				if (circleradius <= 0.5f)
				{
					circleradius = 0.5f;
				}
			}
			switch (e.key.code)
			{
			case sf::Keyboard::Num1:
				brushColor = sf::Color::Blue;
				break;
			case sf::Keyboard::Num2:
				brushColor = sf::Color::Green;
				break;
			case sf::Keyboard::Num3:
				brushColor = sf::Color::Red;
				break;
			case sf::Keyboard::Num4:
				brushColor = sf::Color::Yellow;
				break;
			case sf::Keyboard::Num5:
				brushColor = sf::Color::Magenta;
				break;
			case sf::Keyboard::Num6:
				brushColor = sf::Color::White;
				break;
			}
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				isUpdated = true;
				mState = MouseState::DRAWING;
			}
			if (e.mouseButton.button == sf::Mouse::Right)
			{
				isUpdated = true;
				mState = MouseState::CLEARING;
			}
		}
		if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				mState = MouseState::NOTHING;
			}
			if (e.mouseButton.button == sf::Mouse::Right)
			{
				mState = MouseState::NOTHING;
			}
		}
		if (e.type == sf::Event::MouseMoved)
		{
			if (mState != MouseState::NOTHING)
			{
				isUpdated = true;
			}
		}
	}
}

void Application::draw()
{
	// Draw updated texture
	sf::RectangleShape rectShape;
	rectShape.setPosition(sf::Vector2f(0.0f, 0.0f));
	rectShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	rectShape.setTexture(&test);
	window.draw(rectShape);
}

void Application::predict(char predictType)
{
	// Clear console
	system("CLS");
	// Save to file
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	texture.copyToImage().saveToFile("Predict.jpg");

	if (predictType == 'D')
	{
		std::vector<float> result = connector.predictImage();
		for (int i = 0; i < result.size(); i++)
		{
			std::cout << "Value: " << i << " Predicted Probability: " << result[i] << std::endl;
		}
	}
	else if (predictType == 'O')
	{
		connector.predictObject();
	}
}

void Application::update()
{
	if (mState == MouseState::NOTHING)
	{
		return;
	}
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	// Add changes to window
	sf::CircleShape shape;
	shape.setRadius(circleradius);
	shape.setOrigin(circleradius, circleradius);
	shape.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
	if (mState == MouseState::DRAWING)
	{
		shape.setFillColor(brushColor);
	}
	else if (mState == MouseState::CLEARING)
	{
		shape.setFillColor(sf::Color::Black);
	}
	// Draw texture
	sf::RectangleShape rectShape;
	rectShape.setPosition(sf::Vector2f(0.0f, 0.0f));
	rectShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	rectShape.setTexture(&test);
	window.draw(rectShape);
	// Update window with user input
	window.draw(shape);
	test.update(window);
	// Clear window buffer ( It must be cleared because draw function will draw updated texture again which will cause problems with buffer)
	window.clear();
}
