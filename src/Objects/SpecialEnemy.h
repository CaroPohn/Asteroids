#pragma once
#include "header/raylib.h"

#include "Spaceship.h"

namespace Asteroids
{
	struct SpecialEnemy
	{
		Vector2 position = { 0, 0 };
		Vector2 direction = { 0, 0 };
		Vector2 velocity = { 20, 20 };
		Texture2D texture;
		float creationTime = 0;
		float radius = 35.0f;
		bool isActive = false;
		Rectangle source;
		Rectangle dest;
		float rotation = 0;
		int lives = 3;
	};

	SpecialEnemy InitSpecialEnemy(Vector2 position, Spaceship player); 
	void SpecialEnemyUpdate(SpecialEnemy& specialEnemy, Spaceship player);
	void SpecialEnemyDraw(SpecialEnemy specialEnemy);
	void SpecialEnemyReturnToScreen(SpecialEnemy& specialEnemy, float screenWidth, float screenHeight);
}
