// [Scene].h 


// HEADER GUARD
#ifndef SCENE_H
#define SCENE_H

// Include (Implcit)
#include "../../debug/CLA.h"

// Includes (STL)
#include <memory>
#include <vector>
#include <map>

// Includes (User-defined)
#include "../ActiveWindow.h"
#include <SFML/Graphics.hpp>
#include "../ECS/ComponentList.h"

// Forward Declarations
class SceneManager;

// [IScene] class
class IScene
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

public:
	// Virtuals

	virtual void init() = 0;
	
	virtual void update(deltaTime dt) = 0;
	virtual void render() = 0;

	virtual void pollEvent(sf::Event* event) = 0;
};

// [Scene] class
class Scene : public IScene
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable
	SceneManager& sceneManager;
	ECSManager& entityManager;

	// Variable - Properties
	std::string sceneName;
	bool visibility = true;

public:
	// Constructors/Destructors
	Scene(SceneManager& sManager, ECSManager& eManager)
		: sceneManager{ sManager }, entityManager{ eManager }
	{ 
		cla::construct(*this);
	}
	~Scene()
	{
		cla::deconstruct(*this);
	}

	// Overrides

	virtual void init() {}
	virtual void update(deltaTime dt) {}
	virtual void render() {}
	virtual void pollEvent(sf::Event* event) {}

	// Properties

	void title(std::string name) { sceneName = name; }
	std::string title() { return sceneName; }
	void visible(bool Visibility) { visibility = Visibility; }

	// Test Functions
	void testCall()
	{
		cla::debug("[testCall()] is called!", sceneName, enable_debug);
	}
};

// [SceneManager] class
class SceneManager
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Containers
	std::vector<std::unique_ptr<Scene>> scenes;

	// Variable - System
	ECSManager entityManager;

public:
	// Constructors/Destructors
	
	SceneManager()
	{
		cla::construct(*this);
	}
	~SceneManager()
	{
		cla::deconstruct(*this);
	}

	// Initializations
	
	void init()
	{
		for (auto& e : scenes)
		{
			e->init();
		}
	}
	void update(deltaTime dt)
	{	
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Update All
		for (auto& e : scenes)
		{
			e->update(dt);
		}

		// IO
		cla::end(__func__, enable_debug);
	}
	void render()
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Render Else
		entityManager.draw_else();

		// I - Render Layer
		for (auto& e : scenes)
		{
			e->render();
		}

		// IO
		cla::end(__func__, enable_debug);
	}

	// ECS

	ECSManager* ecs() { return &entityManager; }

	// Manipulators

	void pollEvent(sf::Event* event)
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		for (auto& e : scenes)
		{
			e->pollEvent(event);
		}

		// IO
		cla::end(__func__, enable_debug);
	}

	// Manager Functions - Additions

	Scene& addScene(Scene* scene)
	{	
		// IO
		cla::start(__func__, *this, true);

		// I - Assign Unique Pointer to Existing Heap
		std::unique_ptr<Scene> uPtr{ scene };
		scenes.emplace_back(std::move(uPtr));

		// IO
		cla::end(__func__, true);
		return *scene;
	}
	Scene& createScene()
	{
		// IO
		cla::start(__func__, *this, true);

		// I - Create New Heap and Assign to Unique Pointer
		Scene* scene = new Scene(*this, entityManager);
		std::unique_ptr<Scene> uPtr{ scene };
		scenes.emplace_back(std::move(uPtr));

		// IO
		cla::end(__func__, true);
		return *scene;
	}
	Scene& createScene(std::string SceneName)
	{
		// IO
		cla::start(__func__, *this, true);

		// I - Checks if Scene exists already.
		for (auto& e : scenes)
		{
			if (e->title() == SceneName)
			{
				cla::ifout("e->title() == SceneName", true);
				
				// IO
				cla::end(__func__, true);
				return *e;
			}
		}
		
		// IO
		cla::end(__func__, true);
		return createScene();
	}

	void deleteScene_back()
	{
		// IO
		cla::start(__func__, *this, true);

		// I - Deletes Heap
		scenes.back().reset(nullptr);
		scenes.pop_back();

		// IO
		cla::end(__func__, true);
	}
	void deleteScene(std::string SceneName)
	{
		// IO
		cla::start(__func__, *this, true);

		// I - Deletes Heap if Found
		for (auto& e : scenes)
		{
			if (e->title() == SceneName)
			{
				cla::ifout("e->title() == SceneName", true, enable_debug);
			
				e.reset(nullptr);
				if (e != scenes.back())
					scenes.back().swap(e);
				scenes.pop_back();
				
				// IO
				cla::end(__func__, true);
				return;
			}
		}

		// IO
		cla::end(__func__, true);
	}

	// Test Functions

	void testCall()
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Calls Test
		for (auto& e : scenes)
		{
			if (e != nullptr)
			{
				e->testCall();
			}
		}

		// IO
		cla::end(__func__, enable_debug);
	}
	Scene* testAccess(std::string SceneName)
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Acquires Pointer
		for (auto& e : scenes)
		{
			if (e->title() == SceneName)
			{
				// IO
				cla::end(__func__, enable_debug);
				return e.get();
			}
		}

		// IO
		cla::debug("Unable to find scene", true);
		cla::end(__func__, enable_debug);
		return nullptr;
		// or return scenes.back().get();
	}
};


// HEADER GUARD END
#endif