// [Base_KeyboardComponent].h 


// HEADER GUARD
#ifndef BASE_KEYBOARDCOMPONENT_H
#define BASE_KEYBOARDCOMPONENT_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include "../../../debug/CLA.h"
#include "../ComponentList.h"
#include <SFML/Graphics.hpp>

// [KeyboardComponent] class
class Base_KeyboardComponent : public Component
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Defaults
	bool isActive = false;
	bool hasVelocity = true;
	int noVelocityMultiplier = 8; // Used to offset the slow speed.

public:
	// Variable - Main
	Base_TransformComponent* transform;

	// Constructors/Destructors
	Base_KeyboardComponent() { cla::construct(*this); }
	~Base_KeyboardComponent() { cla::deconstruct(*this); }

	// Overrides

	void init() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);
	
		// I - Transform Dependency
		if (!entity->hasComponent<Base_TransformComponent>())
			entity->addComponent<Base_TransformComponent>();
		transform = &entity->getComponent<Base_TransformComponent>();
		
		// IO
		cla::end(__func__, enable_debug);
	}
	
	void update(deltaTime dt) override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// IO
		cla::end(__func__, enable_debug);
	}

	void draw() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// IO
		cla::end(__func__, enable_debug);
	}

	// External Function

	void update(std::map<std::string, int>* keybinds, sf::Event* event)
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// UP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//CLA::debug("MOVE_UP", true);
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_UP")))
		{
			CLA::debug("MOVE_UP", true);
			if (!sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_DOWN")))
				if (hasVelocity)
				{
					transform->local_velocity.y -= 1;
				}
				else
				{
					transform->local_velocity.y = -1 * noVelocityMultiplier;
				}
		}
		else
		{
			if (transform->local_velocity.y < 0)
				transform->local_velocity.y = 0;
		}
		// DOWN
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_DOWN")))
		{
			if (!sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_UP")))
				if (hasVelocity)
				{
					transform->local_velocity.y += 1;
				}
				else
				{
					transform->local_velocity.y = 1 * noVelocityMultiplier;
				}
		}
		else
		{
			if (transform->local_velocity.y > 0)
				transform->local_velocity.y = 0;
		}
		// LEFT
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_LEFT")))
		{
			if (!sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_RIGHT")))
				if (hasVelocity)
				{
					transform->local_velocity.x -= 1;
				}
				else
				{
					transform->local_velocity.x = -1 * noVelocityMultiplier;
				}
		}
		else
		{
			if (transform->local_velocity.x < 0)
				transform->local_velocity.x = 0;
		}
		// DOWN
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_RIGHT")))
		{
			if (!sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_LEFT")))
				if (hasVelocity)
				{
					transform->local_velocity.x += 1;
				}
				else
				{
					transform->local_velocity.x = 1 * noVelocityMultiplier;
				}
		}
		else
		{
			if (transform->local_velocity.x > 0)
				transform->local_velocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_UP")) && sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_DOWN")))
		{
			transform->local_velocity.y = 0;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_LEFT")) && sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds->at("MOVE_RIGHT")))
		{
			transform->local_velocity.x = 0;
		}

		// IO
		cla::end(__func__, enable_debug);
	}

	// Call Functions
	void setActive() { isActive = true; }
	void setInactive() { isActive = false; }
	void toggleActive() { if (isActive) isActive = false; else isActive = true; }
};

// HEADER GUARD END
#endif