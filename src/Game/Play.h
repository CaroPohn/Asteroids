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
	void AddAsteroid(Vector2 position, AsteroidSize size, bool isSpawned);
	void AsteroidsCreation();
	Vector2 GetNextAsteroidPosition();
	void UpdateAsteroidArray();
	void DrawAsteroidArray();
	void AddProjectile(Vector2 position);
	void CheckShottingInput();
	void UpdateProjectileArray();
	void DrawProjectileArray();
	bool CircleCircleCollision(float circle1x, float circle1y, float circle1r, float circle2x, float circle2y, float circle2r);
	void CheckGameCollisions();
	void AsteroidPlayerCollision();
	void ReduceAsteroidSize(Asteroid& asteroid);
	void BulletAsteroidCollision();
	void PlayerLoses(Scenes& scene);
	void RunGame(Scenes& scene, bool isNewScene, Scenes previousScene);
}
