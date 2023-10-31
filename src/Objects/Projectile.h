#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	struct Projectile
	{
		bool isActive;
		Vector2 position;
		Vector2 direction;
		float radius = 7.0f;
		float speed = 450.0f;
		float timeAlive = 2.0f;
		float currentTime = 0;
	};

	Projectile CreateProjectile(Vector2 position, Vector2 direction);
	void ProjectileUpdate(Projectile& projectile);
	void ProjectileDraw(Projectile& projectile);

}