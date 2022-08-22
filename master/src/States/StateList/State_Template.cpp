// Header File
#include "State_Template.h"

// Other Includes


// Defines/Usings
#define ED State_Template::enable_debug

// Variables


// Functions/Definitions

State_Template::State_Template(std::map<std::string, int>* SupportedKeys)
	: GameState(SupportedKeys)
{
	// IO
	cla::construct(*this);

	// I - Assignment
	supportedKeys = SupportedKeys;

	OnEntry();
}
State_Template::~State_Template()
{
	// IO
	cla::deconstruct(*this);

	OnExit();
}

void State_Template::update(deltaTime dt)
{
	// IO
	cla::start(__func__, *this, enable_debug);

	// I - Update Event
	while (ActiveWindow::window->pollEvent(event))
	{
		GlobalPoll::pollEvent(&event);
		GlobalPoll::pollKeys(&event);
	}

	// I - Update Keys
	pollKeys();
	sceneManager.ecs()->updateKeys(&keybinds, &event);

	// I - Update Scene
	sceneManager.update(dt);

	// IO
	cla::end(__func__, enable_debug);
}
void State_Template::draw()
{
	// IO
	cla::start(__func__, *this, enable_debug);

	sceneManager.render();

	// IO
	cla::end(__func__, enable_debug);
}
void State_Template::SetActive(std::vector<GameState*>& StateList)
{
	// IO
	cla::start(__func__, *this, enable_debug);



	// IO
	cla::end(__func__, enable_debug);
}

void State_Template::pollKeys()
{
	// IO
	cla::start(__func__, *this, enable_debug);

	// Note
	// Poll Keys does not seem to work here, for whatever reason
	// that sf::IsKeyPressed here causes a crash.
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("MOVE_UP")))
	{
		cla::debug("MOVE_UP");
	}

	// IO
	cla::end(__func__, enable_debug);
}

void State_Template::InitKeybinds()
{
	// IO
	cla::start(__func__, *this, enable_debug);

	// Window Config Import
	std::ifstream ifs("../../../Config/Keybinds/State_supportedKeys.ini");

	// Window Config Extraction
	if (ifs.is_open())
	{
		CLA::debug("[State_Template] - [ifs.is_open()] returns true.", ED);

		std::string key = "";
		std::string key_map = "";
		while (ifs >> key >> key_map)
		{
			keybinds[key] = supportedKeys->at(key_map);
		}
	}
	else
	{
		CLA::debug("[State_Template] - [ifs.is_open()] returns false.", ED);

		//cla::debug("Keybinds - ", supportedKeys->at("Escape"), true);
		//cla::debug("Keybinds - ", supportedKeys->at("A"), true);
		//cla::debug("Keybinds - ", supportedKeys->at("D"), true);
		//cla::debug("Keybinds - ", supportedKeys->at("W"), true);
		//cla::debug("Keybinds - ", supportedKeys->at("S"), true);

		// Note: I think the "Escape" as input should be.
		// sf::Keyboard::Escape because it is an int.
		keybinds["CLOSE"] = supportedKeys->at("Escape");
		keybinds["MOVE_LEFT"] = supportedKeys->at("A");
		keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
		keybinds["MOVE_UP"] = supportedKeys->at("W");
		keybinds["MOVE_DOWN"] = supportedKeys->at("S");
	}
	CLA::debug("[State_Template] - [state_supportedKeys] assigned a value!", ED);
	CLA::debug("[State_Template] - Closing [ifs]", ED);
	ifs.close();

	// IO
	cla::end(__func__, enable_debug);
}