// Header File
#include "GlobalPoll.h"

// Other Includes


// Defines/Usings

bool GlobalPoll::enable_debug = false;

// Variables

void GlobalPoll::pollEvent(sf::Event* event)
{
	// IO
	cla::static_start(__func__, enable_debug);

	// E - Resize
	if (event->type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(0, 0, event->size.width, event->size.height);
		ActiveWindow::window->setView(sf::View(visibleArea));
	}
	// E - Button Close
	if (event->type == sf::Event::Closed)
	{
		cla::debug("Closing [window] - StateGlobals triggered by [sf::Event::Closed]", true);
		ActiveWindow::window->close();
		*ActiveWindow::isRunning = false;
	}
	
	// IO
	cla::static_end(__func__, enable_debug);
}
void GlobalPoll::pollKeys(sf::Event* event)
{
	// IO
	cla::static_start(__func__, enable_debug);

	// E - Key Close
	if (event->key.code == sf::Keyboard::Escape)
	{
		cla::debug("Closing [window] - StateGlobals triggered by [sf::Keyboard::Escape]", true);
		ActiveWindow::window->close();
		*ActiveWindow::isRunning = false;
	}

	// IO
	cla::static_end(__func__, enable_debug);
}

// Functions/Definitions

