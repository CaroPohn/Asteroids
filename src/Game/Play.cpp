#include "Game/Play.h"
#include "header/raymath.h"
#include "Objects/Spaceship.h"

namespace Asteroids
{
	Vector2 playerInitPosition = { (1024.0f / 2.0f), ( 768.0f / 2.0f) }; //Arreglar
	Spaceship player = InitSpaceship(playerInitPosition);

	static const int MAX_ASTEROIDS = 10;

	Asteroid static asteroidsArr[MAX_ASTEROIDS] = { 0 };
	AsteroidSize asteroidSizes[] = { Small, Medium, Large };

	Vector2 mousePos;
	float angle;
	Rectangle spaceship;
	Vector2 origin;

	void Update()
	{
		HideCursor();
		
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidUpdate(asteroidsArr[i]);
		}

		if (GetTime() > lastAsteroidCreationTime + ASTEROID_DELAY)
		{
			AsteroidSize nextSize = asteroidSizes[GetRandomValue(0, 2)];
			AddAsteroid(GetNextAsteroidPosition(), nextSize);
			lastAsteroidCreationTime = static_cast<float>(GetTime());
		}

		SpaceshipMovement(player, spaceship, origin, mousePos, angle, GetScreenWidth(), GetScreenHeight());
	}

	void Drawing()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidDraw(asteroidsArr[i]);
		}

		DrawCircle(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), 5, BLUE); //cursor
		SpaceshipDrawing(spaceship, origin, angle);

		EndDrawing();
	}

	void AddAsteroid(Vector2 position, AsteroidSize size)
	{
		bool created = false;
		Vector2 screenCenter = { static_cast<float>(GetScreenHeight() / 2),  static_cast<float>(GetScreenWidth() / 2) };

		Vector2 velocity = Vector2Subtract(screenCenter, position);
		velocity = Vector2Scale(Vector2Normalize(velocity), static_cast<float>(GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED)));

		velocity = Vector2Rotate(velocity, static_cast<float>(GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE)));

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			if (asteroidsArr[i].isActive)
			{
				continue;
			}

			asteroidsArr[i] = InitAsteroid(position, velocity, size);
			created = true;
			break;
		}
	}

	Vector2 GetNextAsteroidPosition()
	{
		float offscreenDist = 128.0f;
		Vector2 result = { -offscreenDist, -offscreenDist };

		if (GetRandomValue(0, 1))
		{
			if (GetRandomValue(0, 1))
			{
				result.y = GetScreenHeight() + offscreenDist;
			}

			result.x = static_cast<float>(GetRandomValue(static_cast<int>(- offscreenDist), GetScreenWidth() + static_cast<int>(offscreenDist)));
		}
		else
		{
			if (GetRandomValue(0, 1))
			{
				result.x = GetScreenWidth() + offscreenDist;
			}

			result.y = static_cast<float>(GetRandomValue(static_cast<int>(-offscreenDist), GetScreenHeight() + static_cast<int>(offscreenDist)));
		}

		return result;
	}

	void RunGame()
	{
		Update();
		Drawing();
	}
}