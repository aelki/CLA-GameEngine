// Header File
#include "Game.h"

// Includes (Implicit)
#include "../debug/CLA.h"
#include <SFML/Graphics.hpp>

// Other Includes
#include <stdio.h> // U - printf, NULL
#include <stdlib.h> // U - srand, rand
#include <time.h> // U - time

// Defines/Usings


// Global Variable - Settings
bool main_enable_debug = true;

// Function Declarations


// Main Function

int main()
{
	// I - Seeds [rand()]
	srand(time(NULL));

	// I - Test Implementations
	//testTemplate();
	//testSFML();
	//testCLA();
	//testScene();
	
	// I - Launch Game
	Game game;

	// I - End Program
	return 0;
}

void testTemplate() {}
void testSFML()
{
	// Debug
	CLA::debug("===== SFML TEST", main_enable_debug);

	// Variables - Main Properties
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", main_enable_debug);
	sf::CircleShape shape(100.f);
	sf::Event event;
	shape.setFillColor(sf::Color::Green);

	CLA::debug("Opening Window", main_enable_debug);
	// Window Loop
	while (window.isOpen())
	{
		// Poll Input Loop
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}

		CLA::debug("Rendering Window", main_enable_debug);
		// Renders Window
		window.clear();
		window.draw(shape);
		window.display();
	}
}
void testCLA() {}
void testScene() {}

