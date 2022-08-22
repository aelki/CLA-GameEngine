// [ECS].h 


// HEADER GUARD
#ifndef ECS_H
#define ECS_H

// Include (Implcit)


// Includes (STL)
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <map>

// Includes (User-defined)
#include "../../debug/CLA.h"
#include "../ActiveWindow.h"
#include <SFML/Graphics.hpp>

// Forward Declaration
class Component; class Entity; class ECSManager;
class SceneManager; class Scene;

// Variable - Max Limit
constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxGroups = 32;

// Usings/Defines
using ComponentID = std::size_t;
using Group = std::size_t;
using ComponentBitset = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

// Component ID

inline ComponentID getNewComponentID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}
template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentID();
	return typeID;
}

// [Component] class
class Component
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

public:
	// Variable - Entity
	Entity* entity;
	
	// Virtuals

	virtual void init() {}
	virtual void update(deltaTime dt) {}
	virtual void draw() {}

	virtual ~Component() {}
};

// [Entity] class
class Entity
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Entity
	ECSManager& manager;
	std::vector<std::unique_ptr<Component>> components;
	bool active = true;

	ComponentArray componentArray;
	ComponentBitset componentBitset;
	GroupBitset groupBitset;

public:
	// Variable - Scene Layer for Rendering
	Scene* sceneLayer = nullptr;

	// Layer
	void giveLayer(Scene* layer) { sceneLayer = layer; }

	// Constructors/Destructors

	Entity(ECSManager& mManager) 
		: manager(mManager) {}

	// Functions

	void update(deltaTime dt)
	{
		// IO
		cla::start(__func__, *this, enable_debug);
		
		// I - Update Entities
		for (auto& c : components)
			c->update(dt);

		// IO
		cla::end(__func__, enable_debug);
	}
	void draw()
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Draw Entities
		for (auto& c : components)
			c->draw();

		// IO
		cla::end(__func__, enable_debug);
	}

	// Manipulators

	bool isActive() const { return active; }
	void destroy() { active = false; }

	// Group Management
	
	bool hasGroup(Group mGroup) { return groupBitset[mGroup]; }
	void addGroup(Group mGroup);
	void delGroup(Group mGroup) { groupBitset[mGroup] = false; }

	// Component Management

	template <typename T>
	bool hasComponent() const
	{
		// IO
		cla::start(__func__, *this, enable_debug);
		cla::end(__func__, enable_debug);
		return componentBitset[getComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Assigning Component to its Bitset
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();

		// IO
		cla::end(__func__, enable_debug);
		return *c;
	}
	template <typename T> 
	T& getComponent() const
	{
		// IO
		cla::start(__func__, *this, enable_debug);
		
		// I - Get Component of this Entity
		auto ptr(componentArray[getComponentTypeID<T>()]);
	
		// IO
		cla::end(__func__, enable_debug);
		return *static_cast<T*>(ptr);
	}
};

// [ECSManager] class
class ECSManager
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Containers
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	// Constructors/Destructors
	ECSManager() {}
	~ECSManager() {}

	// Triggered Functions
	void updateKeys(std::map<std::string, int>* SupportedKeys, sf::Event* Event);

	// Update/Renders

	void update(deltaTime dt)
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Update All Entity
		for (auto& e : entities)
			e->update(dt);

		// IO
		cla::end(__func__, enable_debug);
	}

	void draw()
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Render All Entity
		for (auto& e : entities)
			e->draw();

		// IO
		cla::end(__func__, enable_debug);
	}
	void draw_layer(Scene* layer)
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Render Selected Layer Entities
		for (auto& e : entities)
			if (e->sceneLayer == layer)
				e->draw();

		// IO
		cla::end(__func__, enable_debug);
	}
	void draw_else()
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Renders Entities without Layers
		for (auto& e : entities)
			if (e->sceneLayer == nullptr)
				e->draw();

		// IO
		cla::end(__func__, enable_debug);
	}

	void refresh()
	{
		//IO
		cla::start(__func__, *this, enable_debug);

		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->hasGroup(i);
				}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));

		// IO
		cla::end(__func__, enable_debug);
	}

	// Group Management

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		// IO
		cla::start(__func__, *this, true);

		// I - Assign Entity to ECS Group
		groupedEntities[mGroup].emplace_back(mEntity);

		// IO
		cla::end(__func__, true);
	}
	std::vector<Entity*>& getGroup(Group mGroup)
	{
		// IO
		cla::start(__func__, *this, true);
		cla::end(__func__, true);
		return groupedEntities[mGroup];
	}

	// Entity Creation

	Entity& addEntity()
	{
		// IO
		cla::start(__func__, *this, true);

		// I - Create New Heap and Assign to Entities
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		
		// IO
		cla::end(__func__, true);
		return *e;
	}
};

// HEADER GUARD END
#endif