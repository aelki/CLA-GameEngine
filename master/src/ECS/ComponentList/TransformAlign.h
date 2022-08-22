// [TransformAlign].h 


// HEADER GUARD
#ifndef TRANSFORMALIGN_H
#define TRANSFORMALIGN_H

// Include (Implcit)


// Includes (STL)


// Includes (User-defined)
#include "Base_TransformComponent.h"

// Temporary Defines
#define TransformComponent Base_TransformComponent

// [Align] class
class Align
{
public:
	static void center(TransformComponent* transform)
	{
		transform->local_position.x -= (transform->width * transform->scale) / 2;
		transform->local_position.y -= (transform->height * transform->scale) / 2;
	}
	static void center_left(TransformComponent* transform)
	{
		transform->local_position.y -= (transform->height * transform->scale) / 2;
	}
	static void center_right(TransformComponent* transform)
	{
		transform->local_position.x -= (transform->width * transform->scale);
		transform->local_position.y -= (transform->height * transform->scale) / 2;
	}
	static void center_down(TransformComponent* transform)
	{
		transform->local_position.x -= (transform->width * transform->scale) / 2;
		transform->local_position.y -= (transform->height * transform->scale);
	}
	static void center_up(TransformComponent* transform)
	{
		transform->local_position.x -= (transform->width * transform->scale) / 2;
	}
	static void corner_topleft(TransformComponent* transform) {}
	static void corner_topright(TransformComponent* transform)
	{
		transform->local_position.x -= (transform->width * transform->scale);
	}
	static void corner_downleft(TransformComponent* transform)
	{
		transform->local_position.y -= (transform->height * transform->scale);
	}
	static void corner_downright(TransformComponent* transform)
	{
		transform->local_position.x -= (transform->width * transform->scale);
		transform->local_position.y -= (transform->height * transform->scale);
	}
};

#undef TransformComponent

// HEADER GUARD END
#endif

