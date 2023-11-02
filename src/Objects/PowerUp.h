#pragma once

#include "header/raylib.h"

namespace Asteroids
{
	struct PowerUp
	{
		Vector2 position = { 0, 0 };
		int maxTime = 10;
		float timer = 0;
		bool isActive = false;
		float radius = 20.0f;
		Texture2D texture;
	};

	void InitPowerUpTexture(PowerUp& powerup);
	void ChooseRandPosition(PowerUp& powerUp); 
	void PowerUpController(PowerUp& powerUp);
	void DrawPowerUp(PowerUp powerUp);
}
