// [GlobalPoll].h 


// HEADER GUARD
#ifndef GLOBALPOLL_H
#define GLOBALPOLL_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include <SFML/Graphics.hpp>
#include "../debug/CLA.h"
#include "ActiveWindow.h"

// [GlobalPoll] class
class GlobalPoll
{
private:
	// Debug
	static bool enable_debug;

public:
	// Functions

	static void pollEvent(sf::Event* event);
	static void pollKeys(sf::Event* event);
};

// HEADER GUARD END
#endif