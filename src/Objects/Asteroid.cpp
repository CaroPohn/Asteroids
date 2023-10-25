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

		return asteroid;
	}

	void AsteroidUpdate(Asteroid& asteroid)
	{
		if (!asteroid.isActive)
		{
			return;
		}
		
		asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, GetFrameTime()));
		asteroid.rotation += asteroid.rotationSpeed * GetFrameTime();
	}

	void AsteroidDraw(Asteroid asteroid)
	{
		float asteroidRadius = 0;

		if (asteroid.size & Small)
			asteroidRadius = 16;
		else if (asteroid.size & Medium)
			asteroidRadius = 32;
		else if (asteroid.size & Large)
			asteroidRadius = 64;

		DrawPolyLines(asteroid.position, 3, asteroidRadius, asteroid.rotation, WHITE);
	}
}