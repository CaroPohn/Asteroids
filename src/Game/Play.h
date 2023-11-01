#pragma once
#include "header/raylib.h"

#include "Objects/Asteroid.h"
#include "Scenes.h"
#include "Objects/Projectile.h"

namespace Asteroids
{
	void Init();
	void Update(Scenes& scene);
	void Drawing();
	void CheckPauseInput(Scenes& scene);
	void AddAsteroid(Vector2 position, AsteroidSize size);
	void AsteroidsCreation();
	Vector2 GetNextAsteroidPosition();
	void UpdateAsteroidArray();
	void DrawAsteroidArray();
	void AddProjectile(Vector2 position);
	void CheckShottingInput();
	void UpdateProjectileArray();
	void DrawProjectileArray();
	void RunGame(Scenes& scene, bool isNewScene, Scenes previousScene);
}
