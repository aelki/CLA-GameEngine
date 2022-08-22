// [ActiveWindow].h 


// HEADER GUARD
#ifndef ACTIVEWINDOW_H
#define ACTIVEWINDOW_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include <SFML/Graphics.hpp>

// [ActiveWindow] class
// - Kept (static) for simplicity sake.
class ActiveWindow
{
private:
	// Debug
	bool enable_debug = true;

	// Usings


public:
	// Variable
	static sf::RenderWindow* window;
	static bool* isRunning;

	// Constructors/Destructors
	ActiveWindow() = delete;
};

// HEADER GUARD END
#endif