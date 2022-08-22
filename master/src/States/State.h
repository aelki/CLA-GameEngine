// [State].h 


// HEADER GUARD
#ifndef STATE_H
#define STATE_H

// Include (Implcit)
#include <SFML/Graphics.hpp>
#include "../../debug/CLA.h"
#include "../ActiveWindow.h"

// Includes (STL)
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

// Includes (User-defined)
#include "../GlobalPoll.h"
#include "../Scenes/SceneList.h"

// [IState] class
class IState
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Keys
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	// Internal Functions

	virtual void InitKeybinds() = 0;

public:
	// Constructors/Destructors

	IState(std::map<std::string, int>* SupportedKeys);
	virtual ~IState();

	virtual void OnEntry() = 0;
	virtual void OnExit() = 0;

	// Main Function - Updates

	virtual void update(deltaTime dt) = 0;
};


// [GameState] class
class GameState : public IState
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Internal Functions

	virtual void InitKeybinds();

public:
	// Variable - Active
	bool active = true;

	// Constructors/Destructors
	GameState(std::map<std::string, int>* SupportedKeys);
	~GameState();

	// Overrides

	virtual void OnEntry() = 0;
	virtual void OnExit() = 0;
	virtual void update(deltaTime dt) = 0;

	virtual void SetActive(std::vector<GameState*>& StateList) = 0;

	// Specialty Function

	virtual void draw() = 0;
};


// HEADER GUARD END
#endif