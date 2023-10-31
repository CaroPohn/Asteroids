#pragma once
#include "Objects/Asteroid.h"
#include "Scenes.h"

namespace Asteroids
{
	void Update();
	void Init();
	void Drawing();
	void AddAsteroid(Vector2 position, AsteroidSize size);
	Vector2 GetNextAsteroidPosition();
	void AddProjectile(Vector2 position, float rotation);
	void RunGame(Scenes& scene, bool isNewScene);
}
