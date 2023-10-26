#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	struct Spaceship
	{
		Vector2 position;
		Vector2 direction;
		Vector2 acceleration = {300, 300};
		Vector2 velocity;
	};

	Spaceship InitSpaceship(Vector2 position);
	void SpaceshipMovement(Spaceship& player, Rectangle& spaceship, Vector2& origin, Vector2& mousePos, float& angle, int screenWidth, int screenHeight);
	void SpaceshipDrawing(Rectangle spaceship, Vector2 origin, float angle);
	void SpaceshipReturnToScreen(Spaceship& player, int screenWidth, int screenHeight);

}