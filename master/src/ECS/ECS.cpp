// Header File
#include "ECS.h"

// Other Includes
#include "ComponentList/Base_KeyboardComponent.h"

// Defines/Usings


// Variables


// Functions/Definitions

void Entity::addGroup(Group mGroup)
{
	// IO
	cla::start(__func__, *this, true);

	// I - Assign Entity to Group
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);

	// IO
	cla::end(__func__, true);
}

void ECSManager::updateKeys(std::map<std::string, int>* SupportedKeys, sf::Event* Event)
{
	// IO
	cla::start(__func__, *this, enable_debug);

	// I - Update All Key Components Outside Main Update
	for (auto& e : entities)
	{
		if (e->hasComponent<Base_KeyboardComponent>())
		{
			e->getComponent<Base_KeyboardComponent>().update(SupportedKeys, Event);
		}
	}

	// IO
	cla::end(__func__, enable_debug);
}