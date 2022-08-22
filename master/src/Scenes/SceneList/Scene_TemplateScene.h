// [Scene_TemplateScene].h 


// HEADER GUARD
#ifndef SCENE_TEMPLATESCENE_H
#define SCENE_TEMPLATESCENE_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include "../Scene.h"

// [Scene_TemplateScene] class
class Scene_TemplateScene : public Scene
{
private:
	// Debug
	bool enable_debug = true;

	// Usings
	using deltaTime = float;

protected:
	// Variable - Temp Objects
	Entity* bg_wall = nullptr;

public:
	// Constructors/Destructors

	Scene_TemplateScene(SceneManager& sManager, ECSManager& eManager) : Scene(sManager, eManager)
	{
		cla::construct(*this);
	}
	~Scene_TemplateScene()
	{
		cla::deconstruct(*this);
	}

	// Initializations

	void init() override
	{
		initScene();
	}
	void initScene()
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// I - Assigns and Creates Objects
		bg_wall = &entityManager.addEntity();
		bg_wall->giveLayer(this);
		sf::RectangleShape& wall_rect = bg_wall->addComponent<Base_SquareComponent>().square;
		wall_rect.setSize(sf::Vector2f(ActiveWindow::window->getSize().x, ActiveWindow::window->getSize().y));
		wall_rect.setFillColor(sf::Color::Blue);
		bg_wall->addComponent<Base_KeyboardComponent>();
		
		// IO
		cla::end(__func__, enable_debug);
	}

	// Updates
	
	void update(deltaTime dt) override
	{
		entityManager.update(dt);
	}

	// Render

	void render() override
	{
		entityManager.draw_layer(this);
	}

	// Poll Event

	void pollEvent(sf::Event* event) override
	{
		// IO
		cla::start(__func__, *this, enable_debug);

		// E - Resized
		if (event->type == sf::Event::Resized)
		{
			cla::ifout("event->type == sf::Event::Resized", true, true);
			bg_wall->getComponent<Base_SquareComponent>().square.setSize(sf::Vector2f(ActiveWindow::window->getSize().x, ActiveWindow::window->getSize().y));
		}

		// IO
		cla::end(__func__, enable_debug);
	}
};

// HEADER GUARD END
#endif