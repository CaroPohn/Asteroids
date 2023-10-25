#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	static const int MIN_ROT_SPEED = 5;
	static const int MAX_ROT_SPEED = 240;
	
	enum AsteroidSize
	{
		Small = 1,
		Medium = 2,
		Large = 4
	};

	struct Asteroid
	{
		bool isActive;
		AsteroidSize size;
		Vector2 position;
		float rotation;
		float rotationSpeed;
		Vector2 velocity;
	};

	Asteroid InitAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
	void AsteroidUpdate(Asteroid& asteroid);
	void AsteroidDraw(Asteroid asteroid);
}
