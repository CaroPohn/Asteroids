#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	static const int MIN_ROT_SPEED = 5;
	static const int MAX_ROT_SPEED = 30;

	static const int ASTEROID_MIN_SPEED = 60;
	static const int ASTEROID_MAX_SPEED = 80;

	static const int ASTEROID_RANDOM_ANGLE = static_cast<int>(30 * DEG2RAD);

	static const float ASTEROID_DELAY = 0.75f;
	static float lastAsteroidCreationTime = -1.0f;
	
	enum AsteroidSize
	{
		Small,
		Medium,
		Large
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
		float asteroidRadius;
		Texture2D texture; 
		Rectangle dest = { 0, 0, 85, 50 };
		Rectangle source;
	};

	Asteroid InitAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
	void AsteroidUpdate(Asteroid& asteroid);
	void AsteroidDraw(Asteroid& asteroid);
	void AsteroidsReturnToScreen(Asteroid& asteroid, float screenWidth, float screenHeight);
}
