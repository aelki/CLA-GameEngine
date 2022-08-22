// Header File
#include "StateManager.h"

// Other Includes


// Defines/Usings
#define ED StateManager::enable_debug

// Variables


// Functions/Definitions

StateManager::StateManager()
{
	// IO
	cla::construct(*this);
}
StateManager::~StateManager()
{
	// IO
	cla::deconstruct(*this);
}

void StateManager::init(std::map<std::string, int>* SupportedKeys)
{
	// IO
	cla::start(__func__, *this, ED);

	// I - Default State Init
	supportedKeys = SupportedKeys;
	stateList.push_back(new State_Template(SupportedKeys));
	currentState = stateList.front();

	// IO
	cla::end(__func__, ED);
}

void StateManager::update(deltaTime dt)
{
	// I - [stateDelay] linker for state_swap_cooldown.
	stateDelay += dt;

	// I - Update All
	currentState->update(dt);

	// I - Load State from Queue
	if (!stateQueue.empty())
	{
		cla::ifout("stateQueue.empty()", false, enable_debug);
		changeState(stateQueue.front());
	}
}

void StateManager::draw()
{
	// IO
	cla::start(__func__, *this, enable_debug);
	
	// I - Draw All
	currentState->draw();

	// IO
	cla::end(__func__, enable_debug);
}

void StateManager::changeState(StateType stateType)
{
	// IO
	cla::start(__func__, *this, enable_debug);

	// I - Swap on Cooldown
	if (stateDelay > state_swap_cooldown)
	{
		cla::ifout("stateDelay > state_swap_cooldown", true, false);

		// I - Switch
		switch (stateType)
		{
		default:
			// No Existing State
			CLA::debug("[changeState(StateType stateType)] - Invalid State!", ED);
			break;
		case StateType::Template:
			// Main Menu
			stateList.push_back(new State_Template(supportedKeys));
			currentState = stateList.back();
			break;
		}

		// I - Queue Pop
		if (!stateQueue.empty())
		{
			cla::ifout("stateQueue.empty()", false, enable_debug);
			stateQueue.pop();
		}

		// I - Tick Reset
		stateDelay = 0.f;
	}
	else
	{
		stateQueue.push(stateType);
	}
}