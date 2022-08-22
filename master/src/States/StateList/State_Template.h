// [State_Template].h 


// HEADER GUARD
#ifndef STATE_TEMPLATE_H
#define STATE_TEMPLATE_H

// Include (Implcit)
#include "../../Scenes/SceneList.h"
#include "SFML/Graphics.hpp"

// Includes (STL)


// Includes (User-defined)
#include "../State.h"

// [State_Template] class
class State_Template : public GameState
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - KeyMap
	std::map<std::string, int>* supportedKeys;

	// Variable - Internal
	SceneManager sceneManager;
	sf::Event event;

	// Internal Functions

	void InitKeybinds() override;

public:
	// Constructors/Destructors

	State_Template(std::map<std::string, int>* SupportedKeys);
	~State_Template();

	// Overrides

	void OnEntry() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Inits
		InitKeybinds();

		// I - Push All Scenes for this State
		sceneManager.addScene(new Scene_TemplateScene(sceneManager, *sceneManager.ecs()));

		// I - Scene Inits
		sceneManager.init();

		// IO
		cla::end(__func__, enable_debug);
	}
	void OnExit() override
	{
		// IO
		cla::start(__func__, enable_debug);

		// IO
		cla::end(__func__, enable_debug);
	}
	void update(deltaTime dt) override;
	void draw() override;
	void SetActive(std::vector<GameState*>& StateList) override;

	// Accessors
	
	void pollKeys();
};

// HEADER GUARD END
#endif