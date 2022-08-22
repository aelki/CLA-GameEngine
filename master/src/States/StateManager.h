// [StateManager].h 


// HEADER GUARD
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

// Include (Implcit)
#include <SFML/Graphics.hpp>
#include "../../debug/CLA.h"
#include "../ActiveWindow.h"

// Includes (STL)
#include <queue>

// Includes (User-defined)
#include "StateList.h"

// [StateManager] class
class StateManager
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Containers
	std::queue<StateType> stateQueue;
	std::vector<GameState*> stateList;
	GameState* currentState;

	// Variable - KeyMap
	std::map<std::string, int>* supportedKeys;

	// Variable - Settings
	bool allowStateSwitch = true;

	// Variable - Delta Time
	deltaTime stateDelay = 0.f;
	deltaTime state_swap_cooldown = 1.2f;

public:
	// Constructors/Destructors

	StateManager();
	~StateManager();


	// Initializations

	void init(std::map<std::string, int>* SupportedKeys);

	// Updates

	void update(deltaTime dt);

	// Renders

	void draw();

	// Main Functions

	void setDefault();

	void changeState(StateType stateType);
	void switchState(size_t index);
};

// HEADER GUARD END
#endif