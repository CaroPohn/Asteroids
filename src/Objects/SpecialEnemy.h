#pragma once
#include "header/raylib.h"

#include "Spaceship.h"

namespace Asteroids
{
	struct SpecialEnemy
	{
		Vector2 position;
		Vector2 direction;
		Vector2 velocity = { 20, 20 };
		Texture2D texture;
		float creationTime;
		float radius = 20.0f;
		bool isActive;
	};

	SpecialEnemy InitSpecialEnemy(Vector2 position, Spaceship player);
	void SpecialEnemyUpdate(SpecialEnemy& specialEnemy, Spaceship player);
	void SpecialEnemyDraw(SpecialEnemy specialEnemy);
	void SpecialEnemyReturnToScreen(SpecialEnemy& specialEnemy, float screenWidth, float screenHeight);
}
