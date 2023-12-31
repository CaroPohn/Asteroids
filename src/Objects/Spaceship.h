#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	struct Spaceship
	{
		Vector2 position = { 0, 0 };
		Vector2 direction = { 0, 0 };
		Vector2 acceleration = {300, 300};
		Vector2 velocity = { 0, 0 };
		Texture2D texture;
		Texture2D livesTexture;
		Rectangle dest = { 0, 0, 85, 50 };
		float scale = 0.35f;
		float radius = 50.0f;
		int lives = 3;
		bool isAlive = true;
		int points = 0;
	};

	Spaceship InitSpaceship(Vector2 position);
	void SpaceshipMovement(Spaceship& player, Rectangle& spaceship, Vector2& origin, Vector2& mousePos, float& angle, int screenWidth, int screenHeight);
	void PlayerDrawing(Spaceship player, Rectangle source, float angle);
	void DrawLives(Spaceship player);
	void SpaceshipReturnToScreen(Spaceship& player, int screenWidth, int screenHeight);

}