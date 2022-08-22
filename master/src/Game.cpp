// Header File
#include "Game.h"

// Other Includes


// Defines/Usings
#define ED Game::enable_debug


// Variables


// Functions/Definitions

Game::Game()
{
	// IO
	cla::construct(*this);

	init();
	run();

}
Game::~Game()
{
	cla::deconstruct(*this);
}


void Game::initDebug()
{
	// A - Initial Checks outside other Inits.

}

void Game::initWindow()
{
	// IO
	cla::start(__func__, *this, ED);

	// V - Default
	std::string window_title = "Game";
	sf::VideoMode window_bounds(800, 600);
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = false;

	// I - Window Config Import
	std::ifstream ifs("Config/window.ini");

	// I - Window Config Extraction
	CLA::debug("Opening [ifs]", ED);
	if (ifs.is_open())
	{
		cla::ifout("ifs.is_open()", true, ED);

		std::getline(ifs, window_title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}
	else
	{
		cla::ifout("ifs.is_open()", false, ED);
	}
	CLA::debug("Closing [ifs]", ED);
	ifs.close();

	// Window Variable Assignment
	ActiveWindow::window = new sf::RenderWindow(window_bounds, window_title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	ActiveWindow::window->setFramerateLimit(framerate_limit);
	ActiveWindow::window->setVerticalSyncEnabled(vertical_sync_enabled);
	ActiveWindow::isRunning = new bool(true);

	// IO
	cla::end(__func__, ED);
}

void Game::initKeys()
{
	// IO
	cla::start(__func__, *this, ED);

	// I - Game_SupportedKeys Config Import
	std::ifstream ifs("Config/Keybinds/Game_SupportedKeys.ini");

	// I - Window Config Extraction
	CLA::debug("Opening [ifs]", ED);
	if (ifs.is_open())
	{
		cla::ifout("ifs.is_open()", true, ED);

		// V - Key Maps
		std::string key = "";
		int key_value = 0;

		// I - Ifs Extraction
		while (ifs >> key >> key_value)
		{
			CLA::debug("Extracting Keys", key, key_value, ED);
			Game_SupportedKeys[key] = key_value;
		}
	}
	else
	{
		cla::ifout("ifs.is_open()", false, ED);

		// I - Default Supported Keys
		Game_SupportedKeys["Escape"] = sf::Keyboard::Key::Escape;
		Game_SupportedKeys["W"] = sf::Keyboard::Key::W;
		Game_SupportedKeys["S"] = sf::Keyboard::Key::S;
		Game_SupportedKeys["A"] = sf::Keyboard::Key::A;
		Game_SupportedKeys["D"] = sf::Keyboard::Key::D;
	}
	CLA::debug("Closing [ifs]", ED);
	ifs.close();

	// IO
	cla::end(__func__, ED);
}

void Game::initState()
{
	// IO
	cla::start(__func__, *this, enable_debug);

	stateManager.init(&Game_SupportedKeys);

	// IO
	cla::end(__func__, enable_debug);
}

void Game::update(deltaTime dt)
{
	stateManager.update(dt);
}

void Game::render()
{
	ActiveWindow::window->clear(sf::Color::Black);

	stateManager.draw();

	ActiveWindow::window->display();
}

void Game::run()
{
	// IO
	cla::start(__func__, *this, ED);

	// I - Game Loop
	while (*ActiveWindow::isRunning)
	{
		// D - Tick
		cla::tick(__func__, false);

		// I - Delta Time Calculation
		if (dt.asMilliseconds() >= 1 / frames_per_second * 1000)
		{
			cla::tick("deltaTime", dt.asMilliseconds(), false);
			update(dt.asMilliseconds());
			render();
			clock.restart();
		}

		// T - Disable Window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			//ActiveWindow::window->close();
			//*ActiveWindow::isRunning = false;
		}
	}

	// IO
	cla::end(__func__, ED);
}


#undef ED