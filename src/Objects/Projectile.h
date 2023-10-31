#pragma once
#include "header/raylib.h"

namespace Asteroids
{
	static const float PROJECTILE_SPEED = 400.0f;
	static const float PROJECTILE_LIFE = 2.0f;
	static const float PROJECTILE_WIDTH = 10.0f;
	static const float PROJECTILE_HEIGHT = 30.0f;
	
	struct Projectile
	{
		bool isActive;
		Vector2 position;
		float rotation;
		float creationTime;
	};

	Projectile CreateProjectile(Vector2 position, float rotation);
	void ProjectileUpdate(Projectile& projectile);
	void ProjectileDraw(Projectile projectile);

}