// Header File
#include "State.h"

// Other Includes


// Defines/Usings


// Variables


// Functions/Definitions

IState::IState(std::map<std::string, int>* SupportedKeys)
{
	// IO
	cla::construct(*this);

	supportedKeys = SupportedKeys;
}
IState::~IState()
{
	// IO
	cla::deconstruct(*this);
}

GameState::GameState(std::map<std::string, int>* SupportedKeys)
	: IState(SupportedKeys)
{
	// IO
	cla::construct(*this);

	// Initializations
	InitKeybinds();
}
GameState::~GameState()
{
	// IO
	cla::deconstruct(*this);
}

void GameState::InitKeybinds()
{
	// IO
	cla::start(__func__, *this, enable_debug);

	// I - State_SupportedKeys Config Import
	std::ifstream ifs("Config/Keybinds/State_SupportedKeys.ini");

	// I - Window Config Extraction
	cla::debug("Opening [ifs]", enable_debug);
	if (ifs.is_open())
	{
		cla::ifout("ifs.is_open()", true, enable_debug);

		// V - Key Maps
		std::string key = "";
		std::string key_map = "";

		// I - Ifs Extraction
		while (ifs >> key >> key_map)
		{
			keybinds[key] = supportedKeys->at(key_map);
		}
	}
	else
	{
		cla::ifout("ifs.is_open()", false, enable_debug);

		// I - Default Supported Keys
		keybinds["CLOSE"] = supportedKeys->at("Escape");
		keybinds["MOVE_LEFT"] = supportedKeys->at("A");
		keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
		keybinds["MOVE_UP"] = supportedKeys->at("W");
		keybinds["MOVE_DOWN"] = supportedKeys->at("S");
	}
	CLA::debug("Closing [ifs]", enable_debug);
	ifs.close();

	// IO
	cla::end(__func__, enable_debug);
}