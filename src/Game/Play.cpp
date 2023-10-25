#include "Game/Play.h"
#include "header/raymath.h"

namespace Asteroids
{
	static const int MAX_ASTEROIDS = 64;

	Asteroid static asteroidsArr[MAX_ASTEROIDS] = { 0 };
	AsteroidSize asteroidSizes[] = { Small, Medium, Large };

	void Update()
	{
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidUpdate(asteroidsArr[i]);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			//AsteroidSize nextSize = asteroidSizes[GetRandomValue(0, 2)];
			AddAsteroid(GetMousePosition(), Large);
		}
	}

	void Drawing()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidDraw(asteroidsArr[i]);
		}

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

	void RunGame()
	{
		Update();
		Drawing();
	}
}