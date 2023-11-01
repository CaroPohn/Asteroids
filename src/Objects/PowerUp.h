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
		float radius = 10.0f;
	};

	void ChooseRandPosition(PowerUp& powerUp); 
	void PowerUpController(PowerUp& powerUp);
	void DrawPowerUp(PowerUp powerUp);
}
