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
		Texture2D texture;
		Rectangle dest = { 0, 0, 85, 50 };
		float scale = 0.35f;
		float radius = 50.0f;
		int lives = 3;
		bool isAlive = true;
	};

	Spaceship InitSpaceship(Vector2 position);
	void SpaceshipMovement(Spaceship& player, Rectangle& spaceship, Vector2& origin, Vector2& mousePos, float& angle, int screenWidth, int screenHeight);
	void PlayerDrawing(Spaceship player, Rectangle source, float angle);
	void SpaceshipReturnToScreen(Spaceship& player, int screenWidth, int screenHeight);

}