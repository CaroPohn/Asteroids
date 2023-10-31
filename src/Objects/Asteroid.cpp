#include "Asteroid.h"

#include <iostream>
#include "header/raymath.h"

namespace Asteroids
{
	Asteroid InitAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
	{
		Asteroid asteroid;

		asteroid.isActive = true;
		asteroid.size = size;
		asteroid.position = position;
		asteroid.velocity = velocity;
		asteroid.rotation = static_cast<float>(rand() % 360);
		asteroid.rotationSpeed = static_cast<float>(GetRandomValue(MIN_ROT_SPEED, MAX_ROT_SPEED));
		asteroid.creationTime = static_cast<float>(GetTime());

		return asteroid;
	}

	void AsteroidUpdate(Asteroid& asteroid)
	{
		if (!asteroid.isActive)
		{
			return;
		}

		AsteroidsReturnToScreen(asteroid, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));
		
		asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, GetFrameTime()));
		asteroid.rotation += asteroid.rotationSpeed * GetFrameTime();
	}

	void AsteroidDraw(Asteroid asteroid)
	{
		if (!asteroid.isActive)
		{
			return;
		}
		
		float asteroidRadius = 0;

		if (asteroid.size & Small)
			asteroidRadius = 12;
		else if (asteroid.size & Medium)
			asteroidRadius = 24;
		else if (asteroid.size & Large)
			asteroidRadius = 48;

		DrawCircleLines(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroidRadius, WHITE);
	}

	void AsteroidsReturnToScreen(Asteroid& asteroid, float screenWidth, float screenHeight)
	{
		if (asteroid.position.x + asteroid.velocity.x * GetFrameTime() > screenWidth)
		{
			asteroid.position.x = 0;
			if (asteroid.velocity.y > 0)
			{
				if (asteroid.position.y > screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
			else if (asteroid.velocity.y < 0)
			{
				if (asteroid.position.y < screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
		}
		else if (asteroid.position.x + asteroid.velocity.x * GetFrameTime() < 0)
		{
			asteroid.position.x = screenWidth;
			if (asteroid.velocity.y > 0)
			{
				if (asteroid.position.y > screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
			else if (asteroid.velocity.y < 0)
			{
				if (asteroid.position.y < screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
		}

		if (asteroid.position.y + asteroid.velocity.y * GetFrameTime() > screenHeight)
		{
			asteroid.position.y = 0;
			if (asteroid.velocity.x > 0)
			{
				if (asteroid.position.x > screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
			else if (asteroid.velocity.x < 0)
			{
				if (asteroid.position.x < screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
		}
		else if (asteroid.position.y + asteroid.velocity.y * GetFrameTime() < 0)
		{
			asteroid.position.y = screenHeight;
			if (asteroid.velocity.x > 0)
			{
				if (asteroid.position.x > screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
			else if (asteroid.velocity.x < 0)
			{
				if (asteroid.position.x < screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
		}
	}
}