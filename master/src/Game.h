// [Game].h 


// HEADER GUARD
#ifndef GAME_H
#define GAME_H

// Include (Implcit)
#include <SFML/Graphics.hpp>
#include "../debug/CLA.h"
#include "ActiveWindow.h"
#include <fstream>
#include <sstream>

// Includes (STL)


// Includes (User-defined)
#include "States/StateManager.h"

// [Game] class
class Game
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Delta Time, FPS
	sf::Clock clock;
	sf::Time dt;
	int frames_per_second = 30;

	// Variable - Supported Keys
	std::map<std::string, int> Game_SupportedKeys;

	// Variable - System
	StateManager stateManager;

public:
	// Constructors/Destructors
	
	Game();
	
	~Game();

	// Initializations

	void init()
	{
		initDebug();
		initWindow();
		initKeys();
		initState();
	}
	void initDebug();
	void initWindow();
	void initKeys();
	void initState();

	// Updates

	void update(deltaTime dt);

	// Renders

	void render();

	// Run Loop
	void run();
};

// HEADER GUARD END
#endif