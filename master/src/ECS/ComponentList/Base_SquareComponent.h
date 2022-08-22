// [Base_SquareComponent].h 


// HEADER GUARD
#ifndef BASE_SQUARECOMPONENT_H
#define BASE_SQUARECOMPONENT_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include "../../../debug/CLA.h"
#include "../ComponentList.h"

// [SquareComponent] class
class Base_SquareComponent : public Component
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable
	Base_TransformComponent* transform;

public:
	// External Variable (example: TransformComponent* transform;)
	sf::RectangleShape square;

	// Overrides

	void init() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Transform Dependency
		if (!entity->hasComponent<Base_TransformComponent>())
			entity->addComponent<Base_TransformComponent>();
		transform = &entity->getComponent<Base_TransformComponent>();

		// I - Main
		square.setFillColor(sf::Color::Green);

		// IO 
		cla::end(__func__, enable_debug);
	}

	void update(deltaTime dt) override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Main
		square.setPosition(sf::Vector2f(transform->local_position.x, transform->local_position.y));
		square.setSize(sf::Vector2f(transform->width, transform->height));

		// IO 
		cla::end(__func__, enable_debug);
	}

	void draw() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Main
		ActiveWindow::window->draw(square);

		// IO 
		cla::end(__func__, enable_debug);
	}
};

// HEADER GUARD END
#endif