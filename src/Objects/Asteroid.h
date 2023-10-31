#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	static const int MIN_ROT_SPEED = 5;
	static const int MAX_ROT_SPEED = 240;

	static const int ASTEROID_MIN_SPEED = 100;
	static const int ASTEROID_MAX_SPEED = 200;

	static const int ASTEROID_RANDOM_ANGLE = static_cast<int>(30 * DEG2RAD);

	static const float ASTEROID_LIFE = 10.0f;
	static const float ASTEROID_DELAY = 0.75f;
	static float lastAsteroidCreationTime = -1.0f;
	
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
		float creationTime;
		Vector2 velocity;
	};

	Asteroid InitAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
	void AsteroidUpdate(Asteroid& asteroid);
	void AsteroidDraw(Asteroid asteroid);
	void AsteroidsReturnToScreen(Asteroid& asteroid, float screenWidth, float screenHeight);
}
