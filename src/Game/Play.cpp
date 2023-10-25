#include "Game/Play.h"

namespace Asteroids
{
	static const int MAX_ASTEROIDS = 64;

	Asteroid static asteroidsArr[MAX_ASTEROIDS] = { 0 };

	void Update()
	{
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidUpdate(asteroidsArr[i]);
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
}