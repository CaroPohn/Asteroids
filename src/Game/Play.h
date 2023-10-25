#pragma once
#include "Objects/Asteroid.h"
#include "Scenes.h"

namespace Asteroids
{
	void Update();
	void Drawing();
	void AddAsteroid(Vector2 position, AsteroidSize size);
	void RunGame();
}
