#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	struct Projectile
	{
		bool isActive = false;
		Vector2 position = { 0, 0 };
		Vector2 direction = { 0, 0 };
		float radius = 7.0f;
		float speed = 450.0f;
		float timeAlive = 4.0f;
		float currentTime = 0;
	};

	Projectile CreateProjectile(Vector2 position, Vector2 direction);
	void ProjectileUpdate(Projectile& projectile);
	void ProjectileDraw(Projectile projectile);

}