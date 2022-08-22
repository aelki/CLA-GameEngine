// [Base_TemplateComponent].h 


// HEADER GUARD
#ifndef BASE_TEMPLATECOMPONENT_H
#define BASE_TEMPLATECOMPONENT_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include "../../../debug/CLA.h"
#include "../ComponentList.h"

// [Base_TemplateComponent] class
class Base_TemplateComponent : public Component
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable


public:
	// External Variable (example: TransformComponent* transform;)


	// Overrides

	void init() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Dependencies


		// I - Main


		// IO 
		cla::end(__func__, enable_debug);
	}

	void update(deltaTime dt) override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Main


		// IO 
		cla::end(__func__, enable_debug);
	}

	void draw() override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Main


		// IO 
		cla::end(__func__, enable_debug);
	}
};

// HEADER GUARD END
#endif