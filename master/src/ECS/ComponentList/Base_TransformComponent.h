// [Base_TemplateComponent].h 


// HEADER GUARD
#ifndef BASE_TRANSFORMCOMPONENT_H
#define BASE_TRANSFORMCOMPONENT_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include "../../../debug/CLA.h"
#include "../ComponentList.h"

// [Base_TransformComponent] class
class Base_TransformComponent : public Component
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

public:
	// Variable - Base Value
	sf::Vector2f local_position;
	sf::Vector2f world_position;
	sf::Vector2f local_velocity;
	sf::Vector2f limit_velocity;
	bool hasVelocityLimit = false;
	
	// Variable - Properties
	int width = 32, height = 32, scale = 1;
	int speed = 1;
	float rotation = 0;

	// Constructors/Destructors
	Base_TransformComponent()
	{
		cla::construct(*this);
		
		// I - Assignment
		local_position = sf::Vector2f(0.f, 0.f);
	}
	~Base_TransformComponent()
	{
		cla::deconstruct(*this);
	}

	void init() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Assignment
		local_velocity = sf::Vector2f(0.f, 0.f);

		// IO
		cla::end(__func__, enable_debug);
	}

	void update(deltaTime dt) override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Base Transform
		if (rotation > 360.f) { rotation -= 360; }
		if (rotation < 0.f) { rotation += 360; }
		local_position.x += static_cast<int>(local_velocity.x * speed);
		local_position.y += static_cast<int>(local_velocity.y * speed);

		// IO
		cla::end(__func__, enable_debug);
	}
};

// HEADER GUARD END
#endif